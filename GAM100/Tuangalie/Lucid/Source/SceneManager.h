//---------------------------------------------------------
// file:	SceneManager.h
// author:	Justin Chambers
// brief:	Basic scene management system
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include "SceneTable.h"

#define TRUE 1
#define FALSE 0

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
// Public Functions:
//---------------------------------------------------------

void SceneManagerInit();
void SceneManagerUpdate();

// Tell the Scene Manager to Change States
void SceneManagerSetNextScene(SCENE nextScene);
