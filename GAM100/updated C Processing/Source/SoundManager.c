//---------------------------------------------------------
// file:	SoundManager.c
// author:	Anthony Miller
// brief:	Sound functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SoundManager.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------
static PSound snare;                   //holds the sound of a snare
static PSound shoot;                   //holds the sound for shooting
static PSound aExplode;                //holds the sound of an astroid explosion
static PSound sExplode;                //holds the sound of a ship explosion

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SoundManagerInit()
{
	//set the snare variable to the snare sound file
	snare = loadSound("./Assets/Snare.wav", 0);
	shoot = loadSound("./Assets/pew.wav", 0);
	aExplode = loadSound("./Assets/astroidExplode.wav", 0);
	sExplode = loadSound("./Assets/ShipExplode.wav", 0);
}


//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

void playSnare()
{
	sound(snare);
}

void playShoot()
{
	sound(shoot);
}

void playAstroidExplosion()
{
	sound(aExplode);
}

void playShipExplosion()
{
	sound(sExplode);
}