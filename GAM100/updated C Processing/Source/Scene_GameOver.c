//---------------------------------------------------------
// file:	Scene_GameOver.c
// author:	Anthony Miller
// brief:	Game Over scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_GameOver.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include <stdlib.h> //"countof"
#include <stdio.h>

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

static FILE *fp;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------
static void drawScreen();
static void drawMenu();
static void checkClick();
static void updateHighScore();
static void drawHighScore();

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneGameOverInit()
{
  cursor();
  updateHighScore();
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneGameOverUpdate()
{
	drawScreen();

	if (mouseClicked())
	{
		checkClick();
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

/*******************************
*draws the whole screen
*******************************/
void drawScreen()
{
	//stores the text to display to the screen
	char buffer[256] = { 0 }; 

	//set background to black
	//background(0, 0, 0);
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

	drawMenu();
	drawHighScore();

	//set the gameover text color to white
	fillColor(color(255, 255, 255, 255));

	//set text size
	textSize(60);

	//modify and display the gameover text
	sprintf_s(buffer, _countof(buffer), "GAME OVER \nTotal Score: %d", getScore());
	text(buffer, canvasWidth / 4.0F, canvasHeight / 3.0F);

	//print out the credits
	textSize(20);
	text("Made by Anthony Miller, Justin Chaimbers copywright DigiPen 2018", 10.0f, canvasHeight - 10.0f);
}

/*******************************
*draws the buttons for the menu
*******************************/
void drawMenu()
{
	//set button color to white
	fillColor(color(255, 255, 255, 255));

	//draw retry button
	rect((canvasWidth / 2.0f) + 75.0f, (canvasHeight / 2.0f) - 40.0f, 150.0f, 40.0f);

	//draw Main Menu button
	rect((canvasWidth / 2.0f) + 75.0f, (canvasHeight / 2.0f) + 40.0f, 150.0f, 40.0f);

	//draw Main Menu button
	rect((canvasWidth / 2.0f) + 75.0f, (canvasHeight / 2.0f) + 120.0f, 150.0f, 40.0f);

	//set fill color for the button text
	fillColor(color(0, 0, 0, 255));

	//set text size
	textSize(30);

	//display the text for the retry button
	text("Retry", (canvasWidth / 2.0F) + 110.0f, (canvasHeight / 2.0F) - 15.0f);

	//display the text for the retry button
	text("Main Menu", (canvasWidth / 2.0F) + 90.0f, (canvasHeight / 2.0F) + 65.0f);

	//display the text for the exit button
	text("Quit Game", (canvasWidth / 2.0F) + 90.0f, (canvasHeight / 2.0F) + 145.0f);
}

/*******************************
*checks if the mouse is clicked and handles the results
*******************************/
void checkClick()
{
	//check if mouse is in the right area on the x axis
	if ((canvasWidth / 2.0f) + 75.0f < mouseX && mouseX < (canvasWidth / 2.0f) + 225.0f)
	{
		//if mouse within retry button
		if ((canvasHeight / 2.0f) - 40.0f < mouseY && mouseY < (canvasHeight / 2.0f))
		{
			SceneManagerSetNextScene(SCENE_GAME);
		}

		//if mouse within main menu button
		if ((canvasHeight / 2.0f) + 40.0f < mouseY && mouseY < (canvasHeight / 2.0f) + 80.0f)
		{
			SceneManagerSetNextScene(SCENE_MAIN_MENU);
		}

		//if mouse within Quit Game button
		if ((canvasHeight / 2.0f) + 120.0f < mouseY && mouseY < (canvasHeight / 2.0f) + 160.0f)
		{
			Terminate();
		}
	}

	
	
}

/*******************************
*updates the high score information
*******************************/
void updateHighScore()
{
	int i, j; //looping variable

	for (i = 0; i < 10; i++)
	{
		if (getScore() > getHighScore(i))
		{
			for (j = 9; j > i; j--)
			{
				setHighScore(getHighScore(j - 1), j);
			}
			setHighScore(getScore(), i);
			break;
		}
	}
	int err = fopen_s(&fp, "./Assets/HighScores.txt", "wt");
	if (!err)
	{
		for (i = 0; i < 10; i++)
		{
			fprintf(fp, "%d\n", getHighScore(i));
		}
		fclose(fp);
	}
}

/*******************************
*updates the high score information
*******************************/
void drawHighScore()
{
	int i; //looping variable
	char holder[256]; //for converting score to string

	//set text size
	textSize(20);

	//set button color to white
	fillColor(color(255, 255, 255, 255));

	for (i = 0; i < 10; i++)
	{
		//modify and display the gameover text
		sprintf_s(holder, _countof(holder), "%2i:%6.4d", i + 1, getHighScore(i));
		text(holder, canvasWidth / 4.0F, (canvasHeight / 2.0F) + (i * 30.0f));
	}
}