//---------------------------------------------------------
// file:	Scene_Game.h
// author:	Anthony Miller
// brief:	Game scene functions
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

void SceneGameInit();
void SceneGameUpdate();
void leftGame(void);
void drawLeftGame(void);
void drawBullets(void);
void updateAstroids(void);
void drawAstroids(float x, float y);
void spawnBullet(void);
void spawnAstroid(void);
void rightGame(void);
void drawMouse(void);
void checkCollision();
