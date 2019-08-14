//------------------------------------------------------------------------------
//
// File Name:	System.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 1
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <Windows.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
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

// Store the Windows settings passed in WinMain.
void SystemStoreWindowSettings(HINSTANCE instanceH, int show);

// Initialize the System (Windows, Event Handlers).
void SystemInit();

// Update the System (Windows, Event Handlers).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SystemUpdate(float dt);

// Complete the draw process for the current game loop.
void SystemDraw();

// Shutdown the System (Windows, Event Handlers).
void SystemShutdown();

/*----------------------------------------------------------------------------*/

