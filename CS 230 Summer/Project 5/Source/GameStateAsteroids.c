//------------------------------------------------------------------------------
//
// File Name:	GameStateAsteroids.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "GameStateAsteroids.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "BehaviorHudText.h"
#include "SpriteSourceManager.h"
#include "MeshManager.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const int cAsteroidSpawnInitial = 8;
static const int cAsteroidSpawnMaximum = 20;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

static int asteroidScore = 0;
static int asteroidHighScore = 0;
static int asteroidSpawnCount;
static int asteroidWaveCount;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void GameStateAsteroidsCreateHudElement(const char * objectName, const char * formatString, const int * watchValue);
static void GameStateAsteroidsSpawnAsteroidWave(void);
static void GameStateAsteroidsSpawnAsteroid(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateAsteroidsLoad()
{
	MeshManagerInit();
	SpriteSourceManagerInit();
}

// Initialize the memory associated with the Stub game state.
void GameStateAsteroidsInit()
{
	GameObjectPtr spaceship = GameObjectFactoryBuild("Spaceship");
	GameStateAsteroidsCreateHudElement("AsteroidsHighScore", "High Score: %d", &asteroidHighScore);
	GameStateAsteroidsCreateHudElement("AsteroidsScore", "Score: %d", &asteroidScore);
	GameStateAsteroidsCreateHudElement("AsteroidsWave", "Wave: %d", &asteroidWaveCount);

	if (spaceship)
	{
		GameObjectManagerAdd(spaceship);
	}

	AEGfxSetBackgroundColor(0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	asteroidSpawnCount = cAsteroidSpawnInitial;

	if (asteroidHighScore < asteroidScore)
	{
		asteroidHighScore = asteroidScore;
	}
	asteroidScore = 0;
	asteroidWaveCount = 0;
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateAsteroidsUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	if (!GameObjectManagerGetObjectByName("Asteroid"))
	{
       		GameStateAsteroidsSpawnAsteroidWave();
	}

	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsLevel1);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsLevel2);
	}
	else if (AEInputCheckTriggered('3'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
}

// Shutdown any memory associated with the Stub game state.
void GameStateAsteroidsShutdown()
{
	GameObjectManagerShutdown();
}

// Unload the resources associated with the Stub game state.
void GameStateAsteroidsUnload()
{
	MeshManagerFreeAll();
	SpriteSourceManagerFreeAll();
}

void GameStateAsteroidsIncreaseScore()
{
	asteroidScore += 20;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void GameStateAsteroidsCreateHudElement(const char * objectName, const char * formatString, const int * watchValue)
{
	GameObjectPtr holder = GameObjectFactoryBuild(objectName);

	BehaviorPtr behavior = GameObjectGetBehavior(holder);

	BehaviorHudTextSetDisplay(behavior, formatString, watchValue);

	GameObjectManagerAdd(holder);
}

static void GameStateAsteroidsSpawnAsteroidWave(void)
{
	asteroidWaveCount++;
	for (int i = 0; i < asteroidSpawnCount; i++)
	{
		GameStateAsteroidsSpawnAsteroid();
	}
	if (asteroidSpawnCount < cAsteroidSpawnMaximum)
	{
		asteroidSpawnCount++;
	}
}

static void GameStateAsteroidsSpawnAsteroid(void)
{
	GameObjectManagerAdd(GameObjectFactoryBuild("Asteroid"));
}