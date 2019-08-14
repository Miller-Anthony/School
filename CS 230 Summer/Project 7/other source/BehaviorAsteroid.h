//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.h
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

typedef struct Behavior * BehaviorPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

// An example of the enums to be defined in BehaviorAsteroid.c.
#if 0
typedef enum
{
	cAsteroidLarge,
	cAsteroidMedium,
	cAsteroidSmall,

} AsteroidSize;

typedef enum
{
	cAsteroidOriginTlc,
	cAsteroidOriginTrc,
	cAsteroidOriginBlc,
	cAsteroidOriginBrc,
	cAsteroidOriginCount,

} AsteroidOrigin;
#endif

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in BehaviorAsteroid.c.
#if 0
typedef struct BehaviorAsteroid
{
	// Inherit the base behavior structure.
	Behavior	base;

	// Add asteroid-specific behavior variables.
	AsteroidSize	size;
	AsteroidOrigin	origin;

} BehaviorAsteroid, *BehaviorAsteroidPtr;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Asteroid) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorAsteroidCreate(void);

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorAsteroidInit(BehaviorPtr behavior);

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorAsteroidUpdate(BehaviorPtr behavior, float dt);

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorAsteroidExit(BehaviorPtr behavior);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

