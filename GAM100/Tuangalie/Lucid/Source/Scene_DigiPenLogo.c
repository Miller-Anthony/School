//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Tristan Bouhard
// brief:	DigiPen Logo scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_DigiPenLogo.h"
#include "SceneManager.h"
#include "windows.h"
#include "PlayerManager.h"
#include "InputManager.h"

int i, j;

int timer; // timer to keep the digipen logo on the screen for long enough

static PFont deskText;

int Sectime;
PImage DigiLOGO;
PImage TeamLOGO;
PImage GameLOGO;

int IMscaler;
int walk_alpha = 0;
int TeamLogo_alpha = 0;
float DigiLogo_alpha = 0;

bool logo_max;
bool team_max;

bool logo_done = false;
bool team_done = false;

int debug;

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneDigiPenLogoInit()
{
	fullscreen();
	setFrameRate(60);
	background(0, 0, 0);

	//Digipen LOGO
	DigiLOGO = loadImage("./Assets/Digipen_WHITE_1024px.png");

	//Tuangalie LOGO
	TeamLOGO = loadImage("./Assets/TuangalieLogo.png");
	textSize(40);

	GameLOGO = loadImage("./Assets/gamelogo.png");

	deskText = loadFont("./Assets/Fonts/consoleText.ttf");
	textFont(deskText, 20);

	timer = 0;
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneDigiPenLogoUpdate()
{
	background(0, 0, 0);
	image(DigiLOGO, 960, 540, 1024, 247, DigiLogo_alpha);

	if (DigiLogo_alpha < 255 && logo_max != true)
	{
		DigiLogo_alpha += 1;
	}
	else if (timer == second() && logo_max)
	{

	}
	else if (DigiLogo_alpha >= 1)
	{
		logo_max = true;
		timer = second() + 2;
		DigiLogo_alpha -= 1;
	}
	else
	{
		DigiLogo_alpha -= 1;
	}

	if (DigiLogo_alpha < 0)
	{
		logo_done = true;
	}

	if (logo_done == true)
	{
		image(TeamLOGO, 960, 540, 1920, 1080, TeamLogo_alpha);

		if (TeamLogo_alpha < 255 && team_max != true)
		{
			TeamLogo_alpha += 1;
		}
		else if (TeamLogo_alpha >= 1)
		{
			team_max = true;

			TeamLogo_alpha -= 1;
		}
		else
		{
			TeamLogo_alpha -= 1;
		}

		if (TeamLogo_alpha < 0)
		{
			team_done = true;
		}
	}

	if (team_done == true)
	{
		image(GameLOGO, 960, 540, 1920, 1080, 255);


		if (keyPressed(KEY_E))
		{
			SceneManagerSetNextScene(SCENE_MAIN_MENU);
		}
	}
	text("Copyright 2018 DigiPen (USA) Corporation", 1100, 1050);
	
	//activate debug mode
	if (keyPressed(KEY_UP) && debug == 1)
	{
		debug = 2;
	}
	else if (keyPressed(KEY_UP))
	{
		debug = 1;
	}
	if (keyPressed(KEY_DOWN) && debug == 2)
	{
		debug = 3;
	}
	if (keyPressed(KEY_DOWN) && debug == 3)
	{
		debug = 4;
	}
	if (keyPressed(KEY_LEFT) && debug == 4)
	{
		debug = 5;
	}
	if (keyPressed(KEY_RIGHT) && debug == 5)
	{
		debug = 6;
	}
	if (keyPressed(KEY_LEFT) && debug == 6)
	{
		debug = 7;
	}
	if (keyPressed(KEY_RIGHT) && debug == 7)
	{
		debug = 8;
	}
	if (keyPressed(KEY_B) && debug == 8)
	{
		debug = 9;
	}
	if (keyPressed(KEY_A) && debug == 9)
	{
		debug = 10;
	}
	if (keyPressed(KEY_RIGHT_SHIFT) && debug == 10)
	{
		debug = 11;
	}
	if (keyPressed(KEY_ENTER) && debug == 11)
	{
		enableDebug();
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

