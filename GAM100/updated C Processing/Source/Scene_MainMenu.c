//---------------------------------------------------------
// file:	Scene_MainMenu.c
// author:	Justin Chambers
// brief:	Main menu scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_MainMenu.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"

#define TRUE 1
#define FALSE 0


//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static float timer;
static int pastX;
static int pastY;
static int isTriggered;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void drawScreen();
static void drawMenu();
static void checkClick();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Initialize the scene manager.
void SceneMainMenuInit()
{
	timer = second();
  cursor();
  isTriggered = FALSE;
}

//------------------------------------------------------------------------------
// Update the scene manager.
void SceneMainMenuUpdate()
{
	//if mouse moved, reset timer
	if (mouseX != pastX && mouseY != pastY)
	{
		timer = second();
	}

	//draw the menu
	drawScreen();

	//handle mouse clicks
	if (mouseClicked())
	{
		checkClick();
		timer = second();
	}

	//if the mouse has sat for 10 seconds return to the logo scene
	if (timer < second() - 10.0f)
	{
		SceneManagerSetNextScene(SCENE_DIGIPEN_LOGO);
	}

	//set the last position of the mouse for timer checking
	pastX = mouseX;
	pastY = mouseY;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

/*******************************
*draws the buttons for the menu
*******************************/
void drawScreen()
{
	//set background to black
	//background(0, 0, 0);
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

  if (isTriggered)
  {
    //set text color
    fillColor(color(255, 255, 255, 255));

    //draw the how to play info
	textSize(60);
    text("How to play", canvasWidth / 2.6f, canvasHeight / 7.0F);

	//what game this sides instructions are for
    textSize(30);
    text("Left Game", canvasWidth / 4.0F, canvasHeight / 5.0F);
	text("Right Game", (canvasWidth / 2.0F) + (canvasWidth / 7.0F), canvasHeight / 5.0F);

	//the instructions for each game
	textSize(20);
	text("A - Move Left", canvasWidth / 4.0F, (canvasHeight / 5.0F) + 30.0f);
	text("D - Move Right", canvasWidth / 4.0F, (canvasHeight / 5.0F) + 60.0f);
	text("Space Bar - Shoot (consumes energy)", canvasWidth / 4.0F, (canvasHeight / 5.0F) + 90.0f);
    
	text("Ball follows the mouse", (canvasWidth / 2.0F) + (canvasWidth / 7.0F), (canvasHeight / 5.0F) + 30.0f);
	text("Move the mouse over a rectangle to collect energy", 
		  (canvasWidth / 2.0F) + (canvasWidth / 7.0F), (canvasHeight / 5.0F) + 60.0f);
  }
  else
  {
    //set text size and color
    fillColor(color(255, 255, 255, 255));
    textSize(90);
    //modify and display the gameover text
    text("CROSS SHOT X!!!", canvasWidth / 4.0F, canvasHeight / 3.0F);
  }

	drawMenu();
}

/*******************************
*draws the buttons for the menu
*******************************/
void drawMenu()
{
	//set button color to white
	fillColor(color(255, 255, 255, 255));

	//draw retry button
	rect((canvasWidth / 2.0f) - 75.0f, (canvasHeight / 2.0f) - 40.0f, 150.0f, 40.0f);

  //draw how to play button
  rect((canvasWidth / 2.0f) - 75.0f, (canvasHeight / 2.0f) + 40.0f, 150.0f, 40.0f);

	//draw Main Menu button
	rect((canvasWidth / 2.0f) - 75.0f, (canvasHeight / 2.0f) + 120.0f, 150.0f, 40.0f);

	//set fill color for the button text
	fillColor(color(0, 0, 0, 255));

	//set text size
	textSize(30);

	//display the text for the retry button
	text("Play Game", (canvasWidth / 2.0F) - 60.0f, (canvasHeight / 2.0F) - 15.0f);

  //display the text for the retry button
  text("How to Play", (canvasWidth / 2.0F) - 70.0f, (canvasHeight / 2.0F) + 65.0f);

	//display the text for the exit button
	text("Quit Game", (canvasWidth / 2.0F) - 60.0f, (canvasHeight / 2.0F) + 145.0f);
}

/*******************************
*checks if the mouse is clicked and handles the results
*******************************/
void checkClick()
{
	//check if mouse is in the right area on the x axis
	if ((canvasWidth / 2.0f) - 75.0f < mouseX && mouseX < (canvasWidth / 2.0f) + 75.0f)
	{
		//if mouse within Play Game button
		if ((canvasHeight / 2.0f) - 40.0f < mouseY && mouseY < (canvasHeight / 2.0f))
		{
			SceneManagerSetNextScene(SCENE_GAME);
		}

    //if mouse within Play Game button
    if ((canvasHeight / 2.0f) + 40.0f < mouseY && mouseY < (canvasHeight / 2.0f) + 80.0f)
    {
      if (isTriggered)
      {
        isTriggered = FALSE;
      }
      else
      {
        isTriggered = TRUE;
      }
    }

		//if mouse within Quit Game button
		if ((canvasHeight / 2.0f) + 120.0f < mouseY && mouseY < (canvasHeight / 2.0f) + 160.0f)
		{
      Terminate();
		}
	}
}