//------------------------------------------------------------------------------
//
// File Name:	GameStatePvPEquip.c
// Author(s):	Anthony Miller(anthony.m)
// Project:		Knightmare
// Course:		CS150S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStatePvPEquip.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the PvPEquip game state.
void GameStatePVPEquipLoad()
{
}

// Initialize the memory associated with the PvPEquip game state.
void GameStatePVPEquipInit()
{
}

// Update the PvPEquip game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStatePVPEquipUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	GameStateManagerSetNextState(GsQuit);
}

// Free any memory associated with the PvPEquip game state.
void GameStatePVPEquipShutdown()
{
	// Free all objects.
}

// Unload the resources associated with the PvPEquip game state.
void GameStatePVPEquipUnload()
{
	// Free all sprite sources.

	// Unload all textures.

	// Free all meshes.
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

