//---------------------------------------------------------
// file:	Engine.h
// author:	Tristan Bouchard
// brief:	Basic game engine organization/loads fades
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

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
//fade out
int fadeout(void);
//fade in
int fadein(void);
//loads fade variables
void fadeLoad(void);


void EngineInit();
void EngineUpdate();
