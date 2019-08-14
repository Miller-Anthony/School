//------------------------------------------------------------------------------
//
// File Name:	GameStateStatement.h
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
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

// Load the resources associated with the Statement game state.
void GameStateStatementLoad();

// Initialize the memory associated with the Statement game state.
void GameStateStatementInit();

// Update the Statement game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateStatementUpdate(float dt);

// Shutdown any memory associated with the Statement game state.
void GameStateStatementShutdown();

// Unload the resources associated with the Statement game state.
void GameStateStatementUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

