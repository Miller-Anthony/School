//------------------------------------------------------------------------------
//
// File Name:	System.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "System.h"
#include "GameStateManager.h"

#include "StartSettings.h"

//------------------------------------------------------------------------------
// Libraries
//------------------------------------------------------------------------------

#ifdef _DEBUG
#pragma comment (lib, "Alpha_Engine_D.lib")
#else
#pragma comment (lib, "Alpha_Engine.lib")
#endif

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SystemInfo
{
	HINSTANCE mAppInstance;
	bool mCreateWindow;

} SystemInfo;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static SystemInfo systemInfo;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Store the Windows settings passed in WinMain.
void SystemStoreWindowSettings(HINSTANCE instanceH, int show)
{
	systemInfo.mAppInstance = instanceH;
	systemInfo.mCreateWindow = show;
}

// Initialize the System (Windows, Event Handlers).
void SystemInit()
{
	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mAppInstance = systemInfo.mAppInstance;
	sysInitInfo.mShow = systemInfo.mCreateWindow;
	sysInitInfo.mWinWidth = 1920;
	sysInitInfo.mWinHeight = 1080;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL; //MyWinCallBack;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP; //WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;		
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mWindowHandle = NULL;
	AESysInit(&sysInitInfo);

	AEInputShowCursor(0);

	// Change the window title.
	AESysSetWindowTitle("Knightmare: A Hero's Journey");

	// reset the system modules
	AESysReset();

	StartSettingsInit();
	StartSettingsUpdate();
}

// Update the System (Windows, Event Handlers).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SystemUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	// Informing the system about the loop's start
	AESysFrameStart();

	AEInputShowCursor(0);

	// Update the Windows message queue.
	AESysUpdate();

	// Handling Input
	AEInputUpdate();

	// check if forcing the application to quit
	if (/*AEInputCheckTriggered(VK_ESCAPE) ||*/ !AESysDoesWindowExist())
	{
		GameStateManagerSetNextState(GsQuit);
	}
}

// Complete the draw process for the current game loop.
void SystemDraw()
{
	// Informing the system about the loop's end
	AESysFrameEnd();
}

// Shutdown the System (Windows, Event Handlers).
void SystemShutdown()
{
	// Shutdown the Alpha Engine.
	AESysExit();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

