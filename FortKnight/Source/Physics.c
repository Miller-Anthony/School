//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"
#include "AEVec2.h"
#include "Transform.h"
#include <stdlib.h>
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	AEVec2	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	AEVec2	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	AEVec2	velocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	float inverseMass;

} Physics;

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

// Dynamically allocate a new physics component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
PhysicsPtr PhysicsCreate(void)
{
	Physics* physics = calloc(1, sizeof(Physics));

	if (physics != NULL)
	{
		return physics;
	}
	else
	{
		return NULL;
	}
}

// Free the memory associated with a physics component.
// (Also, set the physics pointer to NULL.)
// Params:
//	 physics = Pointer to the physics pointer.
void PhysicsFree(PhysicsPtr * physics)
{
	if (physics != NULL)
	{
		free(*physics);
		*physics = NULL;
	}
}

// Get the acceleration of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's acceleration structure,
//		else return a NULL pointer.
AEVec2 * PhysicsGetAcceleration(PhysicsPtr physics)
{
	if (physics != NULL)
	{
		return &(physics->acceleration);
	}
	else
	{
		return NULL;
	}
}

// Get the velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's velocity structure,
//		else return a NULL pointer.
AEVec2 * PhysicsGetVelocity(PhysicsPtr physics)
{
	if (physics != NULL)
	{
		return &(physics->velocity);
	}
	else
	{
		return NULL;
	}
}

// Get the old translation (position) of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's oldTranslation structure,
//		else return a NULL pointer.
AEVec2 * PhysicsGetOldTranslation(PhysicsPtr physics)
{
	if (physics != NULL)
	{
		return &(physics->oldTranslation);
	}
	else
	{
		return NULL;
	}
}

// Set the acceleration of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 acceleration = Pointer to an acceleration vector.
void PhysicsSetAcceleration(PhysicsPtr physics, AEVec2 * acceleration)
{
	if (physics != NULL)
	{
		physics->acceleration = *acceleration;
	}
}

// Set the velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 velocity = Pointer to a velocity vector.
void PhysicsSetVelocity(PhysicsPtr physics, AEVec2 * velocity)
{
	if (physics != NULL)
	{
		physics->velocity = *velocity;
	}
}

// Update the state of a physics component.
// (NOTE: This function must verify that the physics and transform pointers are valid.)
// Params:
//	 physics = Pointer to the physics component.
//	 transform = Pointer to the associated transform component.
//	 dt = Change in time (in seconds) since the last game loop.
void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt)
{
	if (physics != NULL && transform != NULL)
	{
		physics->oldTranslation = *TransformGetTranslation(transform);

		physics->velocity.x += physics->acceleration.x * dt;
		physics->velocity.y += physics->acceleration.y * dt;

		AEVec2 translation = *TransformGetTranslation(transform);
		translation.x += physics->velocity.x * dt;
		translation.y += physics->velocity.y * dt;
		TransformSetTranslation(transform, &translation);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

