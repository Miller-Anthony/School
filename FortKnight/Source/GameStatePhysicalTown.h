//------------------------------------------------------------------------------
//
// File Name:	GameStatePhysicalTown.h
// Author(s):	Dieter Voegels
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

// Load the resources associated with the PhysicalTown game state.
void GameStatePhysicalTownLoad();

// Initialize the memory associated with the PhysicalTown game state.
void GameStatePhysicalTownInit();

// Update the PhysicalTown game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStatePhysicalTownUpdate(float dt);

// Shutdown any memory associated with the PhysicalTown game state.
void GameStatePhysicalTownShutdown();

// Unload the resources associated with the PhysicalTown game state.
void GameStatePhysicalTownUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

