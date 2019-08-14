//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
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

typedef struct Collider		*ColliderPtr;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in ColliderCircle.c.
#if 0
typedef struct ColliderCircle
{
	// Inherit the base collider structure.
	Collider	base;

	// Radius of the circle collider.
	float radius;

} ColliderCircle, *ColliderCirclePtr;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (circle) collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Make sure to initialize the ColliderType and memorySize correctly.)
ColliderPtr ColliderCircleCreate(void);

// Read the properties of a ColliderCircle component from a file.
// (NOTE: Read the radius value using StreamReadFloat.)
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.
void ColliderCircleRead(ColliderPtr collider, Stream stream);

// Get the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
// Returns:
//	 If the pointer is valid,
//	   then return the circle collider's radius,
//	   else return 0.0f.
float ColliderCircleGetRadius(ColliderPtr collider);

// Set the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
//   radius = the circle collider's new radius.
void ColliderCircleSetRadius(ColliderPtr collider, float radius);

// Check for collision between two circle colliders.
// Params:
//	 collider1 = Pointer to the first circle collider component.
//	 collider2 = Pointer to the second circle collider component.
bool ColliderCircleIsCollidingWithCircle(ColliderPtr collider, ColliderPtr other);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

