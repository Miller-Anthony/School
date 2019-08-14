//---------------------------------------------------------
// file:	Scene_Level_Select.c
// author:	Tristan Bouchard
// brief:	Level Select scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

//All code in this file done by Tristan Bouchard

#include "C_Processing.h"
#include "Scene_MainMenu.h"
#include "SceneManager.h"
#include "Scene_PHYtest.h"

//GLOBALS===========
extern int TIME;
extern int imIndex;
//==================

int charDirection = 1;       //player direction for drawing image
int i, j;                    //loop variables
int walkAnispeed = 0;        //walk speed for playing animations
int idleAnispeed = 0;        //idle speed for playing animations
int walkIdleIndex = 1;       //animation index
int walkStop = 0;            //toggle between idle and walk animations
int leave = 1;               //toggles if you are leaving the room or not
static int walkFiles = 14;   //number of sprites in walking animations
static int idleFiles = 4;    //number of sprites in idle animatiaon
static int toggle = 1;       //toggle if you have been in the scene or not
unsigned int alphaCut = 255; //alpha for init black screen

vec2_t bedText = {0, 200 };              //bed text position
vec2_t bedCollisionXY = { 1222, 785 };   //bed collision position
vec2_t bedCollisionWH = { 800, 300 };    //bed collision width and height
vec2_t playerPosition = { 500, 795 };    //player position
vec2_t playerWidthHeight = { 900, 900 }; //player height and width

PImage clockPics[12];                  //clock animation image buffer
PImage Bedroom;                        //bedroom image
PImage Sky;                            //background sky image
PImage Shadow;                         //clock shadow image
PImage sign;                           //sign image
PImage credits;                        //credit screen
static PImage walk_images_clothed[14]; //image buffer for walk animation sprites
static PImage idle_images_clothed[4];  //image buffer for idle animation sprites
static PImage *charAnimations[2];      //array containing all animations

static char walk_clothed[14][256]; //converter buffer for path to image for walk animations
static char idle_clothed[4][256];  //converter buffer for path to image for idle animations
char clockINIT[12][256] = { 0 };   //converter for paths to images buffer

PChannel intro;  //sound mixer for door slam
PSound doorSlam; //door slam sound

PFont consoleText; //console text used

float timeHolder; //holds last time

void SceneMainMenuInit()
{
	setFrameRate(60);
	fullscreen();

	Bedroom = loadImage("./Assets/Graphics/Bedroom/Bedroom_GAME_FINAL.png");
	Shadow = loadImage("./Assets/Graphics/clock/clockTime_shadow.png");
	Sky = loadImage("./Assets/Graphics/NightSky/nightSkyEdit.png");
	sign = loadImage("./Assets/sign.png");
	credits = loadImage("./Assets/credits.png");


	// loads walking animations
	for (i = 0, j = 1; i < walkFiles; i++, j++)
	{
		sprintf_s(walk_clothed[i], _countof(walk_clothed[i]), "./Assets/sprites/walk/walk_clothed_%i.png", j);
		walk_images_clothed[i] = loadImage(walk_clothed[i]);
	}

	//loads idle animations
	for (i = 0, j = 1; i < idleFiles; i++, j++)
	{
		sprintf_s(idle_clothed[i], _countof(idle_clothed[i]), "./Assets/sprites/idle/idle_clothed_%i.png", j);
		idle_images_clothed[i] = loadImage(idle_clothed[i]);
	}

	//sets pointer array
	charAnimations[0] = walk_images_clothed;
	charAnimations[1] = idle_images_clothed;

	//loads font
	consoleText = loadFont("./Assets/Fonts/consoleText.ttf");
	textFont(consoleText, 25);

	//loads clock
	for (i = 1, j = 0; i <= 12; i++, j++)
	{
		sprintf_s(clockINIT[j], _countof(clockINIT[j]), "./Assets/Graphics/clock/clockTime_%i.png", i);
		clockPics[j] = loadImage(clockINIT[j]);
	}
}

void SceneMainMenuUpdate()
{


  doorSlam = loadSound("./Assets/Notes/doorSlam.wav", 0);

  intro = createChannel("slam");
  setVolume(intro, 1);
  getReverb(intro, 0);
  setPitch(intro, -15);
  if (toggle)
  {
    soundChannel(doorSlam, intro);
    toggle = 0;
  }
  
	if (leave)
	{
		//move right
		if (keyIsDown(KEY_D))
		{
			if (charDirection == -1)
				charDirection = 1;

			walkStop = 0;
			playerPosition.x += 14;
			walkAnispeed++;
		}
		//move left
		else if (keyIsDown(KEY_A))
		{
			if (charDirection == 1)
				charDirection = -1;

			walkStop = 0;
			playerPosition.x -= 14;
			walkAnispeed++;
		}
		//when no keys are pressed
		else
		{
			walkStop = 1;
			idleAnispeed++;
		}
	}


	//12 o'Clock check
	if (TIME == 12)
		timeHolder = 1;
	else
		timeHolder = TIME * 1.5;
	//draws sky
	image(Sky, 720, 4500 - (timeHolder * 400), 1920, 8000, 255);
	//draws background
	image(Bedroom, (1920 / 2), (1080 / 2), 1920, 1080, 255);
	//draws clock shadow
	image(Shadow, 1060, 455, 170, 170, 255);
	//draws clock
	image(clockPics[imIndex], 1070, 450, 170, 170, 255);

	//image on door
	image(sign, 195, 600, 300, 300, 255);

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

	if (playerPosition.x >= 1222)
		playerPosition.x = playerPosition.x - 14;

	//collision for clock
	if (eventCollision(&playerPosition.x, &playerPosition.x, 100, 500, 990, 1000, 80, 10))
	{
		strokeWeight(50);
		fill(255, 255, 255, 255);
		textFont(consoleText, 20);
		text("Time [E]", 1000, 390);
		if (keyPressed(KEY_E))
			SceneManagerSetNextScene(SCENE_CLOCK);
		textFont(consoleText, 25);
	}

	if (playerPosition.x >= 1200)
	{
		if (keyPressed(KEY_E))
		{
			leave = 0;
			playerPosition.x = playerPosition.x - 14;
			playerPosition.x = playerPosition.x + 14;
		}
			
    if (leave == 0 && fadeout() == 0)
    {
      leave = 1;
      SceneManagerSetNextScene(SCENE_LEVEL_SELECT);
    }

		strokeWeight(50);
		fill(255, 255, 255, 255);
		text("Press [E] to sleep", 1285, 775);

		noFill();
	}

	//left collision
	if (playerPosition.x <= 100)
		playerPosition.x = playerPosition.x + 14;

	//exit
	if (playerPosition.x <= 400)
	{
		strokeWeight(50);
		fill(255, 255, 255, 255);
		text("Press [E] to exit", 10, 310);

		if (keyPressed(KEY_E))
			Terminate();
		noFill();
	} 

  //draws player
  image(charAnimations[walkStop][walkIdleIndex], playerPosition.x, playerPosition.y, playerWidthHeight.x * charDirection, playerWidthHeight.y, 255);

  if (playerPosition.x >= 400 && playerPosition.x <= 600)
  {
	  strokeWeight(50);
	  fill(255, 255, 255, 255);
	  text("Hold [E] to view Credits", 400, 580);

    //draws credits
	  if (keyIsDown(KEY_E))
	  {
		  image(credits, 960, 540, 1500, 1000, 255);
	  }
  }
  //black mask for fading in
  if (alphaCut > 0)
  {
    fill(0, 0, 0, --alphaCut);
    rect(0, 0, 1920, 1080);
    noFill();
  }
}