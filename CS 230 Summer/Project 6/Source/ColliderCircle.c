//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderCircle.h"
#include "Collider.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderCircle
{
	// Inherit the base collider structure.
	Collider	base;

	// Radius of the circle collider.
	float radius;

} ColliderCircle, *ColliderCirclePtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (circle) collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Make sure to initialize the ColliderType and memorySize correctly.)
ColliderPtr ColliderCircleCreate(void)
{
	ColliderCirclePtr holder = calloc(1, sizeof(ColliderCircle));

	if (holder)
	{
		holder->base.type = ColliderTypeCircle;
		holder->base.memorySize = sizeof(ColliderCircle);
		return (ColliderPtr)holder;
	}
	return NULL;
}

// Read the properties of a ColliderCircle component from a file.
// (NOTE: Read the radius value using StreamReadFloat.)
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.
void ColliderCircleRead(ColliderPtr collider, Stream stream)
{
	if (collider && stream)
	{
		ColliderCirclePtr holder = (ColliderCirclePtr)collider;

		holder->radius = StreamReadFloat(stream);
	}
}

// Get the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
// Returns:
//	 If the pointer is valid,
//	   then return the circle collider's radius,
//	   else return 0.0f.
float ColliderCircleGetRadius(ColliderPtr collider)
{
	if (collider)
	{
		ColliderCirclePtr holder = (ColliderCirclePtr)collider;

		return holder->radius;
	}
	return 0.0f;
}

// Set the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
//   radius = the circle collider's new radius.
void ColliderCircleSetRadius(ColliderPtr collider, float radius)
{
	if (collider)
	{
		ColliderCirclePtr holder = (ColliderCirclePtr)collider;

		holder->radius = radius;
	}
}

// Check for collision between two circle colliders.
// Params:
//	 collider1 = Pointer to the first circle collider component.
//	 collider2 = Pointer to the second circle collider component.
bool ColliderCircleIsCollidingWithCircle(ColliderPtr collider, ColliderPtr other)
{
	if (collider && other)
	{
		TransformPtr colliderTransform = GameObjectGetTransform(collider->parent);
		const Vector2D *colliderPos = TransformGetTranslation(colliderTransform);
		float colliderRadius = TransformGetScale(colliderTransform)->x / 2.0f;

		TransformPtr otherTransform = GameObjectGetTransform(other->parent);
		const Vector2D *otherPos = TransformGetTranslation(otherTransform);
		float otherRadius = TransformGetScale(otherTransform)->x / 2.0f;



		float distance = Vector2DDistance(colliderPos, otherPos);
		if (distance <= colliderRadius + otherRadius)
		{
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

