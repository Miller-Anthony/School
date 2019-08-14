//---------------------------------------------------------
// file:	Scene_PHYtest.h
// author:	Tristan Bouchard
// brief:	Testing player movment etc
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

//All code in this file done by Tristan Bouchard

#pragma once

//enables x,y axis movement
void enableALLMOVEMENT(float *positionY, float *positionX, float *velocityY, float *velocityX, float accelerationY, float accelerationX, float decelerarion, int max_speed);
//enables y axis movement
void enableUPDOWN(float *velocityY, float accelerationY, float decelerarion, int max_speed);
//enables x axis movement
void enableRIGHTLEFT(float *velocityX, float accelerationX, float decelerarion, int max_speed);
//sets up collision for player movement to be disabled
void disableMOVEMENT(float *positionX, float *positionY, float charWidth, float charHeight, float *velocityX, float *velocityY, float X, float Y, float W, float H, int SeeCollision);
//enable movement
void enableMOVEMENT(float *positionX, float *positionY, float *velocityX, float *velocityY);
//event collision
int eventCollision(float *positionX, float *positionY, float charWidth, float charHeight, float X, float Y, float W, float H);

//graphic stuff
void fractalTree(int length, float angle, int strokethick, int condistional);


void mouseXY(void);
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

void ScenePHYtestInit();
void ScenePHYtestUpdate();