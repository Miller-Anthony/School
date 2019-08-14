//------------------------------------------------------------------------------
//
// File Name:	GameStateTutorial.h
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

// Load the resources associated with the Tutorial game state.
void GameStateTutorialLoad();

// Initialize the memory associated with the Tutorial game state.
void GameStateTutorialInit();

// Update the Tutorial game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateTutorialUpdate(float dt);

// Shutdown any memory associated with the Tutorial game state.
void GameStateTutorialShutdown();

// Unload the resources associated with the Tutorial game state.
void GameStateTutorialUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

