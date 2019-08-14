//---------------------------------------------------------
// file:	OST.c
// author:	Akshat Madan
// brief:	Plays music for the game
//
// Copyright © 2019 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Sound.h"
#include "OST.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------
static FMOD_SOUND* track1;
static FMOD_SOUND* track2;
static FMOD_SOUND* track3;
static FMOD_SOUND* track4;
static FMOD_SOUND* track5;
static FMOD_SOUND* track6;
static FMOD_SOUND* track7;
static FMOD_SOUND* track8;
static FMOD_SOUND* sfx;
//---------------------------------------------------------
// Functions:
//---------------------------------------------------------
void playSong(int ID)
{
	switch (ID)
	{
	case 1:
		SoundInit("./Assets/Sound/OST/thePeasant.mp3", FMOD_LOOP_NORMAL, &track1);
		SoundPlay(&track1, false);
		break;
	case 2:
		SoundInit("./Assets/Sound/OST/breadAndAle.mp3", FMOD_LOOP_NORMAL, &track2);
		SoundPlay(&track2, false);
		break;
	case 3:
		SoundInit("./Assets/Sound/OST/burningEmpire.mp3", FMOD_LOOP_NORMAL, &track3);
		SoundPlay(&track3, false);
		break;
	case 4:
		SoundInit("./Assets/Sound/OST/theKnight.mp3", FMOD_LOOP_NORMAL, &track4);
		SoundPlay(&track4, false);
		break;
	case 5:
		SoundInit("./Assets/Sound/OST/pyrrhicBattles.mp3", FMOD_LOOP_NORMAL, &track5);
		SoundPlay(&track5, false);
		break;
	case 6:
		SoundInit("./Assets/Sound/OST/theHero.mp3", FMOD_LOOP_NORMAL, &track6);
		SoundPlay(&track6, false);
		break;
	case 7:
		SoundInit("./Assets/Sound/OST/untiedDenoument.mp3", FMOD_LOOP_NORMAL, &track7);
		SoundPlay(&track7, false);
		break;
	case 8:
		SoundInit("./Assets/Sound/OST/riseOfTheDormant.mp3", FMOD_LOOP_NORMAL, &track8);
		SoundPlay(&track8, false);
		break;
	}
}

void stopSong(void)
{
	SoundFree(&track1);
	SoundFree(&track2);
	SoundFree(&track3);
	SoundFree(&track4);
	SoundFree(&track5);
	SoundFree(&track6);
	SoundFree(&track7);
	SoundFree(&track8);
}

void playDashSound(void)
{
	SoundInit("./Assets/Sound/SFX/Dash.mp3", FMOD_LOOP_OFF, &sfx);
	SoundPlay(&sfx, false);
}

void playSwingSound(void)
{
	int random = rand() % 4;
	switch (random)
	{
	case 0:
		SoundInit("./Assets/Sound/SFX/Swing1.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 1:
		SoundInit("./Assets/Sound/SFX/Swing2.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 2:
		SoundInit("./Assets/Sound/SFX/Swing3.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 3:
		SoundInit("./Assets/Sound/SFX/Swing4.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 4:
		SoundInit("./Assets/Sound/SFX/Swing5.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	}
}

void playParrySound(void)
{
	int random = rand() % 2;
	switch (random)
	{
	case 0:
		SoundInit("./Assets/Sound/SFX/Parry1.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 1:
		SoundInit("./Assets/Sound/SFX/Parry2.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 2:
		SoundInit("./Assets/Sound/SFX/Parry3.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	}
}

void playBlockSound(void)
{
	int random = rand() % 2;
	switch (random)
	{
	case 0:
		SoundInit("./Assets/Sound/SFX/Block1.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 1:
		SoundInit("./Assets/Sound/SFX/Block2.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	case 2:
		SoundInit("./Assets/Sound/SFX/Block3.mp3", FMOD_LOOP_OFF, &sfx);
		SoundPlay(&sfx, false);
		break;
	}
}