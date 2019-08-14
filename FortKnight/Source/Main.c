//------------------------------------------------------------------------------
//
// File Name:	Main.c
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <windows.h>
#include "Engine.h"
#include "GameStateManager.h"
#include "System.h"
#include "time.h"
#include "DT.h"
#include "AEEngine.h"

//------------------------------------------------------------------------------
// Main Function:
//------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

  srand((unsigned)time(NULL));
	// Store the Windows settings passed in WinMain.
	SystemStoreWindowSettings(instanceH, show);

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