//------------------------------------------------------------------------------
//
// File Name:	GameStateManager.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateTable.h"
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

GameState gameState;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static bool	GameStateIsChanging();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the game state manager.
void GameStateManagerInit()
{
	TraceMessage("GSM: Init");

	// Set the previous and current game states to invalid.
	gameState.previous = GsInvalid;
	gameState.current = GsInvalid;

	// Set the initial game state to launch the game.
	gameState.next = GsInitial;
}

// Update the game state manager.
void GameStateManagerUpdate(float dt)
{
	TraceMessage("GSM: Update");

	// Check for a game state change.
	if (GameStateIsChanging())
	{
		// Shutdown the current game state.
		GameStateExecuteShutdown(gameState.current);

			// if the current state is not restarting
		if (gameState.next != GsRestart)
		{
				//unload the current state
			GameStateExecuteUnload(gameState.current);
		
				// Update the recorded states.
			gameState.previous = gameState.current;
			gameState.current = gameState.next;

				//load the new game state
			GameStateExecuteLoad(gameState.current);
		}
		else
		{
				//reset the next state to the current one so the engine doesnt think states are changing
			gameState.next = gameState.current;
		}

		// Initialize the new game state.
		GameStateExecuteInit(gameState.current);
	}

	// Update the current game state.
	GameStateExecuteUpdate(gameState.current, dt);
}

// Shutdown the game state manager.
void GameStateManagerShutdown()
{
	TraceMessage("GSM: Shutdown");

	// Nothing needs to be done here.
}

// Determine if the current game state is being restarted.
bool GameStateManagerIsRestarting()
{
	return gameState.next == GsRestart;
}

// Determine if the game is still running.
bool GameStateManagerIsRunning()
{
	return gameState.current != GsQuit;
}

// Set the next game state to run.
void GameStateManagerSetNextState(GameStates nextState)
{
	if (GameStateIsValid(nextState) || GameStateIsSpecial(nextState))
	{
		gameState.next = nextState;
	}
	else
	{
#ifdef _DEBUG
		/* In debug mode, print a message that an error has occurred. */
		printf("\nERROR: Invalid game state: %d\n", nextState);
#endif
	}
}

/*------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------*/

// Determine if a game state change has been requested.
static bool	GameStateIsChanging()
{
	return (gameState.current != gameState.next);
}
