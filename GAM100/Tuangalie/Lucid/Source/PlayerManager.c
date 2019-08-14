#pragma once

//---------------------------------------------------------
// file:	Scene_PHYtest.c
// author:	Tristan Bouchard
// brief:	Level Select scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

//All code in this file done by Tristan Bouchard

#include "C_Processing.h"
#include "SceneManager.h"
#include "windows.h"
#include <stdlib.h>
#include <math.h>
#include "PlayerManager.h"
int m, n;                    //loop variables
int walkFiles = 14;          //walk sprite count
int idleFiles = 4;           //idle sprite count
int walkStop;                //toggle for walking and idle anis
int walkIdleIndex;           //index for 2d array

PImage walk_images_nude[14]; //buffer for walking animations
PImage idle_images_nude[4];  //buffer for idle animations
PImage *charAnimations[2];   //2D array for both animations

char walk_nude[14][256];     // 14 files names and 256 possible characters in the file path
char idle_nude[4][256];      //formatting buffer for idle animations




void loadPlayerNUDEImages(void)
{ 
  // loads walking animations
  for (m = 0, n = 1; m < walkFiles; m++, n++)
  {
    sprintf_s(walk_nude[m], _countof(walk_nude[m]), "./Assets/sprites/walk/walk_nude_%i.png", n);
    walk_images_nude[m] = loadImage(walk_nude[m]);
  }

  //loads idle animations
  for (m = 0, n = 1; m < idleFiles; m++, n++)
  {
    sprintf_s(idle_nude[m], _countof(idle_nude[m]), "./Assets/sprites/idle/idle_nude_%i.png", n);
    idle_images_nude[m] = loadImage(idle_nude[m]);
  }

  //sets pointer array
  charAnimations[0] = walk_images_nude;
  charAnimations[1] = idle_images_nude;
}

void drawPlayerNUDE(PLAYER playerXYWH)
{
  //load images, set positions, directions and array toggle
	loadPlayerNUDEImages();
  static int walkAnispeed = 0;
  static int idleAnispeed = 0;
  static int dir = 1;
  static int walkStop = 1;

  //plays player animations

  //move right
  if (keyIsDown(KEY_D))
  {
    if (dir == -1)
      dir = 1;

    walkStop = 0;
    walkAnispeed++;
  }
  //move left
  else if (keyIsDown(KEY_A))
  {
    if (dir == 1)
      dir = -1;

    walkStop = 0;
    walkAnispeed++;
  }
  //move up and down
  else if (keyIsDown(KEY_S) || keyIsDown(KEY_W))
  {
    walkStop = 0;
    walkAnispeed++;
  }
  //when no keys are pressed
  else
  {
    walkStop = 1;
    idleAnispeed++;
  }

  //walk animation speed
  if (walkAnispeed % 6 == 0 && walkStop == 0)
    walkIdleIndex++;

  //idle animation speed
  if (idleAnispeed % 18 == 0 && walkStop == 1)
    walkIdleIndex++;

  //resets index to avoid buffer overflow
  if (walkIdleIndex >= 14 && walkStop == 0)
    walkIdleIndex = 0;
  if (walkIdleIndex >= 4 && walkStop == 1)
    walkIdleIndex = 0;

  //safty check
  if (walkAnispeed == 1000000 || idleAnispeed == 1000000)
  {
    walkAnispeed = 0;
    idleAnispeed = 0;
  }

  //draw player animations
  image(charAnimations[walkStop][walkIdleIndex], playerXYWH.x, playerXYWH.y, playerXYWH.w * dir, playerXYWH.h, 255);
}