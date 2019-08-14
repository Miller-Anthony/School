//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel1.h
// Author(s):	Anthony Miller
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

#include "Objects.h"

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

typedef enum Bosses
{
    SerScatterfoot,
    BaronDeEvidance,
    SVEN,
    BossesMax
}Bosses;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static ObjectPtr CreateHealthText(const float x, const float y, const float w, const float h);
static PlayerPtr CreateCharacter();
static EnemyPtr CreateEnemyChar();



//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateLevel1Load();

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init();

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel1Update(float dt);

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown();

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

