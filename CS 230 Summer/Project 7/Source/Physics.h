//------------------------------------------------------------------------------
//
// File Name:	Physics.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class Physics * PhysicsPtr;
typedef class Transform * TransformPtr;
//typedef struct Vector2D Vector2D;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef class Physics : public Component
{
public:

	// Dynamically allocate a new Physics component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
	Physics(void);

	// Free the memory associated with a Physics component.
	// (Also, set the physics pointer to NULL.)
	// Params:
	//	 physics = Pointer to the Physics component pointer.
	~Physics(void);

	// Dynamically allocate a clone of an existing physics component.
	// (Hint: Perform a shallow copy of the member variables.)
	// Params:
	//	 other = Pointer to the component to be cloned.
	// Returns:
	//	 If 'other' is valid and the memory allocation was successful,
	//	   then return a pointer to the cloned component,
	//	   else return NULL.
	ComponentPtr Clone(void) const override;

	// Read the properties of a Physics component from a file.
	// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 stream = Pointer to the data stream used for reading.
	void Read(Stream stream);

	// Get the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's acceleration structure,
	//		else return a NULL pointer.
	const Vector2D * GetAcceleration(void);

	// Get the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's velocity structure,
	//		else return a NULL pointer.
	const Vector2D * GetVelocity(void);

	// Get the rotational velocity of a physics component.
	// Params:
	//	 physics = Pointer to the physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return the component's rotational velocity value,
	//		else return 0.0f.
	float GetRotationalVelocity(void);

	// Get the old translation (position) of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's oldTranslation structure,
	//		else return a NULL pointer.
	const Vector2D * GetOldTranslation(void);

	// Set the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 acceleration = Pointer to an acceleration vector.
	void SetAcceleration(const Vector2D * acceleration);

	// Set the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 velocity = Pointer to a velocity vector.
	void SetVelocity(const Vector2D * velocity);

	// Set the rotational velocity of a physics component.
	// Params:
	//	 physics = Pointer to the physics component.
	//	 rotationalVelocity = The new rotational velocity.
	void SetRotationalVelocity(float rotationalVelocity);

	// Set the "drag" value of a Physics component.
	// (NOTE: This value should be clamped between [0.0f, 1.0f].
	// Params:
	//	 physics = Pointer to the physics component.
	//	 drag = The new drag value.
	//void SetDrag(float drag);

	// Update the state of a Physics component using the Semi-Implicit Euler method,
	//	 as outlined in the "Dynamics" lecture slides.
	// (NOTE: This function must verify that the physics and transform pointers are valid.)
	// Params:
	//	 physics = Pointer to the physics component.
	//	 transform = Pointer to the associated transform component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	void Draw() const override;

private:

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
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------