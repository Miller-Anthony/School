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

// Initialize the game engine.
void EngineInit()
{
	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be initialized first.
	//--------------------------------------------------------------------------

	// Initialize the Tracing/Logging module.
	TraceInit();

	TraceMessage("Engine: Init");

	//--------------------------------------------------------------------------
	// NOTE: Other modules can be initialized later and in any order.
	//--------------------------------------------------------------------------

	// Initialize the game state manager.
	GameStateManagerInit();
}

// Update the game engine.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void EngineUpdate(float dt)
{
	TraceMessage("Engine: Update");

	// Update the game state manager.
	GameStateManagerUpdate(dt);
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

	// Shutdown the Tracing/Logging module.
	TraceShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

