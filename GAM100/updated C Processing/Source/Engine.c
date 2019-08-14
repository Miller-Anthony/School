//---------------------------------------------------------
// file:	Engine.c
// author:	Justin Chambers
// brief:	Basic game engine organization
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Engine.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

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
// Initialize managers and systems in the engine.
void EngineInit()
{
	fullscreen();
	

	SceneManagerInit();
	GameManagerInit();
	SoundManagerInit();
}

//---------------------------------------------------------
// Update managers and systems in the engine.
void EngineUpdate()
{
	SceneManagerUpdate();
	InputManagerUpdate();
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------
