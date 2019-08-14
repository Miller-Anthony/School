//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel1.h
// Author(s):	Anthony Miller
// Project:		Project 1
// Course:		CS230SU19
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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateLevel1Load();

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init();

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel1Update(float dt);

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown();

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

