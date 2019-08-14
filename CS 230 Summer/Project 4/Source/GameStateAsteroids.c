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
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "MeshManager.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateAsteroidsLoad()
{
	MeshManagerInit();
}

// Initialize the memory associated with the Stub game state.
void GameStateAsteroidsInit()
{
	GameObjectPtr spaceship = GameObjectFactoryBuild("Spaceship");

	if (spaceship)
	{
		GameObjectManagerAdd(spaceship);
	}

	AEGfxSetBackgroundColor(0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateAsteroidsUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

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
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

