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
#include "ScoreSystem.h"
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

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int asteroidSpawnCount;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

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
	ScoreSystemInit();
}

// Initialize the memory associated with the Stub game state.
void GameStateAsteroidsInit()
{
		//Create a spaceship and add it to the active objectlist
	GameObjectPtr spaceship = GameObjectFactoryBuild("Spaceship");
	if (spaceship)
	{
		GameObjectManagerAdd(spaceship);
	}

	 //Create a score and add it to the active objectlist
	GameObjectPtr score = GameObjectFactoryBuild("AsteroidsScore");
	if (score)
	{
		GameObjectManagerAdd(score);
	}

	//Create a high score and add it to the active objectlist
	GameObjectPtr highScore = GameObjectFactoryBuild("AsteroidsHighScore");
	if (highScore)
	{
		GameObjectManagerAdd(highScore);
	}

	//Create a wave count and add it to the active objectlist
	GameObjectPtr wave = GameObjectFactoryBuild("AsteroidsWave");
	if (wave)
	{
		GameObjectManagerAdd(wave);
	}

	AEGfxSetBackgroundColor(0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	asteroidSpawnCount = cAsteroidSpawnInitial;

	ScoreSystemRestart();
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
	else if (AEInputCheckTriggered('4'))
	{
		GameStateManagerSetNextState(GsOmega);
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

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void GameStateAsteroidsSpawnAsteroidWave(void)
{
	ScoreSystemIncreaseWaveCount();
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