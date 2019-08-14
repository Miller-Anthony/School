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
#include "GameStateManager.h"
#include "GameStateLevel1.h"
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

static int numLives1 = 0;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateLevel1Load()
{
	Stream stream = StreamOpen(".\\Data\\Level1_Lives.txt");

	numLives1 = StreamReadInt(stream);

	StreamClose(&stream);
}

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init()
{
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel1Update(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	--numLives1;
	if (numLives1 <= 0)
	{
		GameStateManagerSetNextState(GsLevel2);
	}
}

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown()
{
}

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload()
{
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

