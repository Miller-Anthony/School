//------------------------------------------------------------------------------
//
// File Name:	Sound.h
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "fmod.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

	typedef enum SoundType
	{
		Background,
		SFX
	}SoundType;

#if 1

	typedef struct Sound
	{
		const char* soundPath;	//sound file path
		const char* name;		//sound name
		FMOD_SOUND* fmodSound;	//fmod struct managing fmod stuff
		FMOD_CHANNEL* channel;	//other fmod struct managing fmod stuff
		SoundType	soundType;	//whether a song is effect or background music
	}Sound;

#endif
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
	
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Sound, call only once at game startup
void SoundModuleInit();
// Initialize the sound file for playback
void SoundInit(const char* filePath, FMOD_MODE fmodMode, FMOD_SOUND **sound);

//Play the sound
void SoundPlay(FMOD_SOUND **sound, bool isPaused);

// Update the FMOD Sound System
void SoundModuleUpdate();

//free a song
void SoundFree(FMOD_SOUND **sound);


// Shutdown FMOD Sound System
void SoundShutdown();

// Get current channel for settings
FMOD_SYSTEM* SoundGetSystem();

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

