//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Justin Chambers
// brief:	DigiPen Logo scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_DigiPenLogo.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"

#define START 0
#define MOVING 1
#define MOVED 2

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
// Private Variables:
//---------------------------------------------------------
static PImage logo;                    //digipen logo holder
static float sparks[10];               //holds the x,y cordinates of opening screen sparkles even is x odd is y
static float offSet;                   //variable to move the logo from the center
static float timer;                    //timer for the logo state
static int introState;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------
void start(void);
void moving(void);
void moved(void);
void drawSparkle(float x, float y, float change);

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneDigiPenLogoInit()
{
	introState = START;
	timer = second();
  noCursor();
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneDigiPenLogoUpdate()
{
	switch (introState)
	{
	case START:
		start();
		break;
	case MOVING:
		moving();
		break;
	case MOVED:
		moved();
		break;
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

/**/
void start(void)
{
	//background(0, 0, 0);
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

	//load digipen logo
	logo = loadImage("./Assets/DigiPen_RED_1024px.png");

	//display digipen logo
	image(logo, canvasWidth / 2.0f, canvasHeight / 2.0f,
		canvasWidth / 2.0f - 20.0f, 280.0f);

	//start logo animation after 3 seconds
	if (timer < second() - 3.0f)
	{
		offSet = 0.0f;
		introState = MOVING;
	}
}

/**/
void moving(void)
{
	//set displacment of image
	if (((canvasWidth / 2.0f) - offSet) > canvasWidth / 4.0f)
	{
		offSet++;
	}

	//set background to black
	//backgroundColor(color(0, 0, 0, 255));
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

	//display digipen logo left
	image(logo, (canvasWidth / 2.0f) - offSet, canvasHeight / 2.0f,
		(canvasWidth / 2.0f) - 20.0f, 280.0f);

	//display digipen logo right
	image(logo, (canvasWidth / 2.0f) + offSet - 7.0f, canvasHeight / 2.0f - 7.0f,
		(canvasWidth / 2.0f) - 20.0f, 290.0f);

	//no boarder on drawn objects
	noStroke();

	//when mouse is clicked, start the game
	if (mouseClicked())
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
	if (offSet >= canvasWidth / 4.0f)
	{
		introState = MOVED;
	}
}

/*draws sparkles in random places around the digipen logo*/
void moved(void)
{
	//holder variable for triangle offsets
	int holder;

	//set background to black
	//backgroundColor(color(0, 0, 0, 255));
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

	//set position of first sparkle
	if ((int)second() % 10 == 0)
	{
		sparks[0] = (float)random() * (canvasWidth / 2.0f);
		sparks[1] = ((float)random() * (canvasHeight / 2.0f) + (canvasHeight / 4.0f));
	}

	//draw first sparkle
	if ((int)second() % 10 > 0)
	{
		//set color of sparkle to white
		fillColor(color(255, 255, 255, 255 / ((int)second() % 10)));
		holder = (int)second() % 10;
		drawSparkle(sparks[0], sparks[1], (float)holder);
	}

	//set position for fourth sparkle
	if ((int)second() % 8 == 0)
	{
		sparks[2] = (float)random() * (canvasWidth / 2.0f);
		sparks[3] = ((float)random() * (canvasHeight / 2.0f) + (canvasHeight / 4.0f));
	}

	//draw second sparkle
	if ((int)second() % 8 > 0)
	{
		//set color of sparkle to white
		fillColor(color(255, 255, 255, 255 / ((int)second() % 8)));

		holder = (int)second() % 8;
		//draw the sparkle
		drawSparkle(sparks[2], sparks[3], (float)holder);
	}

	//set position of third sparkle
	if ((int)second() % 6 == 0)
	{
		sparks[4] = (float)random() * (canvasWidth / 2.0f);
		sparks[5] = ((float)random() * (canvasHeight / 2.0f) + (canvasHeight / 4.0f));
	}

	//draw third sparkle
	if ((int)second() % 6 > 0)
	{
		//set color of sparkle to white
		fillColor(color(255, 255, 255, 255 / ((int)second() % 6)));

		holder = (int)second() % 6;
		//draw the sparkle
		drawSparkle(sparks[4], sparks[5], (float)holder);
	}

	//display digipen logo left
	image(logo, (canvasWidth / 2.0f) - offSet, canvasHeight / 2.0f,
		(canvasWidth / 2.0f) - 20.0f, 280.0f);

	//display digipen logo right
	image(logo, (canvasWidth / 2.0f) + offSet - 6.0f, canvasHeight / 2.0f - 6.0f,
		(canvasWidth / 2.0f) - 20.0f, 290.0f);

	//set position of second sparkle
	if ((int)second() % 5 == 0)
	{
		sparks[6] = (float)random() * (canvasWidth / 2.0f);
		sparks[7] = (float)random() * ((canvasHeight / 2.0f) + (canvasHeight / 4.0f));
	}

	//draw second sparkle
	if ((int)second() % 5 > 0)
	{
		//set color of sparkle to white
		fillColor(color(255, 255, 255, 255 / ((int)second() % 5)));
		holder = (int)second() % 5;
		drawSparkle(sparks[6], sparks[7], (float)holder);
	}

	//set position of fourth sparkle
	if ((int)second() % 4 == 0)
	{
		sparks[8] = (float)random() * (canvasWidth / 2.0f);
		sparks[9] = (float)random() * ((canvasHeight / 2.0f) + (canvasHeight / 4.0f));
	}

	//draw fourth sparkle
	if ((int)second() % 4 > 0)
	{
		//set color of sparkle to white
		fillColor(color(255, 255, 255, 255 / ((int)second() % 4)));

		holder = (int)second() % 4;
		//draw the sparkle
		drawSparkle(sparks[8], sparks[9], (float)holder);
	}

	//when mouse is clicked, start the game
	if (mouseClicked())
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
}

/**/
void drawSparkle(float x, float y, float change)
{
	//draw sparkle on left side
	triangle(x - 4.0f - change, y - 9.0f - change,  // point 1
		x + 9.0f + (change * 1.5f), y,  // point 2
		x - 4.0f - change, y + 9.0f + change); // point 3
	triangle(x - 9.0f - (change * 1.5f), y,  // point 1
		x + 4.0f + change, y - 9.0f - change,  // point 2
		x + 4.0f + change, y + 9.0f + change); // point 3

	  //draw sparkle on right side
	triangle(x - 4.0f + (canvasWidth / 2.0f) - 10.0f - change, y - 9.0f - 10.0f - change,  // point 1
		x + 9.0f + (canvasWidth / 2.0f) - 10.0f + (change * 1.5f), y - 10.0f,  // point 2
		x - 4.0f + (canvasWidth / 2.0f) - 10.0f - change, y + 9.0f - 10.0f + change); // point 3
	triangle(x - 9.0f + (canvasWidth / 2.0f) - 10.0f - (change * 1.5f), y - 10.0f,  // point 1
		x + 4.0f + (canvasWidth / 2.0f) - 10.0f + change, y - 9.0f - 10.0f - change,  // point 2
		x + 4.0f + (canvasWidth / 2.0f) - 10.0f + change, y + 9.0f - 10.0f + change); // point 3
}
