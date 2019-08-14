//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <AEEngine.h>
#include "Physics.h"
#include "Vector2D.h"
#include "Transform.h"
#include "BehaviorSpaceship.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "Behavior.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const float spaceshipAcceleration = 150.0f;
static const float spaceshipSpeedMax = 500.0f;
static const float spaceshipTurnRateMax = PI / 1.5f;
static const float spaceshipWeaponCooldownTime = 0.034f;
static const float spaceshipWeaponBulletSpeed = 750.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef enum ShipStates
{
	cSpaceshipInvalid = -1,
	cSpaceshipIdle,
	cSpaceshipThrust
} ShipStates;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorSpaceshipUpdateRotation(BehaviorPtr behavior, float dt);
static void BehaviorSpaceshipUpdateVelocity(BehaviorPtr behavior, float dt);
static void BehaviorSpaceshipUpdateWeapon(BehaviorPtr behavior, float dt);
static void BehaviorSpaceshipSpawnBullet(BehaviorPtr behavior);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Dynamically allocate a new (Spaceship) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorSpaceshipCreate(void)
{
	BehaviorPtr holder = calloc(1, sizeof(Behavior));
	if (holder)
	{
		holder->stateCurr = cSpaceshipInvalid;
		holder->stateNext = cSpaceshipInvalid;
		holder->onInit = BehaviorSpaceshipInit;
		holder->onUpdate = BehaviorSpaceshipUpdate;
		holder->onExit = BehaviorSpaceshipExit;
	}
	return holder;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorSpaceshipInit(BehaviorPtr behavior)
{
	behavior;
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorSpaceshipUpdate(BehaviorPtr behavior, float dt)
{
	switch (behavior->stateCurr)
	{
	case cSpaceshipIdle:
		BehaviorSpaceshipUpdateRotation(behavior, dt);
		BehaviorSpaceshipUpdateWeapon(behavior, dt);

		if (AEInputCheckCurr(VK_UP))
		{
			behavior->stateNext = cSpaceshipThrust;
		}
		break;
	case cSpaceshipThrust:
		BehaviorSpaceshipUpdateRotation(behavior, dt);
		BehaviorSpaceshipUpdateVelocity(behavior, dt);
		BehaviorSpaceshipUpdateWeapon(behavior, dt);

		if (AEInputCheckReleased(VK_UP))
		{
			behavior->stateNext = cSpaceshipIdle;
		}
		break;
	}
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorSpaceshipExit(BehaviorPtr behavior)
{
	behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorSpaceshipUpdateRotation(BehaviorPtr behavior, float dt)
{
	if (AEInputCheckCurr(VK_LEFT))
	{
		PhysicsSetRotationalVelocity(GameObjectGetPhysics(behavior->parent), spaceshipTurnRateMax);
	}
	else if (AEInputCheckCurr(VK_RIGHT))
	{
		PhysicsSetRotationalVelocity(GameObjectGetPhysics(behavior->parent), -spaceshipTurnRateMax);
	}
	else
	{
		PhysicsSetRotationalVelocity(GameObjectGetPhysics(behavior->parent), 0);
	}
	dt;
}

static void BehaviorSpaceshipUpdateVelocity(BehaviorPtr behavior, float dt)
{
	TransformPtr holdTransform = GameObjectGetTransform(behavior->parent);
	PhysicsPtr holdPhysics = GameObjectGetPhysics(behavior->parent);

	if (holdTransform && holdPhysics)
	{
		float speed = 0;
		float rotation = TransformGetRotation(holdTransform);
		Vector2D angleHolder = { 0, 0 };
		const Vector2D *velHolder = PhysicsGetVelocity(holdPhysics);
		Vector2D newVel = { 0, 0 };

		Vector2DFromAngleRad(&angleHolder, rotation);

		Vector2DScaleAdd(&newVel, &angleHolder, velHolder, spaceshipAcceleration * dt);

		speed = Vector2DLength(&newVel);
		if (speed > spaceshipSpeedMax)
		{
			newVel.x *= (spaceshipSpeedMax / speed);
			newVel.y *= (spaceshipSpeedMax / speed);
		}

		PhysicsSetVelocity(holdPhysics, &newVel);
	}
}

static void BehaviorSpaceshipUpdateWeapon(BehaviorPtr behavior, float dt)
{
	if (behavior->timer > 0)
	{
		behavior->timer -= dt;

		if (behavior->timer < 0)
		{
			behavior->timer = 0;
		}
	}

	if (AEInputCheckCurr(' '))
	{
		if (behavior->timer <= 0)
		{
			BehaviorSpaceshipSpawnBullet(behavior);
			behavior->timer = spaceshipWeaponCooldownTime;
		}
	}
}

static void BehaviorSpaceshipSpawnBullet(BehaviorPtr behavior)
{
	GameObjectPtr objHolder = GameObjectFactoryBuild("Bullet");

	if (objHolder)
	{
		//get the transform of the ship for bullet rotation and position
		TransformPtr holdTransform = GameObjectGetTransform(behavior->parent);
		float rotation = TransformGetRotation(holdTransform);
		const Vector2D *position = TransformGetTranslation(holdTransform);

		Vector2D direction; //holder for the new bullet direction
		Vector2D velocity;  //holder for the new bullet velocity

		//set the cloned bullets position and rotation
		TransformSetRotation(GameObjectGetTransform(objHolder), rotation);
		TransformSetTranslation(GameObjectGetTransform(objHolder), position);

		Vector2DFromAngleRad(&direction, rotation);
		Vector2DScale(&velocity, &direction, spaceshipWeaponBulletSpeed);

		PhysicsSetVelocity(GameObjectGetPhysics(objHolder), &velocity);

		GameObjectManagerAdd(objHolder);
	}
}