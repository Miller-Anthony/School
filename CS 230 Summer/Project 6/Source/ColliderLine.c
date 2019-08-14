//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "ColliderLine.h"
#include "Transform.h"
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"


//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderLineSegment
{
	// A single line segment (P0 and P1).
	Vector2D	point[2];
} ColliderLineSegment;

typedef struct ColliderLine
{
	// Inherit the base collider structure.
	Collider	base;

	// The number of line segments in the list.
	unsigned int		lineCount;

	// The individual line segments.
	// (NOTE: Make sure to allocate enough memory for all line segments!)
	ColliderLineSegment	lineSegments[8];

} ColliderLine, *ColliderLinePtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

bool checkLine(const ColliderLineSegment *line, TransformPtr transform, PhysicsPtr physics);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (line) collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Make sure to initialize the ColliderType and memorySize correctly.)
ColliderPtr ColliderLineCreate(void)
{
	ColliderLinePtr holder = calloc(1, sizeof(ColliderLine));

	if (holder)
	{
		holder->base.type = ColliderTypeLine;
		holder->base.memorySize = sizeof(ColliderLine);
		return (ColliderPtr)holder;
	}
	return NULL;
}

// Read the properties of a ColliderLine component from a file.
// (NOTE: First read an integer indicating the number of lines to be read.)
// (NOTE: For each line, read P0 and P1 using StreamReadVector2D.)
// (HINT: Call ColliderLineAddLineSegment() to add each line.)
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.
void ColliderLineRead(ColliderPtr collider, Stream stream)
{
	int count = StreamReadInt(stream);

	for (int i = 0; i < count; ++i)
	{
		Vector2D p0;
		Vector2D p1;

		StreamReadVector2D(stream, &p0);
		StreamReadVector2D(stream, &p1);
		ColliderLineAddLineSegment(collider, &p0, &p1);
	}
}

// Add a line segment to the line collider's line segment list.
// Params:
//	 collider = Pointer to the line collider component.
//	 p0 = The line segment's starting position.
//	 p1 = The line segment's ending position.
void ColliderLineAddLineSegment(ColliderPtr collider, const Vector2D * p0, const Vector2D * p1)
{
	if (collider)
	{
		ColliderLinePtr holder = (ColliderLinePtr)collider;

		holder->lineSegments[holder->lineCount].point[0] = *p0;
		holder->lineSegments[holder->lineCount].point[1] = *p1;

		++holder->lineCount;
	}
}

// Check for collision between a line collider and a circle collider.
// Params:
//	 collider1 = Pointer to the line collider component.
//	 collider2 = Pointer to the circle collider component.
// Returns:
//	 If the pointers are valid,
//	   then return the results of a line-circle collision check,
//	   else return false.
bool ColliderLineIsCollidingWithCircle(ColliderPtr collider, ColliderPtr other)
{
	if (collider && other)
	{
		ColliderLinePtr line = NULL;
		GameObjectPtr circle = NULL;

		if (collider->type == ColliderTypeLine && other->type == ColliderTypeCircle)
		{
			line = (ColliderLinePtr)collider;
			circle = other->parent;
		}
		else if (collider->type == ColliderTypeCircle && other->type == ColliderTypeLine)
		{
			line = (ColliderLinePtr)other;
			circle = collider->parent;
		}
		if (line && circle)
		{
			for (unsigned i = 0; i < line->lineCount; ++i)
			{
				if (checkLine(&(line->lineSegments[i]), GameObjectGetTransform(other->parent), GameObjectGetPhysics(other->parent)))
				{
					return true;
				}
			}
		}
	}
	return false;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

bool checkLine(const ColliderLineSegment *line, TransformPtr transform, PhysicsPtr physics)
{

	Vector2D newPos = *TransformGetTranslation(transform);
	Vector2D oldPos = *PhysicsGetOldTranslation(physics);

	Vector2D lineVec = { 0 };
	Vector2DSub(&lineVec, &(line->point[1]), &(line->point[0]));

	Vector2D normal = { 0 };
	normal.x =  lineVec.y; 
	normal.y = -lineVec.x;
	Vector2DNormalize(&normal, &normal);

	Vector2D v = { 0 };
	Vector2DSub(&v, &oldPos, &newPos);

	if (Vector2DDotProduct(&normal, &v) == 0.0f)
	{
		return false;
	}

	if ((Vector2DDotProduct(&normal, &oldPos) < Vector2DDotProduct(&normal, &line->point[0])) && (Vector2DDotProduct(&normal, &newPos) < Vector2DDotProduct(&normal, &line->point[0])))
	{
		return false;
	}

	if ((Vector2DDotProduct(&normal, &oldPos) > Vector2DDotProduct(&normal, &line->point[0])) && (Vector2DDotProduct(&normal, &newPos) > Vector2DDotProduct(&normal, &line->point[0])))
	{
		return false;
	}

	Vector2D holder = { 0 };
	Vector2DSub(&holder, &oldPos, &(line->point[0]));

	Vector2D Bi = { 0 };
	Vector2DScaleAdd(&Bi, &v, &oldPos, (
		((Vector2DDotProduct(&normal, &(line->point[0])) - Vector2DDotProduct(&normal, &oldPos))
		/ Vector2DDotProduct(&normal, &v))));

	Vector2DSub(&holder, &Bi, &(line->point[0]));

	if (Vector2DDotProduct(&lineVec, &holder) < 0)
	{
		return false;
	}

	Vector2DSub(&holder, &Bi, &(line->point[1]));
	Vector2DNeg(&lineVec, &lineVec);
	if (Vector2DDotProduct(&lineVec, &holder) < 0)
	{
		return false;
	}
	
	Vector2D incident = { 0 };
	Vector2DSub(&incident, &newPos, &Bi);

	Vector2D s = { 0 };
	Vector2DScale(&s, &normal, Vector2DDotProduct(&normal, &incident));

	Vector2D r = { 0 };
	Vector2DScaleAdd(&r, &s, &incident, -2.0f);
	Vector2DAdd(&holder, &r, &Bi);

	TransformSetTranslation(transform, &holder);

	Vector2DNormalize(&r, &r);
	Vector2DScale(&r, &r, Vector2DLength(PhysicsGetVelocity(physics)));

	PhysicsSetVelocity(physics, &r);
	return true;
}