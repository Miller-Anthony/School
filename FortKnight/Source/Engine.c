//------------------------------------------------------------------------------
//
// File Name:	Engine.c
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
#include "System.h"
#include "Input.h"
#include "Trace.h"
#include "Sound.h"
#include "DT.h"
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

// Initialize the game engine.
void EngineInit()
{
	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be initialized first.
	//--------------------------------------------------------------------------

	// Initialize the Tracing/Logging module.
	//TraceInit();

	TraceMessage("Engine: Init");

	// Initialize the System (Windows, Event Handlers).
	SystemInit();

	//--------------------------------------------------------------------------
	// NOTE: Other modules can be initialized later and in any order.
	//--------------------------------------------------------------------------

	// Initialize the game state manager.
	GameStateManagerInit();
	// Initialize Controller Input
	InputInit(0);
	//InputInit(1);
}

// Update the game engine.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EngineUpdate()
{
	TraceMessage("Engine: Update");
  
	//Update dt
	DTUpdate();

	// Update the System (Windows, Event Handlers).
	SystemUpdate(dt);

	// Update the game state manager.
	GameStateManagerUpdate(dt);

	// Update Controller Input
	InputUpdate(0);

	SoundModuleUpdate();
	// Complete the draw process for the current game loop.
	SystemDraw();
}

// Shutdown the game engine.
void EngineShutdown()
{
	TraceMessage("Engine: Shutdown");

	//--------------------------------------------------------------------------
	// NOTE: Some modules can be shutdown in any order.
	//--------------------------------------------------------------------------

	// Shutdown the game state manager.
	GameStateManagerShutdown();

	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be shutdown last and in reverse order.
	//--------------------------------------------------------------------------

	// Shutdown the System (Windows, Event Handlers).
	SystemShutdown();

	// Shutdown the Tracing/Logging module.
	TraceShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

