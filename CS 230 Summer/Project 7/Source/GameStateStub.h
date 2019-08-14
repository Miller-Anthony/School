//------------------------------------------------------------------------------
//
// File Name:	GameStateStub.h
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

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

// Load the resources associated with the Stub game state.
void GameStateStubLoad();

// Initialize the memory associated with the Stub game state.
void GameStateStubInit();

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateStubUpdate(float dt);

// Shutdown any memory associated with the Stub game state.
void GameStateStubShutdown();

// Unload the resources associated with the Stub game state.
void GameStateStubUnload();

/*----------------------------------------------------------------------------*/

