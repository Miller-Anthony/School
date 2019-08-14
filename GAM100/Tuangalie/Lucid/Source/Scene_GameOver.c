//---------------------------------------------------------
// file:	Scene_GameOver.c
// author:	Tristan Bouchard
// brief: time checking/game over scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_DigiPenLogo.h"
#include "SceneManager.h"


//GLOBAL VARIABLES
extern int TIME;    //time global
extern int imIndex; //index for clock image array
//================

int timerGO = 0;     //timer for tracking timed events
int exitTime = 1;    //toggles if you are able to leave
int endBoi;          //checks what time and if its 11 going to 12     
int changeClock = 0; //ticks clock
int startFade = 180; //start fade function

PImage CShadGO;     //image for clock shadow
PImage clockGO[12]; //array of clock images

char clockStringGO[12][256] = { 0 }; // 12 files names and 256 possible characters in the file path

PChannel clockTick; //noise channel for sounds
PSound timeChange;  //init sound when entering the map

void SceneGameOverInit()
{
  int i, j;
  background(0, 0, 0);

  //loads sounds
  timeChange = loadSound("./Assets/timeChangeSound.wav", 0);

  //loads shadow
  CShadGO = loadImage("./Assets/Graphics/clock/clockTime_shadow.png");

  //load clock sprites
  for (i = 1, j = 0; i <= 12; i++, j++)
  {
    sprintf_s(clockStringGO[j], _countof(clockStringGO[j]), "./Assets/Graphics/clock/clockTime_%i.png", i);
    clockGO[j] = loadImage(clockStringGO[j]);
  }
  i = 0;

  //create channel
  clockTick = createChannel("yeet");
  setPitch(clockTick, 50);
  while (i++ < 2)
  {
    setReverb(clockTick, 1);
  }
  setVolume(clockTick, 1);
  soundChannel(timeChange, clockTick);

  //resets time if 12
  if (TIME == 12)
    TIME = 1;
}

//get sound working for changing the time.
//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneGameOverUpdate()
{
  background(0, 0, 0);
  int holder = imIndex;
  if (timerGO++ == 100)
  {
    imIndex++;
    TIME++;
  }
    
  if (timerGO == startFade)
    exitTime = 0;

  if (holder == 11)
    endBoi = 1;

if (imIndex == 12)
    imIndex = 0;
  //draw clock shadow
  image(CShadGO, 880, 540, 800, 800, 255);
  //draw clock
  image(clockGO[imIndex], 900, 540, 800, 800, 255);

  

  //perform exit fade
  if (exitTime == 0 && fadein() == 0)
  {
    timerGO = 0;
    if (endBoi == 1)
    {
      SceneManagerSetNextScene(SCENE_GAME);  
      TIME = 12;
    }
    else if (endBoi != 1)
      SceneManagerSetNextScene(SCENE_LEVEL_SELECT);
  }
    
}
    

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

