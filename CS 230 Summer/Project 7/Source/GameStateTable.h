//------------------------------------------------------------------------------
//
// File Name:	GameStateTable.h
// Author(s):	Doug Schilling (dschilling)
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

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum
{
	/* Special Game States */
	GsQuit = -3,
	GsRestart = -2,
	GsInvalid = -1,

	/* Normal Game States: */
	GsLevel1,
	GsLevel2,
	//GsAsteroids,
	//GsOmega,

	/* Bookkeeping States: */
	GsNum,
	GsLast = GsNum - 1,

	/* Specify the initial game state */
	GsInitial = GsLevel1,

} GameStates;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Determine if the game state is valid.
bool GameStateIsValid(GameStates gameState);

// Determine if the game state is a "special" game state.
bool GameStateIsSpecial(GameStates gameState);

// Execute the Load function for the current game state.
void GameStateExecuteLoad(GameStates gameState);

// Execute the Init function for the current game state.
void GameStateExecuteInit(GameStates gameState);

// Execute the Update function for the current game state.
void GameStateExecuteUpdate(GameStates gameState, float dt);

// Execute the Shutdown function for the current game state.
void GameStateExecuteShutdown(GameStates gameState);

// Execute the Unload function for the current game state.
void GameStateExecuteUnload(GameStates gameState);

//------------------------------------------------------------------------------

