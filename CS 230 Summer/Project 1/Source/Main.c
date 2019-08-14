//------------------------------------------------------------------------------
//
// File Name:	Main.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Engine.h"
#include "GameStateManager.h"

//------------------------------------------------------------------------------
// Main Function:
//------------------------------------------------------------------------------

int main(void)
{
	// Change in time (in seconds) since the last game loop.
	// A framerate controller is not required for this assignment.
	float dt = 0;

	// Initialize the game engine.
	EngineInit();

	// MAIN LOOP: Do not exit until instructed to do so by the game state manager (GSM).
	while (GameStateManagerIsRunning())
	{
		// Update the game engine.
		EngineUpdate(dt);
	}

	// Shutdown the game engine.
	EngineShutdown();

	return 0;
}