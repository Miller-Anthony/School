//------------------------------------------------------------------------------
//
// File Name:	GameStateTown.h
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

// Load the resources associated with the Town game state.
void GameStateTownLoad();

// Initialize the memory associated with the Town game state.
void GameStateTownInit();

// Update the Town game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateTownUpdate(float dt);

// Shutdown any memory associated with the Town game state.
void GameStateTownShutdown();

// Unload the resources associated with the Town game state.
void GameStateTownUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

