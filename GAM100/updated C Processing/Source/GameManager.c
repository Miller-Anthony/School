//---------------------------------------------------------
// file:	GameManager.c
// author:	Anthony Miller
// brief:	Game Over scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "GameManager.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------
static int score;				// stores the overall score for the current game
static int energy;				// stores amount of energy for shooting
static float bullets[150];      // stores the coordinates of all the bullets
static float astroids[150];		// stores the coordinates of all the astroids
static FILE *fp;                // Stores the file location for the high score table
static int scores[10];          // holds the high score scores

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

int getScore()
{
	return score;
}

void incrementScore()
{
	score++;
}

void resetScore()
{
	score = 0;
}

int getEnergy()
{
	return energy;
}

void incrementEnergy()
{
	energy++;
}

void decrementEnergy()
{
	energy--;
}

void resetEnergy()
{
	energy = 0;
}

float getShotX(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return 0;
	}
	return bullets[iteration];
}

float getShotY(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return 0;
	}
	return bullets[iteration + 1];
}

void setShot(int iteration, float x, float y)
{
	if (iteration < 0 || iteration > 148)
	{
		return;
	}
	bullets[iteration] = x;
	bullets[iteration + 1] = y;
}

void moveShot(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return;
	}
	bullets[iteration + 1] -= 3;
}

float getAstroidX(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return 0;
	}
	return astroids[iteration];
}

float getAstroidY(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return 0;
	}
	return astroids[iteration + 1];
}

void setAstroid(int iteration, float x, float y)
{
	if (iteration < 0 || iteration > 148)
	{
		return;
	}
	astroids[iteration] = x;
	astroids[iteration + 1] = y;
}

void moveAstroid(int iteration)
{
	if (iteration < 0 || iteration > 148)
	{
		return;
	}
	astroids[iteration + 1] += 3;
}

void setHighScore(int newScore, int location)
{
	scores[location] = newScore;
}

int getHighScore(int location)
{
	return scores[location];
}

//---------------------------------------------------------
// Initialize the game value.
void GameManagerInit()
{
	int i = 0; //looping variable

	score = 0;
	energy = 0;
	//int err = fopen_s(&fp, "./Assets/HighScores.txt", "rt");
	//if (!err)
	//{
	//	while (!feof(fp))
	//	{	
	//		scores[i++] = atoi(fgetc(fp));
	//	}
	//	fclose(fp);
	//}
	//else
	//{
		for (i = 0; i < 10; i++)
		{
			scores[i] = 0;
		}
	//}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

