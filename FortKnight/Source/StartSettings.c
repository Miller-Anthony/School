//------------------------------------------------------------------------------
//
// File Name:	StartSettings.c
// Author(s):	Akshat Madan
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "StartSettings.h"

#include "GameStateManager.h"
#include "System.h"
#include "Input.h"
#include "Trace.h"

#include <windows.h>
#include <wchar.h>
#include <Shlobj.h>
#include <winerror.h>


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
static int windowed;
static int resolution;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the game settings at start.
void StartSettingsInit()
{
	LPWSTR wpath = NULL;
	HRESULT hr;
	wchar_t buffer[MAX_PATH];
	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("Settings.txt"));

	char folder[MAX_PATH];
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}

	static FILE *settings; // File to read lives from
	static errno_t error;

	error = fopen_s(&settings, folder, "a"); // Open file
	if (error == 0)
		fclose(settings);
	error = fopen_s(&settings, folder, "r"); // Open file

	if (error == 0)
	{
		windowed = fgetc(settings); // If opened, read windowed / fullscreen 
		resolution = fgetc(settings); // If opened, read resolution
		fclose(settings);
	}

	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}

	static FILE *save1; // File to read lives from
	static FILE *save2; // File to read lives from
	static FILE *save3; // File to read lives from

	error = fopen_s(&save1, folder, "a"); // Open file
	if (error == 0)
		fclose(save1);

	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}

	error = fopen_s(&save2, folder, "a"); // Open file
	if (error == 0)
		fclose(save2);

	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error = fopen_s(&save3, folder, "a"); // Open file
	if (error == 0)
		fclose(save3);
}

// Update the game settings at start.
void StartSettingsUpdate()
{
	HWND window = AESysGetWindowHandle();

	if (windowed == 'f')
	{
		SetWindowLongA(window, GWL_STYLE, WS_POPUP);
		SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW); // Set window to 0,0 and 1080p, CHANGE WITH FOPEN AND SETTINGS CALL LATER
	}
	else if(resolution == '0')
		SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
	else if (resolution == '1')
		SetWindowPos(window, HWND_TOP, 0, 0, 1280, 720, SWP_SHOWWINDOW);
	else
		SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

