//------------------------------------------------------------------------------
//
// File Name:	GameStateWin.h
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

// Load the resources associated with the Win game state.
void GameStateWinLoad();

// Initialize the memory associated with the Win game state.
void GameStateWinInit();

// Update the Win game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateWinUpdate(float dt);

// Shutdown any memory associated with the Win game state.
void GameStateWinShutdown();

// Unload the resources associated with the Win game state.
void GameStateWinUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

