//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Rotational velocity (in radians).
	float rotationalVelocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

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

// Dynamically allocate a new Physics component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
PhysicsPtr PhysicsCreate(void)
{
	//initialize a Physics object.
	PhysicsPtr holder = calloc(1, sizeof(Physics));

	if (!holder)
	{
		return NULL;
	}

	return holder;
}

// Dynamically allocate a clone of an existing physics component.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
PhysicsPtr PhysicsClone(const PhysicsPtr other)
{
	if (other)
	{
		PhysicsPtr holder = calloc(1, sizeof(Physics));
		if (holder)
		{
			*holder = *other;
			return holder;
		}
	}
	return NULL;
}

// Free the memory associated with a Physics component.
// (Also, set the physics pointer to NULL.)
// Params:
//	 physics = Pointer to the Physics component pointer.
void PhysicsFree(PhysicsPtr * physics)
{
	if (physics)
	{
		free(*physics);
		*physics = NULL;
	}
}

// Read the properties of a Physics component from a file.
// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Physics component.
//	 stream = Pointer to the data stream used for reading.
void PhysicsRead(PhysicsPtr physics, Stream stream)
{
	if (physics && stream)
	{
		Vector2D holder;

		StreamReadVector2D(stream, &holder);
		PhysicsSetAcceleration(physics, &holder);

		StreamReadVector2D(stream, &holder);
		PhysicsSetVelocity(physics, &holder);
	}
}

// Get the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's acceleration structure,
//		else return a NULL pointer.
const Vector2D * PhysicsGetAcceleration(const PhysicsPtr physics)
{
	if (physics)
	{
		return &(physics->acceleration);
	}
	return NULL;
}

// Get the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's velocity structure,
//		else return a NULL pointer.
const Vector2D * PhysicsGetVelocity(const PhysicsPtr physics)
{
	if (physics)
	{
		return &(physics->velocity);
	}
	return NULL;
}

// Get the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return the component's rotational velocity value,
//		else return 0.0f.
float PhysicsGetRotationalVelocity(PhysicsPtr physics)
{
	if (physics)
	{
		return physics->rotationalVelocity;
	}
	return 0.0f;
}

// Get the old translation (position) of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's oldTranslation structure,
//		else return a NULL pointer.
const Vector2D * PhysicsGetOldTranslation(PhysicsPtr physics)
{
	if (physics)
	{
		return &(physics->oldTranslation);
	}
	return NULL;
}

// Set the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 acceleration = Pointer to an acceleration vector.
void PhysicsSetAcceleration(PhysicsPtr physics, const Vector2D * acceleration)
{
	if (physics && acceleration)
	{
		physics->acceleration = *acceleration;
	}
}

// Set the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 velocity = Pointer to a velocity vector.
void PhysicsSetVelocity(PhysicsPtr physics, const Vector2D * velocity)
{
	if (physics && velocity)
	{
		physics->velocity = *velocity;
	}
}

// Set the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 rotationalVelocity = The new rotational velocity.
void PhysicsSetRotationalVelocity(PhysicsPtr physics, float rotationalVelocity)
{
	if (physics)
	{
		physics->rotationalVelocity = rotationalVelocity;
	}
}

// Update the state of a Physics component using the Semi-Implicit Euler method,
//	 as outlined in the "Dynamics" lecture slides and the project instructions.
// (NOTE: This function must verify that the physics and transform pointers are valid.)
// Params:
//	 physics = Pointer to the physics component.
//	 transform = Pointer to the associated transform component.
//	 dt = Change in time (in seconds) since the last game loop.
void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt)
{
	if (physics && transform)
	{
		const Vector2D *holder = TransformGetTranslation(transform);
		const Vector2D *acceleration = PhysicsGetAcceleration(physics);
		const Vector2D *velocity = PhysicsGetVelocity(physics);
		Vector2D newVelocity = *velocity;
		Vector2D newTranslation = *holder;
		float rotation = TransformGetRotation(transform);

		physics->oldTranslation = *holder;

		TransformSetRotation(transform, rotation += physics->rotationalVelocity * dt);

		Vector2DScaleAdd(&newVelocity, acceleration, velocity, dt);
		PhysicsSetVelocity(physics, &newVelocity);

		Vector2DScaleAdd(&newTranslation, &newVelocity, &newTranslation, dt);
		TransformSetTranslation(transform, &newTranslation);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

