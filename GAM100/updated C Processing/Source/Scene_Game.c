//---------------------------------------------------------
// file:	Scene_Game.c
// author:	Anthony Miller
// brief:	Game scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneTable.h"
#include "Scene_Game.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include <stdlib.h> //"countof"
#include <stdio.h>  //"spintf_s"

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
static float rectX;      // x position of rectangle to collect
static float rectY;      // y position of rectangle to collect
static float shipX;		 // hold the starting position for left game ship
static float offSet;     // variable to move the ship from the center
static float holder;	 // holds the time when the game started
static float difference; // hold the time between astroid spawns

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneGameInit()
{
	noStroke();

	//set first square to collect
	rectX = ((float)random() * ((canvasWidth / 2) - 50.0f)) + (canvasWidth / 2);
	rectY = (float)random() * (canvasHeight - 25.0f);

	offSet = 0.0f;
	holder = second();
	difference = 1.3f;
	resetScore();
	resetEnergy();

	//set bullet and astroid arrays to empty
	for (int i = 0; i < 150; i += 2)
	{
		setAstroid(i, 0, 0);
		setShot(i, 0, 0);
	}
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneGameUpdate()
{
	leftGame();
	rightGame();
	checkCollision();
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

/*manages the left game*/
void leftGame(void)
{
	//move left and right
	if (keyIsDown(KEY_A))
	{
		if (offSet * 2.0f > 25.0f - canvasWidth / 4.0f)
		{
			offSet--;
			offSet--;
		}
	}
	else if (keyIsDown(KEY_D))
	{
		if (offSet * 2.0f < canvasWidth / 4.0f - 25.0f)
		{
			offSet++;
			offSet++;
		}
	}

	//set the current x position of the ship
	shipX = canvasWidth / 4.0f + (offSet * 2.0f);

	//shooting
	if (keyPressed(KEY_SPACE) && getEnergy() > 0)
	{
		spawnBullet();
	}
	
	/*spaws an astroid every 2 seconds*/
	if (second() - holder > difference)
	{
		spawnAstroid();
		difference *= 0.99f;
		holder = second();
	}

	//draw all of the objects for the left game onto the screen
	drawLeftGame();
}

/*draw the left game*/
void drawLeftGame(void)
{
	//set background to green
	//backgroundColor(color(0, 0, 0, 255));
	fillColor(color(0, 0, 0, 255));
	rect(0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);

	fillColor(color(255, 255, 255, 255));

	//draw the ship
	triangle(shipX, canvasHeight - 100.0f,    //top point
		shipX - 25.0f, canvasHeight - 50.0f,  //lower left point
		shipX + 25.0f, canvasHeight - 50.0f); //lower right point

	drawBullets();
	updateAstroids();

	//display the energy left
	char buffer[256] = { 0 };
	sprintf_s(buffer, _countof(buffer), "Energy: %d", getEnergy());
	textSize(25.0f);
	text(buffer, (canvasWidth / 2) - 100.0f, 20.0f);
}

/*updates and draws the bullets to the screen*/
void drawBullets(void)
{
	int i; /*looping variable*/

	for (i = 0; i <= 148; i += 2)
	{
		if (getShotX(i) != 0)
		{
			//move bullet up the screen by one
			moveShot(i);

			//make bullet red and draw it
			fillColor(color(255, 0, 0, 255));
			rect(getShotX(i), getShotY(i), 2.0f, 10.0f);

		}
		/*if bullet goes of screen delete it from the array*/
		if (getShotY(i) < 0)
		{
			setShot(i, 0, 0);
		}
	}
}

/*updates and draws the bullets to the screen*/
void updateAstroids(void)
{
	int i; /*looping variable*/

	//look through the array for all valid astroids
	for (i = 0; i <= 148; i += 2)
	{
		//if the astroid exists
		if (getAstroidX(i) != 0)
		{
			//move astroid down the screen
			moveAstroid(i);

			drawAstroids(getAstroidX(i), getAstroidY(i));

		}
		if (getAstroidY(i) > canvasHeight)
		{
			setAstroid(i, 0, 0);
		}
	}
}

/**/
void drawAstroids(float x, float y)
{
	//make astroid white and draw it
	fillColor(color(255, 255, 255, 255));
	rect(x, y, 30.0f, 30.0f);
}

/**/
void spawnBullet(void)
{
	int i; /*looping variable*/

	decrementEnergy();

	//check through array for next open slot
	for (i = 0; i <= 98; i += 2)
	{
		//if slot is open assign a new bullet
		if (getShotX(i) == 0)
		{
			setShot(i, shipX, canvasHeight - 110.0f);
			playShoot();
			return;
		}
	}
}

/**/
void spawnAstroid(void)
{
	int i; /*looping variable*/

	for (i = 0; i <= 98; i += 2)
	{
		if (getAstroidX(i) == 0)
		{
			setAstroid(i, random() * ((canvasWidth / 2.0f) - 30.0f), 0.0f);
			return;
		}
	}
}

/*manages the right game*/
void rightGame(void)
{
	char buffer[256] = { 0 };

	//gets rid of the cursor while it is in the screen
	noCursor();

	//draw background of right game
	fillColor(color(0, 255, 0, 255));
	rect(canvasWidth / 2.0f, 0.0f, canvasWidth / 2.0f, canvasHeight * 1.0f);

	//draws a blue circle where the mouse is
	//int mPositionX = mouseX;
	//int mPositionY = mouseY;
	drawMouse();

	//draw the block to collect
	fillColor(color(252, 0, 0, 255));
	rect(rectX, rectY, 50.0f, 25.0f);

	//display the score
	sprintf_s(buffer, _countof(buffer), "Score: %d", getScore());
	text(buffer, canvasWidth - 100.0f, 20.0f);
}

/*draws the circle over the mouse position for the right game*/
void drawMouse(void)
{
	//set circle to blue
	fillColor(color(0, 0, 255, 255));

	//if mouse is in the window
	if ((mouseY > 6 && canvasHeight - 6 > mouseY) && (mouseX > (canvasWidth / 2) + 6 && canvasWidth - 6 > mouseX))
	{
		//draw the circle where the mouse is
		circle(mouseX, mouseY, 10.0f);
	}
	//if the mouse is to the right of the screen
	else if (mouseX > canvasWidth - 7)
	{
		//if the mouseY cordinate is inline with the window
		if (mouseY > 6 && canvasHeight - 6 > mouseY)
		{
			circle(canvasWidth - 6.0f, mouseY, 5.0f);
		}
		//if the mouseY cordinate is above the window
		else if (mouseY < 7)
		{
			circle(canvasWidth - 6.0f, 6.0f, 5.0f);
		}
		//if the mouseY cordinate is below the window
		else
		{
			circle(canvasWidth - 6.0f, canvasHeight - 6.0f, 5.0f);
		}
	}
	//if the mouse is to the left of the right game
	else if (mouseX < (canvasWidth / 2.0f) + 7.0f)
	{
		//if the mouseY cordinate is inline with the window
		if (mouseY > 7.0f && canvasHeight - 7.0f > mouseY)
		{
			circle((canvasWidth / 2.0f) + 6.0f, mouseY, 5.0f);
		}
		//if the mouseY cordinate is above the window
		else if (mouseY < 7.0f)
		{
			circle((canvasWidth / 2.0f) + 6.0f, 6.0f, 5.0f);
		}
		//if the mouseY cordinate is below the window
		else
		{
			circle((canvasWidth / 2.0f) + 6.0f, canvasHeight - 6.0f, 5.0f);
		}
	}
	//if the mouse is below the right game
	else if (mouseY > canvasHeight - 6.0f)
	{
		//if the mouseX cordinate is inline with the window
		if (mouseX > (canvasWidth / 2.0f) + 6.0f && canvasWidth - 6.0f > mouseX)
		{
			circle(mouseX, canvasHeight - 6.0f, 5.0f);
		}
		//if the mouseX cordinate is to the left of the right game
		else if (mouseX < (canvasWidth / 2.0f) - 7.0f)
		{
			circle((canvasWidth / 2.0f) - 6.0f, 6.0f, 5.0f);
		}
		//if the mouseX cordinate is to the right the window
		else
		{
			circle(canvasWidth - 6.0f, canvasHeight - 6.0f, 5.0f);
		}
	}
	//if the mouse is above the right game
	else if (mouseY < 7.0f)
	{
		//if the mouseX cordinate is inline with the window
		if (mouseX > (canvasWidth / 2.0f) + 7.0f && canvasWidth - 7.0f > mouseX)
		{
			circle(mouseX, 6.0f, 5.0f);
		}
		//if the mouseX cordinate is to the left of the right game
		else if (mouseX < (canvasWidth / 2.0f) - 7.0f)
		{
			circle((canvasWidth / 2.0f) - 6.0f, 6.0f, 5.0f);
		}
		//if the mouseX cordinate is to the right the window
		else
		{
			circle(canvasWidth - 6.0f, 6.0f, 5.0f);
		}
	}
}

/**/
void checkCollision()
{
	int i, j = 0; //looping variables

	//itterate through astroids array
	for (i = 0; i < 150; i += 2)
	{
		//itterate through the bullets array
		for (j = 0; j < 150; j += 2)
		{
			//when the bullet is within the column of the astroid and above the bottom side
			if (getAstroidX(i) < getShotX(j) && getShotX(j) + 2.0f < getAstroidX(i) + 30.0f && getAstroidY(i) + 30.0f > getShotY(j))
			{
				//remove the coresponding bullet and astoid
				setAstroid(i, 0.0f, 0.0f);
				setShot(j, 0.0f, 0.0f);
				playAstroidExplosion();
				incrementScore();
			}
		}
	}
	//itterate through astroids array
	for (i = 0; i < 150; i += 2)
	{
		//if the ship is in the column of the current astroid and the astroid is bellow the front of the ship
		if ((getAstroidX(i) < shipX + 25.0f && shipX - 25.0f < getAstroidX(i) + 30.0f) &&
        (getAstroidY(i) + 30.0f > canvasHeight - 100.0f) && (getAstroidY(i) < canvasHeight - 50.0f))
		{
			playShipExplosion();
			SceneManagerSetNextScene(SCENE_GAMEOVER);
		}
	}
	//reset where the block is when one is collected and increase the score
	if ((rectX <= mouseX + 10.0f && mouseX - 10.0f <= rectX + 50.0f) && (rectY <= mouseY + 10.0f && mouseY - 10.0f <= rectY + 25.0f))
	{
		rectX = ((float)random() * ((canvasWidth / 2) - 50.0f)) + (canvasWidth / 2);
		rectY = (float)random() * (canvasHeight - 25.0f);
		incrementScore();
		incrementEnergy();
		playSnare();
	}
}

