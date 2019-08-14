//---------------------------------------------------------
// file:	Desk.c
// author:	Anthony Miller
// brief:   Function to control going under a desk and coming back out
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneManager.h"
#include "SceneTable.h"
#include "Desk.h"
#include "PlayerManager.h"

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

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

void enterDesk(PLAYER *player, vec2_t desk);

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

/*****************************************************************************
Author: Anthony Miller

Input: player  - x and y of the player
	   desk	   - x and y of the given desk
	   stretch - total length and width of the given desk 

Output: None

Description: Check if the player is near the given desk. if they are, 
			 allow them to hide under it
*****************************************************************************/
int checkDesk(PLAYER *player, vec2_t desk, vec2_t stretch)
{
	char holder[256];  //string holder for text about hiding in desks

		//check to see if the player is next to the given desk
	if ((desk.x - (stretch.x / 2) - 50 < player->x && player->x < desk.x && desk.y - (stretch.y / 2) < player->y && player->y < desk.y + (stretch.y / 2)) ||
		(desk.x + (stretch.x / 2) + 50 > player->x && player->x > desk.x && desk.y - (stretch.y / 2) < player->y && player->y < desk.y + (stretch.y / 2)) ||
		(desk.y + (stretch.y / 2) + 50 > player->y && player->y > desk.y && desk.x - (stretch.x / 2) < player->x && player->x < desk.x + (stretch.x / 2)) ||
		(desk.y - (stretch.y / 2) - 50 < player->y && player->y < desk.y && desk.x - (stretch.x / 2) < player->x && player->x < desk.x + (stretch.x / 2)))
	{

			//display that the player can hide under the desk
		fill(0, 0, 0, 255);
		text("Press [E]", desk.x - 45, desk.y - 75);
		text("To Hide", desk.x - 45, desk.y + 75);

			//If E is pressed then hide under the desk
		if (keyPressed(KEY_E))
		{
			enterDesk(player, desk);
			return TRUE;
		}
	}
	return FALSE;
}

/*****************************************************************************
Author: Anthony Miller

Input: player - x and y of the player
Output: None

Description: Rotates the sight triangles of the NPCs
*****************************************************************************/
int stopHiding(PLAYER *player)
{
	if (keyPressed(KEY_W))
	{
			// Player has to not be hiding in the top row
		if (player->y < -200)
		{
			player->y = player->y + 150; // Enough to get out from under the desk
			player->x = player->x * -1;
			player->y = player->y * -1;

			return FALSE;
		}
	}
	if (keyPressed(KEY_S))
	{
			// Player cant be hiding in the bottom row
		if (player->y > -900)
		{
			player->y = player->y - 150; // Enough to get out from under the desk

				// Switch position back to positive (in the level)
			player->x = player->x * -1;
			player->y = player->y * -1;

			return FALSE;
		}
	}
	if (keyPressed(KEY_A))
	{
			// Only works on the players desk
		if (player->x > -250 && player->y > -400)
		{
			player->x = player->x + 150; // Enough to get out from under the desk

			// Switch position back to the level
			player->x = player->x * -1;
			player->y = player->y * -1;

			return FALSE;
		}
	}
	if (keyPressed(KEY_D))
	{
			// Has to be a desk at the front of the class
		if (player->x < -1000)
		{
			player->x = player->x - 150; // Enough to get out from under the desk

			// Switch position back to the level
			player->x = player->x * -1;
			player->y = player->y * -1;
			
			return FALSE;
		}
	}
	return TRUE;
}

/*****************************************************************************
Author: Anthony Miller

Input: desk - x and y of the given desk

Output: None

Description: Draws a bouncing and rotating triangle over the given desk
*****************************************************************************/
void showDesk(vec2_t desk)
{
		// Draw triangle at the location of the given desk
	fill(255, 0 , 0, 255);
	triangle(desk.x, desk.y - (10.0f * sin(second() * 2)),
			desk.x - (20.0f * sin(second() * 3)), desk.y - 40.0f - (10.0f * sin(second() * 2)),
			desk.x + (20.0f * sin(second() * 3)), desk.y - 40.0f - (10.0f * sin(second() * 2)));
}

/*****************************************************************************
Author: Anthony Miller

Input: player - x and y of the player
	   desk   - x and y of the given desk

Output: None

Description: Moves the player to the negative of where the desk is
*****************************************************************************/
void enterDesk(PLAYER *player, vec2_t desk)
{
		// Players x and y are set to the negative of the given desk
	player->x = -1 * desk.x;
	player->y = -1 * desk.y;
}