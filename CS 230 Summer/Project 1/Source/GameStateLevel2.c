//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel2.c
// Author(s):	Anthony Miller
// Project:		Project 1
// Course:		CS230SU19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateLevel2.h"
#include "Stream.h"
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

static int numLives = 0;
static int numHealth = 0;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level2 game state.
void GameStateLevel2Load()
{
	Stream stream = StreamOpen(".\\Data\\Level2_Lives.txt");

	numLives = StreamReadInt(stream);

	StreamClose(&stream);
}

// Initialize the memory associated with the Level2 game state.
void GameStateLevel2Init()
{
	Stream stream = StreamOpen(".\\Data\\Level2_Health.txt");

	numHealth = StreamReadInt(stream);

	StreamClose(&stream);
}

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel2Update(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	--numHealth;

	if (numHealth <= 0)
	{
		--numLives;

		if (numLives <= 0)
		{
			GameStateManagerSetNextState(GsQuit);
		}
		else
		{
			GameStateManagerSetNextState(GsRestart);
		}
	}
}

// Shutdown any memory associated with the Level2 game state.
void GameStateLevel2Shutdown()
{
}

// Unload the resources associated with the Level2 game state.
void GameStateLevel2Unload()
{
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

