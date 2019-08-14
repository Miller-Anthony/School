//------------------------------------------------------------------------------
//
// File Name:	GameStateBattleRoyale.h
// Author(s):	Brayan Lopez
// Project:		Knightmare
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
void GameStateBattleRoyaleLoad();

// Initialize the memory associated with the Stub game state.
void GameStateBattleRoyaleInit();

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateBattleRoyaleUpdate(float dt);

// Shutdown any memory associated with the Stub game state.
void GameStateBattleRoyaleShutdown();

// Unload the resources associated with the Stub game state.
void GameStateBattleRoyaleUnload();
//queue a kill up to be displayed as kill feed
void QueueKill(const char* killer, const char* dead);
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

