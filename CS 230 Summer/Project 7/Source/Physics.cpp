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
//#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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
Physics::Physics(void) : Component(PhysicsType)
{
	rotationalVelocity = 0;
}

// Dynamically allocate a clone of an existing physics component.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ComponentPtr Physics::Clone(void) const
{
	PhysicsPtr holder = new Physics;
	if (holder)
	{
		*holder = *this;
	}
	return holder;
}

// Free the memory associated with a Physics component.
// (Also, set the physics pointer to NULL.)
// Params:
//	 physics = Pointer to the Physics component pointer.
Physics::~Physics(void)
{

}

// Read the properties of a Physics component from a file.
// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Physics component.
//	 stream = Pointer to the data stream used for reading.
void Physics::Read(Stream stream)
{
	if (stream)
	{
		Vector2D holder;

		StreamReadVector2D(stream, &holder);
		SetAcceleration(&holder);

		StreamReadVector2D(stream, &holder);
		SetVelocity(&holder);
	}
}

// Get the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's acceleration structure,
//		else return a NULL pointer.
const Vector2D * Physics::GetAcceleration(void)
{
	return &acceleration;
}

// Get the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's velocity structure,
//		else return a NULL pointer.
const Vector2D * Physics::GetVelocity(void)
{
	return &velocity;
}

// Get the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return the component's rotational velocity value,
//		else return 0.0f.
float Physics::GetRotationalVelocity(void)
{
	return rotationalVelocity;
}

// Get the old translation (position) of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's oldTranslation structure,
//		else return a NULL pointer.
const Vector2D * Physics::GetOldTranslation(void)
{
	return &oldTranslation;
}

// Set the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 acceleration = Pointer to an acceleration vector.
void Physics::SetAcceleration(const Vector2D * newAcceleration)
{
	if (newAcceleration)
	{
		acceleration = *newAcceleration;
	}
}

// Set the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 velocity = Pointer to a velocity vector.
void Physics::SetVelocity(const Vector2D * newVelocity)
{
	if (newVelocity)
	{
		velocity = *newVelocity;
	}
}

// Set the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 rotationalVelocity = The new rotational velocity.
void Physics::SetRotationalVelocity(float newRotationalVelocity)
{
	rotationalVelocity = newRotationalVelocity;
}

// Update the state of a Physics component using the Semi-Implicit Euler method,
//	 as outlined in the "Dynamics" lecture slides and the project instructions.
// (NOTE: This function must verify that the physics and transform pointers are valid.)
// Params:
//	 physics = Pointer to the physics component.
//	 transform = Pointer to the associated transform component.
//	 dt = Change in time (in seconds) since the last game loop.
void Physics::Update(float dt)
{
	const Vector2D *holder = this->GetParent()->GetTransform()->GetTranslation();
	const Vector2D *holdAcceleration = GetAcceleration();
	const Vector2D *holdVelocity = GetVelocity();
	Vector2D newVelocity = *holdVelocity;
	Vector2D newTranslation = *holder;
	float rotation = this->GetParent()->GetTransform()->GetRotation();

	oldTranslation = *holder;

	this->GetParent()->GetTransform()->SetRotation(rotation += rotationalVelocity * dt);

	Vector2DScaleAdd(&newVelocity, holdAcceleration, holdVelocity, dt);
	SetVelocity(&newVelocity);

	Vector2DScaleAdd(&newTranslation, &newVelocity, &newTranslation, dt);
	this->GetParent()->GetTransform()->SetTranslation(&newTranslation);
}

void Physics::Draw() const
{

}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

