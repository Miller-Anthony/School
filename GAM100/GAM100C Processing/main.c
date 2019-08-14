//---------------------------------------------------------
// file:	main.c
// author:	Anthony Miller
// email:	Anthony.m@digipen.edu
// course:	GAM100-F18-D
//
// brief:	Main entry point for the sample project
//			of the C_Processing library
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <windows.h>
#include "C_Processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//gamestate defines
#define START 0
#define MOVING 1
#define MOVED 2
#define MENU 3
#define PLAYING 4
#define END 5

#define LEFT 1
#define RIGHT 2


/*prototypes*/
void start(void);
void moving(void);
void moved(void);
void drawSparkle(float x, float y, float offSet);
void menu(void);
void playing(void);
void leftGame(void);
void drawLeftGame(void);
void drawBullets(void);
void updateAstroids(void);
void drawAstroids(float x, float y);
void spawnBullet(void);
void spawnAstroid(void);
void rightGame(void);
void drawMouse(void);
void checkCollision(int game);
void end(void);

/*initilization of sounds*/
PSound snare;                   //holds the sound of a snare
PSound shoot;                   //holds the sound for shooting
PSound aExplode;                //holds the sound of an astroid explosion
PSound sExplode;                //holds the sound of a ship explosion

/*initilization of images*/
PImage logo;                    //digipen logo holder

/*initilization of variables*/
float rectX;                    //x position of rectangle to collect
float rectY;                    //y position of rectangle to collect
int score = START;              //how many rectangles have been collected
int energy = START;             //how much energy you have for shooting
float offSet;                   //variable to move the logo from the center
int gameState = START;          //gamestate
float sparks[10];               //holds the x,y cordinates of opening screen sparkles even is x odd is y
float shipX;				    //stores the x position of the ship in the left game
float bullets[100];             //stores the coordinates of all the bullets
float astroids[100];			//stores the coordinates of all the astroids



// when used with Run() this function will be called once at the beginning of the program
void init()
{
	//set the resolution to 1000x800
	size(1200, 800);

  //fullscreen();

  noStroke();

	//set the snare variable to the snare sound file
	snare = loadSound("./Assets/Snare.wav", 0);
	shoot = loadSound("./Assets/pew.wav", 0);
	aExplode = loadSound("./Assets/astroidExplode.wav", 0);
	sExplode = loadSound("./Assets/ShipExplode.wav", 0);

	//set the initial ship position
	shipX = windowWidth / 4.0f;
}

// when used with Run() this function will be called repeatedly every frame
void update()
{
  switch (gameState)
	{	
		case START :
      start();
      break;
			
		case MOVING :
      moving();
			break;

    case MOVED:
      moved();
      break;

    case MENU:
      menu();
      break;

		case PLAYING :
      playing();
      break;

    case END:
      end();
      break;
	}
}

// main() the starting point for the program
// Run() is used to tell the program which init and update functions to use.
int main(void)
{    
    Run(init, update);
    return 0;
}

/**/
void start(void)
{
  //load digipen logo
  logo = loadImage("./Assets/DigiPen_RED_1024px.png");

  //display digipen logo
  image(logo, windowWidth / 2.0f, windowHeight / 2.0f,
    windowWidth / 2.0f - 20.0f, 280.0f);

  //start logo animation after 3 seconds
  if (3 < second())
  {
    offSet = 0.0f;
    gameState = MOVING;
  }
}

/**/
void moving(void)
{
  //set displacment of image
  if (((windowWidth / 2.0f) - offSet) > windowWidth / 4.0f)
  {
    offSet++;
  }

  //set background to black
  backgroundColor(color(0, 0, 0, 255));

  //display digipen logo left
  image(logo, (windowWidth / 2.0f) - offSet, windowHeight / 2.0f,
    (windowWidth / 2.0f) - 20.0f, 280.0f);

  //display digipen logo right
  image(logo, (windowWidth / 2.0f) + offSet - 7.0f, windowHeight / 2.0f - 7.0f,
    (windowWidth / 2.0f) - 20.0f, 290.0f);

  //no boarder on drawn objects
  //noStroke();

  //when mouse is clicked, start the game
  if (mouseClicked())
  {
	  gameState = MENU;
  }
  if (offSet >= windowWidth / 4.0f)
  {
	  gameState = MOVED;
  }
}

/*draws sparkles in random places around the digipen logo*/
void moved(void)
{
  //holder variable for triangle offsets
  int holder;

	//set background to black
	backgroundColor(color(0, 0, 0, 255));
	
		//set position of first sparkle
		if ((int)second() % 10 == 0)
		{
			sparks[0] = (float)random() * (windowWidth / 2.0f);
			sparks[1] = ((float)random() * ((windowHeight / 2.0f)) + (windowHeight / 4.0f));
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
		sparks[2] = (float)random() * (windowWidth / 2.0f);
		sparks[3] = ((float)random() * ((windowHeight / 2.0f)) + (windowHeight / 4.0f));
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
			sparks[4] = (float)random() * (windowWidth / 2.0f);
			sparks[5] = ((float)random() * ((windowHeight / 2.0f)) + (windowHeight / 4.0f));
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
		image(logo, (windowWidth / 2.0f) - offSet, windowHeight / 2.0f,
			(windowWidth / 2.0f) - 20.0f, 280.0f);

		//display digipen logo right
		image(logo, (windowWidth / 2.0f) + offSet - 6.0f, windowHeight / 2.0f - 6.0f,
			(windowWidth / 2.0f) - 20.0f, 290.0f);

    //set position of second sparkle
    if ((int)second() % 5 == 0)
    {
		sparks[6] = (float)random() * (windowWidth / 2.0f);
		sparks[7] = ((float)random() * ((windowHeight / 2.0f)) + (windowHeight / 4.0f));
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
			sparks[8] = (float)random() * (windowWidth / 2.0f);
			sparks[9] = ((float)random() * ((windowHeight / 2.0f)) + (windowHeight / 4.0f));
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
		gameState = MENU;
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
  triangle(x - 4.0f + (windowWidth / 2.0f) - 10.0f - change, y - 9.0f - 10.0f - change,  // point 1
    x + 9.0f + (windowWidth / 2.0f) - 10.0f + (change * 1.5f), y - 10.0f,  // point 2
    x - 4.0f + (windowWidth / 2.0f) - 10.0f - change, y + 9.0f - 10.0f + change); // point 3
  triangle(x - 9.0f + (windowWidth / 2.0f) - 10.0f - (change * 1.5f), y - 10.0f,  // point 1
    x + 4.0f + (windowWidth / 2.0f) - 10.0f + change, y - 9.0f - 10.0f - change,  // point 2
    x + 4.0f + (windowWidth / 2.0f) - 10.0f + change, y + 9.0f - 10.0f + change); // point 3
}

/*the menu system*/
void menu(void)
{
	//set first square to collect
	rectX = ((float)random() * (windowWidth / 2)) + (windowWidth / 2);
	if (rectX > windowWidth - 50.0f)
	{
		rectX = windowWidth - 50.0f;
	}
	rectY = (float)random() * (windowHeight - 25.0f);
	offSet = 0.0f;

	//set score and energy to starting values
	score = START;
	energy = START;

	//set bullet and astroid arrays to empty
	for (int i = 0; i < 100; i += 2)
	{
		astroids[i] = 0;
		astroids[i+1] = 0;
		bullets[i] = 0;
		bullets[i+1] = 0;

	}

	//change gamestate
	gameState = PLAYING;
}

/*run the two games being played*/
void playing(void)
{
	leftGame();
	rightGame();
}

/*manages the left game*/
void leftGame(void)
{
	//move left and right
	if (keyIsDown(KEY_A))
	{
		if (offSet * 2.0f > 25.0f - windowWidth / 4.0f)
		{
			offSet--;
			offSet--;
		}
	}
	else if (keyIsDown(KEY_D))
	{
		if (offSet * 2.0f < windowWidth / 4.0f- 25.0f)
		{
			offSet++;
			offSet++;
		}
	}

	//set the current x position of the ship
	shipX = windowWidth / 4.0f + (offSet * 2.0f);

	//shooting
	if (keyPressed(KEY_SPACE) && energy > 0)
	{
		spawnBullet();
	}

	//draw all of the objects for the left game onto the screen
	drawLeftGame();

	//check for collisions
	checkCollision(LEFT);
}

/*draw the left game*/
void drawLeftGame(void)
{
  static int holder = 0;
	//set background to green
	backgroundColor(color(0, 0, 0, 255));

	fillColor(color(255, 255, 255, 255));

	//draw the ship
	triangle(shipX, windowHeight - 100.0f,  //top point
		shipX - 25.0f, windowHeight - 50.0f,  //lower left point
		shipX + 25.0f, windowHeight - 50.0f); //lower right point

	drawBullets();
	updateAstroids();

	/*spaws an astroid every 2 seconds*/
	if ((int)second() != holder)
	{
		spawnAstroid();
	}

	//display the energy left
	char buffer[256] = { 0 };
	sprintf_s(buffer, _countof(buffer), "Energy: %d", energy);
	text(buffer, (windowWidth / 2) - 100.0f, 20.0f);
  holder = (int)second();
}

/*updates and draws the bullets to the screen*/
void drawBullets(void)
{
	int i; /*looping variable*/

	for (i = 0; i <= 98; i += 2)
	{
		if (bullets[i] != 0)
		{
			//move bullet up the screen by one
			bullets[i + 1] -= 3;

			//make bullet red and draw it
			fillColor(color(255, 0, 0, 255));
			rect(bullets[i], bullets[i + 1], 2.0f, 10.0f);
			
		}
		if (bullets[i + 1] < 0)
		{
			bullets[i] = 0;
			bullets[i + 1] = 0;
		}
	}
}

/*updates and draws the bullets to the screen*/
void updateAstroids(void)
{
	int i; /*looping variable*/

	//look through the array for all valid astroids
	for (i = 0; i <= 98; i += 2)
	{
		//if the astroid exists
		if (astroids[i] != 0)
		{
			//move astroid down the screen
			astroids[i + 1] += 3;

			drawAstroids(astroids[i], astroids[i+1]);

		}
		if (astroids[i + 1] > windowHeight)
		{
			astroids[i] = 0;
			astroids[i + 1] = 0;
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

	energy--;

	//check through array for next open slot
	for (i = 0; i <= 98; i += 2)
	{
		//if slot is open assign a new bullet
		if (bullets[i] == 0)
		{
			bullets[i] = shipX;
			bullets[i+1] = windowHeight - 110.0f;
      sound(shoot);
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
		if (astroids[i] == 0)
		{
			astroids[i] = random() * ((windowWidth / 2.0f) - 30.0f);
			astroids[i + 1] = 0.0f;
			return;
		}
	}
}

/*manages the right game*/
void rightGame(void)
{
	char buffer[256] = {0};

	//gets rid of the cursor while it is in the screen
	noCursor();

	//draw background of right game
	fillColor(color(0, 255, 0, 255));
	rect(windowWidth / 2, 0.0f, windowWidth / 2, windowHeight);

	//draws a blue circle where the mouse is
	//int mPositionX = mouseX;
	//int mPositionY = mouseY;
	drawMouse();

	checkCollision(RIGHT);

	//draw the block to collect
	fillColor(color(252, 0, 0, 255));
	rect(rectX, rectY, 50.0f, 25.0f);

	//display the score
	sprintf_s(buffer, _countof(buffer), "Score: %d", score);
	text(buffer, windowWidth - 100.0f, 20.0f);
}

/*draws the circle over the mouse position for the right game*/
void drawMouse(void)
{
	//set circle to blue
	fillColor(color(0, 0, 255, 255));

	//if mouse is in the window
	if ((mouseY > 6 && windowHeight - 6 > mouseY) && (mouseX > (windowWidth / 2) + 6 && windowWidth - 6 > mouseX))
	{
		//draw the circle where the mouse is
		circle(mouseX, mouseY, 5.0f);
	}
	//if the mouse is to the right of the screen
	else if (mouseX > windowWidth - 7)
	{
		//if the mouseY cordinate is inline with the window
		if (mouseY > 6 && windowHeight - 6 > mouseY)
		{
			circle(windowWidth - 6, mouseY, 5.0f);
		}
		//if the mouseY cordinate is above the window
		else if (mouseY < 7)
		{
			circle(windowWidth - 6, 6, 5.0f);
		}
		//if the mouseY cordinate is below the window
		else
		{
			circle(windowWidth - 6, windowHeight - 6, 5.0f);
		}
	}
	//if the mouse is to the left of the right game
	else if (mouseX < (windowWidth / 2) + 7)
	{
		//if the mouseY cordinate is inline with the window
		if (mouseY > 7 && windowHeight - 7 > mouseY)
		{
			circle((windowWidth / 2) + 6, mouseY, 5.0f);
		}
		//if the mouseY cordinate is above the window
		else if (mouseY < 7)
		{
			circle((windowWidth / 2) + 6, 6, 5.0f);
		}
		//if the mouseY cordinate is below the window
		else
		{
			circle((windowWidth / 2) + 6, windowHeight - 6, 5.0f);
		}
	}
	//if the mouse is below the right game
	else if (mouseY > windowHeight + 7)
	{
		//if the mouseX cordinate is inline with the window
		if (mouseX > (windowWidth / 2) + 7 && windowWidth - 7 > mouseX)
		{
			circle(mouseX, windowHeight - 6, 5.0f);
		}
		//if the mouseX cordinate is to the left of the right game
		else if (mouseX < (windowWidth / 2) - 7)
		{
			circle((windowWidth / 2) - 6, 6, 5.0f);
		}
		//if the mouseX cordinate is to the right the window
		else
		{
			circle(windowWidth - 6, windowHeight - 6, 5.0f);
		}
	}
	//if the mouse is above the right game
	else if (mouseY < 7)
	{
		//if the mouseX cordinate is inline with the window
		if (mouseX > (windowWidth / 2) + 7 && windowWidth - 7 > mouseX)
		{
			circle(mouseX, 6, 5.0f);
		}
		//if the mouseX cordinate is to the left of the right game
		else if (mouseX < (windowWidth / 2) - 7)
		{
			circle((windowWidth / 2) - 6, 6, 5.0f);
		}
		//if the mouseX cordinate is to the right the window
		else
		{
			circle(windowWidth - 6, 6, 5.0f);
		}
	}
}

/**/
void checkCollision(int game)
{
	int i, j = 0; //looping variables
	switch (game)
	{
	case LEFT:
		//itterate through astroids array
		for(i = 0; i < 100; i += 2)
		{
			//itterate through the bullets array
			for (j = 0; j < 100; j +=2)
			{
				//when the bullet is within the column of the astroid and above the bottom side
				if (astroids[i] < bullets[j] && bullets[j] + 2.0f < astroids[i] + 30.0f && astroids[i + 1] + 30.0f > bullets[j + 1])
				{
					//remove the coresponding bullet and astoid
					astroids[i] = 0.0f;
					astroids[i+1] = 0.0f;
					bullets[j] = 0.0f;
					bullets[j+1] = 0.0f;
          sound(aExplode);
					score++;
				}
			}
		}
		//itterate through astroids array
		for (i = 0; i < 100; i += 2)
		{
			//if the ship is in the column of the current astroid and the astroid is bellow the front of the ship
			if ((astroids[i] < shipX + 25.0f && shipX - 25.0f < astroids[i] + 30.0f) && (astroids[i + 1] + 30.0f > windowHeight - 100.0f))
			{
        sound(sExplode);
				gameState = END;
			}
		}
		break;
	case RIGHT:
		//reset where the block is when one is collected and increase the score
		if ((rectX <= mouseX + 10.0f && mouseX - 10.0f <= rectX + 50.0f) && (rectY <= mouseY + 10.0f && mouseY - 10.0f <= rectY + 25.0f))
		{
			rectX = ((float)random() * (windowWidth / 2)) + (windowWidth / 2);
			if (rectX > windowWidth - 50.0f)
			{
				rectX = windowWidth - 50.0f;
			}
			rectY = (float)random() * (windowHeight - 25.0f);
			score++;
			energy++;
			sound(snare);
		}
		break;
	}
}

/**/
void end(void)
{
  char buffer[256] = { 0 };

  sprintf_s(buffer, _countof(buffer), "GAME OVER \nTotal Score: %d", score);
  text(buffer, windowWidth / 2.0f, windowHeight / 2.0f);
	
  if (mouseClicked())
	{
		gameState = MENU;
	}
}