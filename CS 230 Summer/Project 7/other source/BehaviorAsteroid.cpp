//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "ScoreSystem.h"
#include "GameObject.h"
#include "Teleporter.h"
#include "Transform.h"
#include "Random.h"
#include "Collider.h"
#include "Physics.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

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

typedef enum
{
	cAsteroidInvalid = -1,
	cAsteroidIdle,
} AsteroidState;

// Speed range of the asteroids.
static const float asteroidSpeedMin = 50.0f;
static const float asteroidSpeedMax = 100.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BehaviorAsteroid
{
	// Inherit the base behavior structure.
	Behavior	base;

	// Add asteroid-specific behavior variables.
	AsteroidSize	size;
	AsteroidOrigin	origin;

} BehaviorAsteroid, *BehaviorAsteroidPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorAsteroidSetPosition(BehaviorAsteroidPtr behavior);
static void BehaviorAsteroidSetVelocity(BehaviorAsteroidPtr behavior);
static void BehaviorAsteroidCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Asteroid) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorAsteroidCreate(void)
{
	BehaviorAsteroidPtr holder = calloc(1, sizeof(BehaviorAsteroid));

	if (holder)
	{
		holder->base.stateCurr = cAsteroidInvalid;
		holder->base.stateNext = cAsteroidIdle;
		holder->base.onInit = BehaviorAsteroidInit;
		holder->base.onUpdate = BehaviorAsteroidUpdate;
		holder->base.onExit = BehaviorAsteroidExit;
		holder->base.memorySize = sizeof(BehaviorAsteroid);
		holder->size = cAsteroidLarge;
	}

	return (BehaviorPtr)holder;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorAsteroidInit(BehaviorPtr behavior)
{
	if (behavior)
	{
		BehaviorAsteroidPtr holder = (BehaviorAsteroidPtr)behavior;
		if (holder->base.stateCurr == cAsteroidIdle)
		{
			ColliderPtr holdCollider = GameObjectGetCollider(holder->base.parent);

			holder->origin = RandomRange(0, 3);
			BehaviorAsteroidSetPosition(holder);
			BehaviorAsteroidSetVelocity(holder);

			if (holdCollider)
			{
				ColliderSetCollisionHandler(holdCollider, BehaviorAsteroidCollisionHandler);
			}
		}
	}
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorAsteroidUpdate(BehaviorPtr behavior, float dt)
{
	if (behavior)
	{
		switch (behavior->stateCurr)
		{
		case cAsteroidIdle:
			dt;
			break;
		}
		TeleporterUpdateObject(behavior->parent);
	}
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorAsteroidExit(BehaviorPtr behavior)
{
	behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorAsteroidSetPosition(BehaviorAsteroidPtr behavior)
{
	if (behavior)
	{
		if (behavior->size == cAsteroidLarge)
		{
			//check transform to see where position values are coming from
			TransformPtr holdTrans = GameObjectGetTransform(behavior->base.parent);
			Vector2D pos = { 0,0 };

			switch (behavior->origin)
			{
			case cAsteroidOriginTlc:
				pos.x = -((float)AEGfxGetWinMaxX() - 20);
				pos.y = ((float)AEGfxGetWinMaxY() - 20);
				break;

			case cAsteroidOriginTrc:
				pos.x = ((float)AEGfxGetWinMaxX() - 20);
				pos.y = (float)AEGfxGetWinMaxY() - 20;
				break;

			case cAsteroidOriginBlc:
				pos.x = -((float)AEGfxGetWinMaxX() - 20);
				pos.y = -((float)AEGfxGetWinMaxY() - 20);
				break;

			case cAsteroidOriginBrc:
				pos.x = (float)AEGfxGetWinMaxX() - 20;
				pos.y = -((float)AEGfxGetWinMaxY() - 20);
				break;
			}
			TransformSetTranslation(holdTrans, &pos);
		}
	}
}

static void BehaviorAsteroidSetVelocity(BehaviorAsteroidPtr behavior)
{
	if (behavior)
	{
		float angle = 0;
		Vector2D direction = { 0, 0 };
		PhysicsPtr holdPhysics = GameObjectGetPhysics(behavior->base.parent);

		if (behavior->size == cAsteroidLarge)
		{
			switch (behavior->origin)
			{
			case cAsteroidOriginTlc:
				angle = RandomRangeFloat(-10, -80);
				break;

			case cAsteroidOriginTrc:
				angle = RandomRangeFloat(-100, -170);
				break;

			case cAsteroidOriginBlc:
				angle = RandomRangeFloat(10, 80);
				break;

			case cAsteroidOriginBrc:
				//rand range float is worng
				angle = RandomRangeFloat(100, 170);
				break;
			}
		}
		if (behavior->size == cAsteroidMedium || behavior->size == cAsteroidSmall)
		{
			angle = RandomRangeFloat(0, 359);
		}
		Vector2DFromAngleDeg(&direction, angle);

		//put the speed min and speed max into a vec to make sure it is correct with the rand
		Vector2DScale(&direction, &direction, RandomRangeFloat(asteroidSpeedMin, asteroidSpeedMax));

		PhysicsSetVelocity(holdPhysics, &direction);
	}
}

static void BehaviorAsteroidCollisionHandler(GameObjectPtr gameObject1, GameObjectPtr gameObject2)
{
	if (gameObject1 && gameObject2)
	{
		if (!strcmp(GameObjectGetName(gameObject2), "Spaceship") || !strcmp(GameObjectGetName(gameObject2), "Bullet"))
		{
			ScoreSystemIncreaseScore(20);
			GameObjectDestroy(gameObject1);
		}
	}
}