//---------------------------------------------------------
// file:	Engine.c
// author:	Tristan Bouchard
// brief:	Basic game engine organization/ transition store
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Engine.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <stdio.h>

//====================================FADE VARIABLES====================================================
//fade out
int alpharectOUT = 0;  //alpha for rectangle 
int xpos = 960;        //image x position
int ypos = 540;        //image y position   
int alphaIMGwavy2 = 0; //image alpha
int time = 0;          //time check for timed events

PSound transIN;  //transision in sound
PSound transOUT; //sound for transitioning ouit

PImage wavy2;                //wavy image
PImage walk_images_nude[14]; //image buffer for drawing nude player walking animations
PImage idle_images_nude[4];  //image buffer for drawing nude player idle animations


char idle_nude[4][256];  //changing path to image buffer
char walk_nude[14][256]; //changing path to image buffer

//---------------------------------------------------------
// Initialize managers and systems in the engine.
void EngineInit()
{
  //load sounds
  transIN = loadSound("./Assets/transIN.wav", 0);
  transOUT = loadSound("./Assets/transOUT.wav", 0);

  //load fade images.
	fadeLoad();

  //set image flags
	setImageFlags(CP_IMAGE_NEAREST);

  //fullscreen the program
	fullscreen();

  SceneManagerInit();
}

//---------------------------------------------------------
// Update managers and systems in the engine.
void EngineUpdate()
{
	SceneManagerUpdate();
	InputManagerUpdate();
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

void fadeLoad(void)
{
	wavy2 = loadImage("./Assets/Graphics/Transition/bigwavy2.png");
}

//FADE OUT FUNCTION
int fadeout(void)
{
  if (time == 0)     //player sound on first frame
    sound(transOUT);

	time++; //increase time

  //while the image is not fully seen
	if (alpharectOUT <= 254)
	{
		xpos += 7; //move x of image
		ypos -= 7; //move y of image


		if (alpharectOUT <= 254 && time >= 1 * 30) //stops alpha from going to 256
			alpharectOUT += 4;
		else
			alphaIMGwavy2 += 5;

		blendMode(CP_BLEND_SUBTRACT);

		image(wavy2, xpos, ypos, 4000, 4000, alphaIMGwavy2); //draw image
	}
  else
  {
    //reset all variables
    time = 0;
    alpharectOUT = 0;
    xpos = 0;
    ypos = 0;
    return 0;
  }

	fill(255, 255, 255, alpharectOUT); //set fill color
	rect(0, 0, 1920, 1080);            //draw rectangle/mask
	noFill();
	blendMode(CP_BLEND_ALPHA);

	return 1;
}

//FADE IN FUNCTION
int fadein(void)
{
  if (time == 0)    //plays ousnd on first frame
    sound(transIN);

  time++;
  
  //while the images isnt fully seen
  if (alpharectOUT <= 254)
  {
    xpos += 7; //move x of image
    ypos -= 7; //move y of image

    if (alpharectOUT <= 254 && time >= 1 * 30) //stops alpha from going to 256
      alpharectOUT += 4;
    else
      alphaIMGwavy2 += 5;

    blendMode(CP_BLEND_SUBTRACT);

    image(wavy2, xpos, ypos, 4000, 4000, alphaIMGwavy2); //draw image
  }
  else
  {
    //reset variables
    time = 0;
    alpharectOUT = 0;
    xpos = 0;
    ypos = 0;
    return 0;
  }

  fill(255, 255, 255, alpharectOUT); //set fill color
  rect(0, 0, 1920, 1080);            //draw rectangle/mask
  noFill();
  blendMode(CP_BLEND_ALPHA);

  return 1;
}