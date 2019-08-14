//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel2.h
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19-A
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
	typedef enum Prog
	{
		Start = 0,
		Secnd = 2,
		Third = 5
	} Prog;

	typedef enum Unlock
	{
		unlock1 = 1,
		unlock2 = 2,
		unlock3 = 3
	} Unlock;
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Set the selection panel for Level2.
void SetSelect();

// Load the resources associated with the Level2 game state.
void GameStateLevel2Load();

// Initialize the memory associated with the Level2 game state.
void GameStateLevel2Init();

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel2Update(float dt);

// Shutdown any memory associated with the Level2 game state.
void GameStateLevel2Shutdown();

// Unload the resources associated with the Level2 game state.
void GameStateLevel2Unload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

