//---------------------------------------------------------
// file:	InputManager.c
// author:	Anthony Miller
// brief:	Custom game input functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameManager.h"
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
void InputManagerInit()
{
	
}

//---------------------------------------------------------
// Update managers and systems in the engine.
void InputManagerUpdate()
{
	if (keyPressed(KEY_1))
	{
		SceneManagerSetNextScene(SCENE_DIGIPEN_LOGO);
	}
	if (keyPressed(KEY_2))
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
	if (keyPressed(KEY_3))
	{
		SceneManagerSetNextScene(SCENE_GAME);
	}
	if (keyPressed(KEY_4))
	{
		SceneManagerSetNextScene(SCENE_GAMEOVER);
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------
