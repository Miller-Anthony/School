//---------------------------------------------------------
// file:	Scene_PHYtest.h
// author:	Tristan Bouchard
// brief:	Testing player movment etc
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

//All code in this file done by Tristan Bouchard

#pragma once
void mouseXY(void);
//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------
typedef struct PLAYER
{
  float x;
  float y;
  float w;
  float h;
  float velX;
  float velY;
}PLAYER;
//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------
void loadPlayerNUDEImages(void);
void drawPlayerNUDE(PLAYER playerXYWH);
//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------