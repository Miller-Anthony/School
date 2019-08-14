//------------------------------------------------------------------------------
//
// File Name:	GameStatePvPEquip.h
// Author(s):	Anthony Miller (anthony.m)
// Project:		Knightmare
// Course:		CS150S19
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

// Load the resources associated with the PvPEquip game state.
void GameStatePVPEquipLoad();

// Initialize the memory associated with the PvPEquip game state.
void GameStatePVPEquipInit();

// Update the PvPEquip game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStatePVPEquipUpdate(float dt);

// Shutdown any memory associated with the PvPEquip game state.
void GameStatePVPEquipShutdown();

// Unload the resources associated with the PvPEquip game state.
void GameStatePVPEquipUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

