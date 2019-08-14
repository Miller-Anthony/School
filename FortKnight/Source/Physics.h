//------------------------------------------------------------------------------
//
// File Name:	Physics.h
// Author(s):	Dieter Voegels
// Project:		Knightmare
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

typedef struct Transform* TransformPtr;
typedef struct AEVec2 AEVec2;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct Physics* PhysicsPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new physics component.
PhysicsPtr PhysicsCreate(void);

// Free the memory associated with a physics component.
void PhysicsFree(PhysicsPtr * physics);

// Get the acceleration of a physics component.
AEVec2* PhysicsGetAcceleration(PhysicsPtr physics);

// Get the velocity of a physics component.
AEVec2* PhysicsGetVelocity(PhysicsPtr physics);

// Get the old translation (position) of a physics component.
AEVec2* PhysicsGetOldTranslation(PhysicsPtr physics);

// Set the acceleration of a physics component.
void PhysicsSetAcceleration(PhysicsPtr physics, AEVec2* acceleration);

// Set the velocity of a physics component.
void PhysicsSetVelocity(PhysicsPtr physics, AEVec2* velocity);

// Update the state of a physics component.
void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

