//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Collider * ColliderPtr;
typedef struct GameObject * GameObjectPtr;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef void(*CollisionEventHandler)(GameObjectPtr gameObject1, GameObjectPtr gameObject2);

// An example of the structure to be defined in Collider.c.
#if 0
typedef struct Collider
{
	// Pointer to the collider's parent game object.
	GameObjectPtr parent;

	// Pointer to a function that handles collisions between two objects.
	CollisionEventHandler	handler;

} Collider;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
ColliderPtr ColliderCreate(void);

// Dynamically allocate a clone of an existing Collider component.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ColliderPtr ColliderClone(const ColliderPtr other);

// Free the memory associated with a Collider component.
// (Also, set the collider pointer to NULL.)
// Params:
//	 collider = Pointer to the collider component.
void ColliderFree(ColliderPtr * collider);

// Read the properties of a Collider component from a file.
// [NOTE: No values need to be read at this time.]
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.
void ColliderRead(ColliderPtr collider, Stream stream);

// Set the parent game object for a Collider component.
// Params:
//	 collider = Pointer to the Collider component.
//	 parent = Pointer to the parent game object.
void ColliderSetParent(ColliderPtr collider, GameObjectPtr parent);

// Check if two objects are colliding.
// (Hint: Refer to the project instructions for implementation suggestions.)
// (Hint: Make sure to call the handler for both colliders, passing the 
//	  parent game object pointers in the correct order!)
// Params:
//	 collider1 = Pointer to the first collider component.
//	 collider2 = Pointer to the second collider component.
void ColliderCheck(ColliderPtr collider, ColliderPtr other);

// Set the collision event handler for a collider.
// (Hint: This allows other components, such as behaviors, to respond to collision events.)
// (Note: It is acceptable for the handler to be NULL.  This allows an existing handler to be removed.)
// Params:
//	 collider = Pointer to the collider component.
//	 handler = Pointer to the collision event handler (may be NULL).
void ColliderSetCollisionHandler(ColliderPtr collider, CollisionEventHandler handler);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

