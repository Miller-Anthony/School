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
#include "Teleporter.h"
#include "BehaviorSpaceship.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"
#include "GameObjectFactory.h"
#include "GameStateTable.h"
#include "Behavior.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const float spaceshipAcceleration = 150.0f;
static const float spaceshipSpeedMax = 500.0f;
static const float spaceshipTurnRateMax = PI / 1.5f;
static const float spaceshipWeaponCooldownTime = 0.25f;
static const float spaceshipWeaponBulletSpeed = 750.0f;
static const float spaceshipDeathDuration = 3.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef enum ShipStates
{
	cSpaceshipInvalid = -1,
	cSpaceshipIdle,
	cSpaceshipThrust,
	cSpaceshipDead
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
static void BehaviorSpaceshipCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2);
static void SpaceshipDeath(GameObjectPtr object);

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
		holder->memorySize = sizeof(Behavior);
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
	if (behavior->stateCurr == cSpaceshipIdle)
	{
		ColliderPtr holder = GameObjectGetCollider(behavior->parent);
		if (holder)
		{
			ColliderSetCollisionHandler(holder, BehaviorSpaceshipCollisionHandler);
		}
	}

	if (behavior->stateCurr == cSpaceshipDead)
	{
		behavior->timer = spaceshipDeathDuration;
		SpaceshipDeath(behavior->parent);
	}
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
	case cSpaceshipDead:
		behavior->timer -= dt;

		if (behavior->timer < 0)
		{
			GameStateManagerSetNextState(GsRestart);
		}

		SpaceshipDeath(behavior->parent);
		break;
	}
	TeleporterUpdateObject(behavior->parent);
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

static void BehaviorSpaceshipCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2)
{
	if (gameObject1 && gameObject2)
	{
		if (!strcmp(GameObjectGetName(gameObject2), "Asteroid"))
		{
			BehaviorPtr holder = GameObjectGetBehavior(gameObject1);
			holder->stateNext = cSpaceshipDead;
		}
	}
}

static void SpaceshipDeath(GameObjectPtr object)
{
	TransformPtr holdTransform = GameObjectGetTransform(object);
	const Vector2D *oldScale = TransformGetScale(holdTransform);
	Vector2D newScale = { 0, 0 };
	float rotation = TransformGetRotation(holdTransform);

	newScale.x = oldScale->x * 0.98f;
	newScale.y = oldScale->y * 0.98f;
	
	if (rotation == 0)
	{
		rotation = 10;
	}
	rotation *= 1.01f;

	TransformSetScale(holdTransform, &newScale);
	TransformSetRotation(holdTransform, rotation);
}