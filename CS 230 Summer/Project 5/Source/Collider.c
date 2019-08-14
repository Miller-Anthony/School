//------------------------------------------------------------------------------
//
// File Name:	Collider.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Transform.h"
#include "GameObject.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Collider
{
	// Pointer to the collider's parent game object.
	GameObjectPtr parent;

	// Pointer to a function that handles collisions between two objects.
	CollisionEventHandler	handler;

} Collider;

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

// Dynamically allocate a new Collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
ColliderPtr ColliderCreate(void)
{
	ColliderPtr holder = calloc(1, sizeof(Collider));

	return holder;
}

// Dynamically allocate a clone of an existing Collider component.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ColliderPtr ColliderClone(const ColliderPtr other)
{
	if (other)
	{
		ColliderPtr holder = calloc(1, sizeof(Collider));
		*holder = *other;
		return holder;
	}
	return NULL;
}

// Free the memory associated with a Collider component.
// (Also, set the collider pointer to NULL.)
// Params:
//	 collider = Pointer to the collider component.
void ColliderFree(ColliderPtr * collider)
{
	if (collider)
	{
		free(*collider);
		*collider = NULL;
	}
}

// Read the properties of a Collider component from a file.
// [NOTE: No values need to be read at this time.]
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.
void ColliderRead(ColliderPtr collider, Stream stream)
{
	if (collider && stream)
	{

	}
}

// Set the parent game object for a Collider component.
// Params:
//	 collider = Pointer to the Collider component.
//	 parent = Pointer to the parent game object.
void ColliderSetParent(ColliderPtr collider, GameObjectPtr parent)
{
	if (collider && parent)
	{
		collider->parent = parent;
	}
}

// Check if two objects are colliding.
// (Hint: Refer to the project instructions for implementation suggestions.)
// (Hint: Make sure to call the handler for both colliders, passing the 
//	  parent game object pointers in the correct order!)
// Params:
//	 collider1 = Pointer to the first collider component.
//	 collider2 = Pointer to the second collider component.
void ColliderCheck(ColliderPtr collider, ColliderPtr other)
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
		collider->handler(collider->parent, other->parent);
		other->handler(other->parent, collider->parent);
	}
}

// Set the collision event handler for a collider.
// (Hint: This allows other components, such as behaviors, to respond to collision events.)
// (Note: It is acceptable for the handler to be NULL.  This allows an existing handler to be removed.)
// Params:
//	 collider = Pointer to the collider component.
//	 handler = Pointer to the collision event handler (may be NULL).
void ColliderSetCollisionHandler(ColliderPtr collider, CollisionEventHandler handler)
{
	if (collider)
	{
		collider->handler = handler;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
