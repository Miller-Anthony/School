//------------------------------------------------------------------------------
//
// File Name:	GameStateLose.h
// Author(s):	Dieter Voegels
// Project:		Knightmare
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

// Load the resources associated with the Lose game state.
void GameStateLoseLoad();

// Initialize the memory associated with the Lose game state.
void GameStateLoseInit();

// Update the Lose game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLoseUpdate(float dt);

// Shutdown any memory associated with the Lose game state.
void GameStateLoseShutdown();

// Unload the resources associated with the Lose game state.
void GameStateLoseUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

