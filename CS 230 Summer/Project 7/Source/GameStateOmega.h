//------------------------------------------------------------------------------
//
// File Name:	GameStateOmega.h
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

// Load the resources associated with the Stub game state.
	void GameStateOmegaLoad();

	// Initialize the memory associated with the Stub game state.
	void GameStateOmegaInit();

	// Update the GameStateOmegaUpdate game state.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void GameStateOmegaUpdate(float dt);

	// Shutdown any memory associated with the Stub game state.
	void GameStateOmegaShutdown();

	// Unload the resources associated with the Stub game state.
	void GameStateOmegaUnload();

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

