//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel1.c
// Author(s):	Anthony Miller
// Project:		Project 1
// Course:		CS230SU19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "GameStateLevel1.h"
#include "Stream.h"
#include "Trace.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Mesh.h"
#include "GameObjectFactory.h"
#include "Animation.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };
static const float wallDistance = 350.0f;
static const float CheckSquareDistance = (75.0f * 75.0f);

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef enum MonkeyStates
{
	MonkeyInvalid = -1,
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump
}MonkeyStates;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int numLives1 = 0;
static AEGfxVertexList * unitMesh;
static AEGfxVertexList * threeMesh;
static AEGfxVertexList * textMesh;
static AEGfxTexture * planetTexture;
static AEGfxTexture * pTextureMonkeyIdle;
static AEGfxTexture * pTextureMonkeyWalk;
static AEGfxTexture * pTextureMonkeyJump;
static AEGfxTexture * pTextureFontSheet;
static SpriteSourcePtr planetSource;
static SpriteSourcePtr idleSource;
static SpriteSourcePtr walkSource;
static SpriteSourcePtr jumpSource;
static SpriteSourcePtr fontSource;
static GameObjectPtr planet;
static GameObjectPtr monkey;
static GameObjectPtr text;
static enum MonkeyStates monkeyState = MonkeyInvalid;
static char livesBuffer[16] = "";

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void GameStateLevel1MovementController(GameObjectPtr gameObject);
void GameStateLevel1BounceController(GameObjectPtr gameObject);
void GameStateLevel1SetMonkeyState(GameObjectPtr gameObject, MonkeyStates newState);
bool GameStateLevel1IsColliding(GameObjectPtr objectA, GameObjectPtr objectB);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateLevel1Load()
{
	Stream stream = StreamOpen(".\\Data\\Level1_Lives.txt");

	numLives1 = StreamReadInt(stream);

	StreamClose(&stream);

	unitMesh = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	threeMesh = MeshCreateQuad(0.5, 0.5, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	textMesh = MeshCreateQuad(0.5, 0.5, 1.0f / 16, 1.0f / 6, "Mesh16x6");

	planetTexture = AEGfxTextureLoad("./Assets/PlanetTexture.png");
	pTextureMonkeyIdle = AEGfxTextureLoad("Assets/MonkeyIdle.png");
	pTextureMonkeyWalk = AEGfxTextureLoad("Assets/MonkeyWalk.png");
	pTextureMonkeyJump = AEGfxTextureLoad("Assets/MonkeyJump.png");
	pTextureFontSheet = AEGfxTextureLoad("Assets/FontSheet.png");

	planetSource = SpriteSourceCreate(1, 1, planetTexture);
	idleSource = SpriteSourceCreate(1, 1, pTextureMonkeyIdle);
	walkSource = SpriteSourceCreate(3, 3, pTextureMonkeyWalk);
	jumpSource = SpriteSourceCreate(1, 1, pTextureMonkeyJump);
	fontSource = SpriteSourceCreate(16, 6, pTextureFontSheet);
}

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init()
{
	planet = GameObjectFactoryBuild("PlanetBounce");
	monkey = GameObjectFactoryBuild("Monkey");
	text = GameObjectFactoryBuild("MonkeyLivesText");

	if (planet)
	{
		SpritePtr holder = GameObjectGetSprite(planet);

		SpriteSetMesh(holder, unitMesh);
		SpriteSetSpriteSource(holder, planetSource);
	}

	if (monkey)
	{
		monkeyState = MonkeyInvalid;
		GameStateLevel1SetMonkeyState(monkey, MonkeyIdle);
	}

	if (text)
	{
		SpritePtr textSprite = GameObjectGetSprite(text);

		SpriteSetMesh(textSprite, textMesh);
		SpriteSetSpriteSource(textSprite, fontSource);

		sprintf_s(livesBuffer, 16, "lives: %d", numLives1);

		SpriteSetText(textSprite, livesBuffer);
	}

	AEGfxSetBackgroundColor(1, 1, 1);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel1Update(float dt)
{

	GameStateLevel1MovementController(monkey);
	GameStateLevel1BounceController(planet);

	GameObjectUpdate(planet, dt);
	GameObjectUpdate(monkey, dt);
	GameObjectUpdate(text, dt);

	GameObjectDraw(planet);
	GameObjectDraw(monkey);
	GameObjectDraw(text);

	if (GameStateLevel1IsColliding(monkey, planet))
	{
		numLives1--;

		if (numLives1 <= 0)
		{
			GameStateManagerSetNextState(GsLevel2);
		}
		else
		{
			GameStateManagerSetNextState(GsRestart);
		}
	}

	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsLevel2);
	}
	else if (AEInputCheckTriggered('3'))
	{
		GameStateManagerSetNextState(GsAsteroids);
	}
}

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown()
{
	GameObjectFree(&text);
	GameObjectFree(&monkey);
	GameObjectFree(&planet);
}

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload()
{
	SpriteSourceFree(&fontSource);
	SpriteSourceFree(&jumpSource);
	SpriteSourceFree(&walkSource);
	SpriteSourceFree(&idleSource);
	SpriteSourceFree(&planetSource);

	AEGfxTextureUnload(pTextureFontSheet);
	AEGfxTextureUnload(pTextureMonkeyJump);
	AEGfxTextureUnload(pTextureMonkeyWalk);
	AEGfxTextureUnload(pTextureMonkeyIdle);
	AEGfxTextureUnload(planetTexture);

	AEGfxMeshFree(textMesh);
	AEGfxMeshFree(threeMesh);
	AEGfxMeshFree(unitMesh);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void GameStateLevel1MovementController(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		PhysicsPtr physics = GameObjectGetPhysics(gameObject);
		TransformPtr transform = GameObjectGetTransform(gameObject);

		if (physics && transform)
		{
			Vector2D velocity = *PhysicsGetVelocity(physics);
			Vector2D translation = *TransformGetTranslation(transform);

			if (AEInputCheckCurr(VK_LEFT))
			{
				velocity.x = -moveVelocity;

				if (monkeyState != MonkeyJump)
				{
					GameStateLevel1SetMonkeyState(gameObject, MonkeyWalk);
				}
			}
			else if (AEInputCheckCurr(VK_RIGHT))
			{
				velocity.x = moveVelocity;

				if (monkeyState != MonkeyJump)
				{
					GameStateLevel1SetMonkeyState(gameObject, MonkeyWalk);
				}
			}
			else
			{
				velocity.x = 0.0f;

				if (monkeyState != MonkeyJump)
				{
					GameStateLevel1SetMonkeyState(gameObject, MonkeyIdle);
				}
			}

			if (AEInputCheckTriggered(VK_UP))
			{
				velocity.y = jumpVelocity;
				PhysicsSetAcceleration(physics, &gravityNormal);
				GameStateLevel1SetMonkeyState(gameObject, MonkeyJump);
			}

			if (translation.y < groundHeight)
			{
				translation.y = groundHeight;
				velocity.y = 0;
				PhysicsSetAcceleration(physics, &gravityNone);

				GameStateLevel1SetMonkeyState(gameObject, MonkeyIdle);
			}

			TransformSetTranslation(transform, &translation);
			PhysicsSetVelocity(physics, &velocity);
		}
	}
}

void GameStateLevel1BounceController(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		PhysicsPtr physics = GameObjectGetPhysics(gameObject);
		TransformPtr transform = GameObjectGetTransform(gameObject);

		if (physics && transform)
		{
			Vector2D position = *TransformGetTranslation(transform);
			Vector2D velocity = *PhysicsGetVelocity(physics);

			if (position.x <= -wallDistance)
			{
				position.x = -wallDistance;
				velocity.x = -velocity.x;
			}

			if (position.x >= wallDistance)
			{
				position.x = wallDistance;
				velocity.x = -velocity.x;
			}

			if (position.y <= groundHeight)
			{
				position.y = groundHeight + (groundHeight - position.y);
				velocity.y = -velocity.y;
			}

			TransformSetTranslation(transform, &position);
			PhysicsSetVelocity(physics, &velocity);
		}
	}
}

void GameStateLevel1SetMonkeyState(GameObjectPtr gameObject, MonkeyStates newState)
{
	if (monkeyState != newState)
	{
		SpritePtr sprite = GameObjectGetSprite(gameObject);
		AnimationPtr animation = GameObjectGetAnimation(gameObject);

		monkeyState = newState;

		switch (newState)
		{
		case MonkeyIdle:
			SpriteSetMesh(sprite, unitMesh);
			SpriteSetSpriteSource(sprite, idleSource);
			AnimationPlay(animation, 1, 0.0f, false);
			break;

		case MonkeyWalk:
			SpriteSetMesh(sprite, threeMesh);
			SpriteSetSpriteSource(sprite, walkSource);
			AnimationPlay(animation, 8, 0.05f, true);
			break;

		case MonkeyJump:
			SpriteSetMesh(sprite, unitMesh);
			SpriteSetSpriteSource(sprite, jumpSource);
			AnimationPlay(animation, 1, 0.0f, false);
			break;
		}
	}
}

bool GameStateLevel1IsColliding(GameObjectPtr objectA, GameObjectPtr objectB)
{
	if (objectA && objectB)
	{
		Vector2D positionA = *TransformGetTranslation(GameObjectGetTransform(objectA));
		Vector2D positionB = *TransformGetTranslation(GameObjectGetTransform(objectB));

		float distance = Vector2DSquareDistance(&positionA, &positionB);

		if (distance < CheckSquareDistance)
		{
			return true;
		}
	}
	return false;
}