//---------------------------------------------------------
// file:	GameManager.h
// author:	Anthony Miller
// brief:	Game Over scene functions
//
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

#pragma once

void GameManagerInit();
int getScore();
void incrementScore();
void resetScore();
int getEnergy();
void incrementEnergy();
void decrementEnergy();
void resetEnergy();
float getShotX(int iteration);
float getShotY(int iteration);
void setShot(int iteration, float x, float y);
void moveShot(int iteration);
float getAstroidX(int iteration);
float getAstroidY(int iteration);
void setAstroid(int iteration, float x, float y);
void moveAstroid(int iteration);
void setHighScore(int newScore, int location);
int getHighScore(int location);