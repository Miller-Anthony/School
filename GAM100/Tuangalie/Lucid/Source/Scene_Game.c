//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Justin Chambers
// brief:	DigiPen Logo scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_DigiPenLogo.h"
#include "SceneManager.h"

static PImage GameLOGO;     //game logo image

static int timerEnd = 0;    //end timer
static int alphaMale = 0;   //alpha for game logo image
static int startSound = 60; //starts the sound on fram set
static int startFade = 180; //start fading on frame set
    
PChannel mixer; //sound channel
PSound alarm;   //sound alarm
//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneGameInit()
{
  //set sound stuff
  mixer = createChannel("4AM");
  setVolume(mixer, 1);
  setFade(mixer, 0, 4);
  setReverb(mixer, 100);
  alarm = loadSound("./Assets/Notes/alarm.wav", 0);
  GameLOGO = loadImage("./Assets/gamelogo.png");
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneGameUpdate()
{
  background(0, 0, 0); 
  timerEnd++;
  //player sound on frame set
  if (timerEnd == startSound)
    soundChannel(alarm, mixer);

  //start fade on said frame set, add to alphaMale
  if (timerEnd >= startFade)
    image(GameLOGO, 960, 540, 1920, 1080, alphaMale++);

  //stuff for removing text and adding new text
  textSize(40);
  fill(0, 0, 0, 255);
  rect(700, 700, 500, 300);
  fill(156, 8, 80, alphaMale);
  text("Press {E} to open your eyes", 350, 700);

  //enables E and stops alpha changes
  if (alphaMale >= 250)
	  if (keyPressed(KEY_E))
		  Terminate();
  noFill();
}