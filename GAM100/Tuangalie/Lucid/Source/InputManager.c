//---------------------------------------------------------
// file:	InputManager.c
// author:	Justin Chambers
// brief:	Custom input functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneManager.h"
#include "SceneTable.h"

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
int activated = FALSE;
//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

void enableDebug()
{
	activated = !activated;
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void InputManagerUpdate()
{
	if (activated)
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
			SceneManagerSetNextScene(SCENE_LEVEL_SELECT);
		}
		if (keyPressed(KEY_4))
		{
			SceneManagerSetNextScene(SCENE_ROOM1);
		}
		if (keyPressed(KEY_5))
		{
			SceneManagerSetNextScene(SCENE_ROOM2);
		}
		if (keyPressed(KEY_6))
		{
			SceneManagerSetNextScene(SCENE_ROOM3);
		}
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

