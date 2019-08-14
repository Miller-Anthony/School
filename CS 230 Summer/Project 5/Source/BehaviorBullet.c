//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorBullet.h"
#include "GameObject.h"
#include "Teleporter.h"
#include "Behavior.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

// Maximum speed of the bullet.
static const float bulletSpeedMax = 500.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef enum bulletState
{
	cBulletInvalid = -1,
	cBulletIdle
} bulletState;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorBulletUpdateLifeTimer(BehaviorPtr behavior, float dt);
static void BehaviorBulletCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Bullet) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorBulletCreate(void)
{
	BehaviorPtr holder = calloc(1, sizeof(Behavior));
	if (holder)
	{
		holder->memorySize = sizeof(Behavior);
		holder->stateCurr = cBulletInvalid;
		holder->stateNext = cBulletInvalid;
		holder->onInit = BehaviorBulletInit;
		holder->onUpdate = BehaviorBulletUpdate;
		holder->onExit = BehaviorBulletExit;
	}
	return holder;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorBulletInit(BehaviorPtr behavior)
{
	if (behavior->stateCurr == cBulletIdle)
	{
		ColliderPtr holder = GameObjectGetCollider(behavior->parent);

		if (holder)
		{
			ColliderSetCollisionHandler(holder, BehaviorBulletCollisionHandler);
		}
	}
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorBulletUpdate(BehaviorPtr behavior, float dt)
{
	switch (behavior->stateCurr)
	{
	case cBulletIdle:
		BehaviorBulletUpdateLifeTimer(behavior, dt);
	}
	TeleporterUpdateObject(behavior->parent);
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorBulletExit(BehaviorPtr behavior)
{
	behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorBulletUpdateLifeTimer(BehaviorPtr behavior, float dt)
{
	if (behavior->timer > 0)
	{
		behavior->timer -= dt;

		if (behavior->timer <= 0)
		{
			GameObjectDestroy(behavior->parent);
		}
	}
}

void BehaviorBulletCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2)
{
	if (gameObject1 && gameObject2)
	{
		if (!strcmp(GameObjectGetName(gameObject2), "Asteroid"))
		{
			GameObjectDestroy(gameObject1);
		}
	}
}