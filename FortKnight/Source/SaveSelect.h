//------------------------------------------------------------------------------
//
// File Name:	SaveSelect.h
// Author(s):	Akshat Madan
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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Load the resources associated with the Level2 game state.
void SaveSelectLoad();

// Initialize the memory associated with the Level2 game state.
void SaveSelectInit();

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SaveSelectUpdate(float dt);

// Shutdown any memory associated with the Level2 game state.
void SaveSelectShutdown();

// Unload the resources associated with the Level2 game state.
void SaveSelectUnload();

void SaveSelectContinue(void);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

