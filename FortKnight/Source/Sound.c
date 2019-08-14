//------------------------------------------------------------------------------
//
// File Name:	Sound.c
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sound.h"
#include "fmod_common.h"
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
static	FMOD_SYSTEM      *FmodSystem;  //for initializing and shutting down FMOD
//static	FMOD_SOUND       *sound[10];   //Pointer to array of sounds
static	FMOD_CHANNEL     *channel = 0; //sound channel to play sound on
static FMOD_CREATESOUNDEXINFO exinfo;  //I dont think this is needed
static unsigned int		  version;	   //for checking FMOD version
static FMOD_RESULT		  result;	   //for error checking
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Initialize the Sound, call only once at game startup
void SoundModuleInit()
{
	result = FMOD_System_Create(&FmodSystem);
//	ERRCHECK(result);

	result = FMOD_System_GetVersion(FmodSystem, &version);
//	ERRCHECK(result);

	result = FMOD_System_Init(FmodSystem, 32, FMOD_INIT_NORMAL, NULL);
//	ERRCHECK(result);

}
// Initialize the sound file for playback
void SoundInit(const char* filePath, FMOD_MODE fmodMode, FMOD_SOUND **sound)
{
	result = FMOD_System_CreateSound(FmodSystem, filePath, fmodMode, NULL, sound);
	//	ERRCHECK(result);
}

void SoundPlay(FMOD_SOUND **sound,bool isPaused)
{
	FMOD_System_PlaySound(FmodSystem, *sound, 0, isPaused, &channel);
}

// Update the Sound
void SoundModuleUpdate()
{
	FMOD_System_Update(FmodSystem);
//	ERRCHECK(result);
}

void SoundFree(FMOD_SOUND **sound)
{
	result = FMOD_Sound_Release(*sound);
	//ERRCHECK(result);
}

// Shutdown Sound System
void SoundShutdown()
{
	result = FMOD_System_Close(FmodSystem);
//	ERRCHECK(result);
	result = FMOD_System_Release(FmodSystem);
//	ERRCHECK(result);
}

FMOD_SYSTEM* SoundGetSystem()
{
	return FmodSystem;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

