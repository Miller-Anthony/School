#pragma once

//---------------------------------------------------------
// file:	Scene_Clock.c
// author:	Tristan Bouchard
// brief:	time changing and displaying
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

//All code in this file done by Tristan Bouchard

#include "C_Processing.h"
#include "Scene_PHYtest.h"
#include "SceneManager.h"
#include "windows.h"
#include "Scene_PHYtest.h"
#include <stdlib.h>

//GLOBAL VERIABLES
int TIME = 1;    //global time
int imIndex = 0; //global time index
//================

PFont consoleFont;                 //font of choice
char clockString[12][256] = { 0 }; // 12 files names and 256 possible characters in the file path
char timeDisplay[20];              //displays time

PImage clock[12]; //image buffer fir the clock
PImage Closeup;   //close up image of background
PImage CShad;     //clock shadow
int i, j;         //loop variable

int FramesPerSec = 0; //tracks time for index changing

void SceneClockInit()
{
	setFrameRate(60);
  fullscreen();
	background(255, 255, 255);
	
	//loads font
	consoleFont = loadFont("./Assets/Fonts/consoleText.ttf");
	textFont(consoleFont, 50);

	//loads background
	Closeup = loadImage("./Assets/Graphics/Bedroom/CloseupWall.png");
	//loads shadow
	CShad = loadImage("./Assets/Graphics/clock/clockTime_shadow.png");

  //loads clock index images in buffer
	for (i = 1, j = 0; i <= 12; i++, j++)
	{
		sprintf_s(clockString[j], _countof(clockString[j]), "./Assets/Graphics/clock/clockTime_%i.png", i);
		clock[j] = loadImage(clockString[j]);
	}
}

void SceneClockUpdate()
{
  //dispaly time
	sprintf_s(timeDisplay, _countof(timeDisplay), "%2i:00am", TIME);

  //increse frame check
	FramesPerSec++;

	//draw backgorund
	image(Closeup, 960, 540, 1920, 1080, 255);

	//rotaes clock and index

  //add to time
	if (keyIsDown(KEY_D))
	{
		if (FramesPerSec % 5 == 0)
		{
			imIndex++;
			TIME += 1;
		} 
		if (TIME > 12)
			TIME = 1;
	}
  //subtract time
	else if (keyIsDown(KEY_A))
	{
		if (FramesPerSec % 5 == 0)
		{
			imIndex--;
			TIME -= 1;
		}
		if (TIME < 1)
			TIME = 12;
	}

	//prevents overflows in arrays
	if (imIndex > 11)
		imIndex = 0;
	else if (imIndex < 0)
		imIndex = 11;

	//fail safe
	if (FramesPerSec > 100000000)
		FramesPerSec = 0;

	//leave clock
	if (keyPressed(KEY_E))
		SceneManagerSetNextScene(SCENE_MAIN_MENU);

	//draw clock shadow
	image(CShad, 680, 550, 800, 800, 255);
	//draw clock
	image(clock[imIndex], 700, 540, 800, 800, 255);
	//loads time
	fill(0, 0, 0, 255);
	text(timeDisplay, 530, 660);

  //UI stuff
	textFont(consoleFont, 40);
	text("-A D+", 620, 720);
	textFont(consoleFont, 50);
	text("Exit[E]", 10, 1030);
}
