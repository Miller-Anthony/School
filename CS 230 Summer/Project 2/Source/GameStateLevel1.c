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

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int numLives1 = 0;
static AEGfxVertexList * list;
static AEGfxTexture * pTexture;
static SpriteSourcePtr source;
static GameObjectPtr object;


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void GameStateLevel1MovementController(GameObjectPtr gameObject);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateLevel1Load()
{
	Stream stream = StreamOpen(".\\Data\\Level1_Lives.txt");

	numLives1 = StreamReadInt(stream);

	StreamClose(&stream);

	list = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");

	pTexture = AEGfxTextureLoad("./Assets/PlanetTexture.png");
	source = SpriteSourceCreate(1, 1, pTexture);
}

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init()
{
	object = GameObjectFactoryBuild("./Data/PlanetJump.txt");

	if (object)
	{
		SpritePtr holder = GameObjectGetSprite(object);

		SpriteSetMesh(holder, list);
		SpriteSetSpriteSource(holder, source);
	}
	
	AEGfxSetBackgroundColor(1, 1, 1);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel1Update(float dt)
{

	GameStateLevel1MovementController(object);
	GameObjectUpdate(object, dt);
	GameObjectDraw(object);
	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsLevel2);
	}
}

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown()
{
	GameObjectFree(&object);
}

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload()
{
	SpriteSourceFree(&source);
	AEGfxMeshFree(list);
	AEGfxTextureUnload(pTexture);
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
			}
			else if (AEInputCheckCurr(VK_RIGHT))
			{
				velocity.x = moveVelocity;
			}
			else
			{
				velocity.x = 0.0f;
			}

			if (AEInputCheckTriggered(VK_UP))
			{
				velocity.y = jumpVelocity;
				PhysicsSetAcceleration(physics, &gravityNormal);
			}

			if (translation.y < groundHeight)
			{
				translation.y = groundHeight;
				velocity.y = 0;
				PhysicsSetAcceleration(physics, &gravityNone);
				numLives1--;
				//if lives run out switch to the level 2
				if (numLives1 <= 0)
				{
					GameStateManagerSetNextState(GsLevel2);
				}
			}

			TransformSetTranslation(transform, &translation);
			PhysicsSetVelocity(physics, &velocity);
		}
	}
}