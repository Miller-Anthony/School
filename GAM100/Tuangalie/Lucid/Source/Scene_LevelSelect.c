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

//GLOBAL===================
extern int exitTime;
extern PFont consoleText1;
extern int TIME;
extern int imIndex;
//=========================

int clockSeen = 0;         //clock seen toggle
int walkFiles2 = 14;       //number of sprites in walking animations
int idleFiles2 = 4;        //number of sprites in idle animations
int walkAnispeed2 = 0;     //walk animation speed 
int idleAnispeed2 = 0;     //idle animation speed
int walkIdleIndex2 = 1;    //index for 2D array
int walkStop2 = 0;         //toggles between walk and idle animations
int charDirectionNUDE = 1; //player direction
int quit = 1;              //can quit toggle
int charSpeed = 14;        //movement speed
int exit_Collision = 3750; //ecit collision position
int level = 480;           //set value to scall event collision for doors
int gotoLevel1 = 1;        //toggle for level 1
int gotoLevel2 = 1;        //toggle for level 2
int gotoLevel3 = 1;        //toggle for level 3
int gotoLevel4 = 1;        //toggle for level 4
int gotoLevel5 = 1;        //toggle for level 5
int waving = 0;            //waving event happening
int walksIndex = 0;        //walk inde
int i; j;                  //loop variables
int m, n;                  //loop variables
static int alphaCut = 255; //overlay alpha
static int timer = 0;      //timer for events

PImage Hallway;              //hallway image
PImage dlc;                  //DLC images
PImage *charAnimations2[2];  //2D animation buffer
PImage walk_images_nude[14]; //image buffer for play
PImage clockLS[12];          //image buffer for clock sprites
PImage CShadLS;              //clock shadow buffer
PImage idle_images_nude[4];  //image buffer for idle animations

PChannel walkSplat; //mixer for walk sounds
PSound splat1;      //walk sound 1
PSound splat2;      //walk sound 2
PSound walks[2];    //sound array for walk sounds

char walk_nude[14][256];             //converter from path to image
char idle_nude[4][256];              //number of sprites in idle animation
char clockStringLS[12][256] = { 0 }; //converter buffer from path to image

vec2_t playerPositionNUDE = { 270, 635 };    //player positions
vec2_t playerWidthHeightNUDE = { 490, 490 }; //player dimentions

float screenPos = 1920; //screen positions

PFont consoleText2; //console text used

void SceneLevelSelectInit()
{
  alphaCut = 255;
  timer = 0;
  //set framerate and screen rez
	setFrameRate(60);
	fullscreen();

  //set walk sound mixer
  walkSplat = createChannel("splat");
  setVolume(walkSplat, 1);
  
  //load sounds
  splat1 = loadSound("./Assets/Notes/walksplat1.wav", 0);
  splat2 = loadSound("./Assets/Notes/walksplat2.wav", 0);

  //load walk sounds into buffer
  walks[0] = splat1;
  walks[1] = splat2;

  //load hallway and DLC
	Hallway = loadImage("./Assets/Graphics/LevelSelect/level_select.png");
	dlc = loadImage("./Assets/sprites/dlc.png");
  
	// loads walking animations
	for (m = 0, n = 1; m < walkFiles2; m++, n++)
	{
		sprintf_s(walk_nude[m], _countof(walk_nude[m]), "./Assets/sprites/walk/walk_nude_%i.png", n);
		walk_images_nude[m] = loadImage(walk_nude[m]);
	}

	//loads idle animations
	for (m = 0, n = 1; m < idleFiles2; m++, n++)
	{
		sprintf_s(idle_nude[m], _countof(idle_nude[m]), "./Assets/sprites/idle/idle_nude_%i.png", n);
		idle_images_nude[m] = loadImage(idle_nude[m]);
	}

	//sets pointer array of image toggling
	charAnimations2[0] = walk_images_nude;
	charAnimations2[1] = idle_images_nude;

	//loads font
	consoleText2 = loadFont("./Assets/Fonts/consoleText.ttf");
	textFont(consoleText2, 30);

  //loads shadow
  CShadLS = loadImage("./Assets/Graphics/clock/clockTime_shadow.png");

  //loads clock images into buffer
  for (i = 1, j = 0; i <= 12; i++, j++)
  {
    sprintf_s(clockStringLS[j], _countof(clockStringLS[j]), "./Assets/Graphics/clock/clockTime_%i.png", i);
    clockLS[j] = loadImage(clockStringLS[j]);
  }
}

//------------------------------------------------------------------------------
// Update the scene manager.
void SceneLevelSelectUpdate()
{

  exitTime = 1; //resets fade toggle

	background(0, 0, 0);

  //while no transisions are happening
  if (!waving && alphaCut <= 20)
  {
    //toggles clock seen or not
    if (keyPressed(KEY_Q))
      clockSeen += 255;
    if (clockSeen > 255)
      clockSeen = 0;

    //move right
	  if (keyIsDown(KEY_D))
	  {
      //set direction to facing properly
		  if (charDirectionNUDE == -1)
			  charDirectionNUDE = 1;

      //switch to walk animation buffer
		  walkStop2 = 0;

      //move plater
		  playerPositionNUDE.x += charSpeed;

      //index walk animation
		  walkAnispeed2++;
	  }
	  //move left
	  else if (keyIsDown(KEY_A))
	  {
      //sets player direction to facing left
		  if (charDirectionNUDE == 1)
			  charDirectionNUDE = -1;

      //set animation buffer to walking
		  walkStop2 = 0;

      //move player
		  playerPositionNUDE.x -= charSpeed;

      //index walk animation
		  walkAnispeed2++;
	  }
	  else //when no keys are pressed
	  {
      //set animation buffer to play idle animations
		  walkStop2 = 1;

      //play idle animationm
		  idleAnispeed2++;
	  }
  }

  //players walk sound on frame of foot being put on the ground 
  if (!waving && keyIsDown(KEY_A) || keyIsDown(KEY_D))
  {
    //checks buffer overflow
    if (walksIndex == 2)
      walksIndex = 0;
      
    //players sound on timed event
    if (frameCount % 20 == 0)
      soundChannel(walks[walksIndex++], walkSplat);
  }
      
	//loads background
	image(Hallway, screenPos, (1080 / 2), 1920 * 2.05, 455 * 2.37362373626374, 255);
	image(dlc, level + 1850, 675, 300, 175, 255);
	image(dlc, level + 2400, 600, 275, 375, 255);

	//walk animation speed
  if (walkAnispeed2 % 6 == 0 && walkStop2 == 0)
    walkIdleIndex2++;

	//idle animation speed
	if (idleAnispeed2 % 18 == 0 && walkStop2 == 1)
		walkIdleIndex2++;

	//resets index to avoid buffer overflow
	if (walkIdleIndex2 >= 14 && walkStop2 == 0)
		walkIdleIndex2 = 0;
    if (walkIdleIndex2 >= 4 && walkStop2 == 1)
		walkIdleIndex2 = 0;

	//safty check
	if (walkAnispeed2 == 1000000 || idleAnispeed2 == 1000000)
	{
		walkAnispeed2 = 0;
	  idleAnispeed2 = 0;
	}

	//left collision
	if (playerPositionNUDE.x <= 150)
	{
		playerPositionNUDE.x = playerPositionNUDE.x + charSpeed;

		if (screenPos <= 1920)
		{
			screenPos += charSpeed;
			exit_Collision += charSpeed;
      level += charSpeed;
		}
	}

	//right collision
	if (playerPositionNUDE.x >= 1780)
	{
		playerPositionNUDE.x = playerPositionNUDE.x - charSpeed;

		if (screenPos >= 0)
		{
			screenPos -= charSpeed;
			exit_Collision -= charSpeed;
      level -= charSpeed;
		}
	}
  
	//exit collision
	if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y, playerWidthHeightNUDE.x, playerWidthHeightNUDE.y, exit_Collision, 800, 100, 500))
	{
		strokeWeight(50);
		fill(255, 255, 255, 255);
		text("Press [E] to exit", exit_Collision - 200, 490);

    //enables fade animation
    if (keyPressed(KEY_E))
    {
      quit = 0;
      waving = 1;
    }

		noFill();
	}
  if (quit == 0 && fadeout() == 0)
    Terminate();

  //room 1 collsiion
  if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y,  playerWidthHeightNUDE.x / 2 - 60, playerWidthHeightNUDE.y / 2, level, 600, 200, 300))
  {
    strokeWeight(50);
    fill(255, 255, 255, 255);
    text("Press [E]", level - 130, 440);

    //toggles animations
    if (keyPressed(KEY_E))
    {
      gotoLevel1 = 0;
      waving = 1;
    }

    noFill();
  }
  if (gotoLevel1 == 0 && fadeout() == 0) //go to room 1 after animation is finished
  {
    waving = 0;
    gotoLevel1 = 1;
    SceneManagerSetNextScene(SCENE_ROOM1);
  } 

  //room 2 collision
  if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y, playerWidthHeightNUDE.x / 2 - 60, playerWidthHeightNUDE.y / 2, level + 690, 600, 200, 300))
  {
    strokeWeight(50);
    fill(255, 255, 255, 255);
    text("Press [E]", level + 540, 440);

    //toggles animations
    if (keyPressed(KEY_E))
    {
      gotoLevel2 = 0;
      waving = 1;
    }

    noFill();
  }
  if (gotoLevel2 == 0 && fadeout() == 0) //go to room 2 after animation is finished
  {
    waving = 0;
    gotoLevel2 = 1;
    SceneManagerSetNextScene(SCENE_ROOM2);
  }

  //room 3 collision
  if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y, playerWidthHeightNUDE.x / 2 - 60, playerWidthHeightNUDE.y / 2, level + 1300, 600, 200, 300))
  {
    strokeWeight(50);
    fill(255, 255, 255, 255);
    text("Press [E]", level + 1150, 440);

    //toggles animations
    if (keyPressed(KEY_E))
    {
      gotoLevel3 = 0;
      waving = 1;
    }

    noFill();
  }
  if (gotoLevel3 == 0 && fadeout() == 0) //go to room 3 after animation is finished
  {
    waving = 0;
    gotoLevel3 = 1;
    SceneManagerSetNextScene(SCENE_ROOM3);
  }

  //room 4 collision
  if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y, playerWidthHeightNUDE.x / 2 - 60, playerWidthHeightNUDE.y / 2, level + 1900, 600, 200, 300))
  {
    strokeWeight(50);
    fill(255, 255, 255, 255);
    text("Press [E]", level + 1730, 600);

    //toggles animations
    if (keyPressed(KEY_E))
    {
      gotoLevel4 = 0;
      waving = 1;
    }

    noFill();
  }
  if (gotoLevel4 == 0 && fadeout() == 0) //go to room 4 after animation is finished
  {
    waving = 0;
    gotoLevel4 = 1;
  }

  //room 5 collision
  if (eventCollision(&playerPositionNUDE.x, &playerPositionNUDE.y, playerWidthHeightNUDE.x / 2 - 60, playerWidthHeightNUDE.y / 2, level + 2400, 600, 200, 300))
  {
    strokeWeight(50);
    fill(255, 255, 255, 255);
    text("Press [E]", level + 2265, 450);

    //toggles animations
    if (keyPressed(KEY_E))
    {
      gotoLevel5 = 0;
      waving = 1;
    }

    noFill();
  }
  if (gotoLevel5 == 0 && fadeout() == 0) //go to room 5 after animation is finished
  {
    waving = 0;
    gotoLevel5 = 1;
  }

  //check time text
  text("Check time [Q]", 10, 1048);

 
  //draw clock shadow
  image(CShadLS, playerPositionNUDE.x + 120, 570 + 5 * sin(frameCount * 0.05f), 120, 120, clockSeen);
  //draw clock
  image(clockLS[imIndex], playerPositionNUDE.x + 120, 560 + 5 * sin(frameCount * 0.05f), 120, 120, clockSeen);

  //draw player
  image(charAnimations2[walkStop2][walkIdleIndex2], playerPositionNUDE.x, playerPositionNUDE.y, playerWidthHeightNUDE.x * charDirectionNUDE, playerWidthHeightNUDE.y, 255);

  //black mask for fading in to show task
  if (alphaCut > 0)
  {
    if (timer++ >= 45)
      alphaCut -= 2;

    fill(0, 0, 0, alphaCut);
    rect(0, 0, 1920, 1080);
    textSize(30);
    fill(255, 255, 255, alphaCut);
    text("Face your fears. Don't wake up", 450, 540);
    noFill();
  }
}