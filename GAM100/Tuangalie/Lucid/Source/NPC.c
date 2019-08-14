//---------------------------------------------------------
// file:	NPC.c
// author:	Maverick Alexander and Anthony Miller
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneManager.h"
#include "SceneTable.h"
#include "NPC.h"
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

void devideRow(float matrix[], float value);
void subtractRow(float row1[4], float row2[4], float multiplyer);

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

/*****************************************************************************
Author: Maverick Alexander
Name:   npc_updown_movement

Input: x,y - x,y coordinates
		 r - radius
	offset - change the y position by
	max    - furthest the circle will travel down
	min    - furthest the circle will travel up

Output: circle moving up and down

Description: moves a circle up and back down
*****************************************************************************/
void npc_updown_movement(int* y, int offset, int max, int min, bool *hitmax)
{

	if (*y >= max)
	{
		*hitmax = true;
	}
	else if (*y <= min)
	{
		*hitmax = false;
	}

	if (*hitmax == false)
	{
		*y += offset;
	}
	else
	{
		*y -= offset;
	}
}

/*****************************************************************************
Author: Maverick Alexander
Name:   npc_updown_movement

Input: x,y - x,y coordinates
		 r - radius
	offset - change the y position by
	max    - furthest the circle will travel down
	min    - furthest the circle will travel up

Output: circle moving left and right

Description: moves a circle left and right
*****************************************************************************/
void npc_leftright_movement(int *x, int offset, int max, int min, bool *hitmax)
{

	if (*x >= max)
	{
		*hitmax = true;
	}
	else if (*x <= min)
	{
		*hitmax = false;
	}

	if (*hitmax == false)
	{
		*x += offset;
	}
	else
	{
		*x -= offset;
	}

}

/*****************************************************************************
Author: Anthony Miller

Input: p1 - x and y of the first triangle point
	   p2 - x and y of the second triangle point
	   p3 - x and y of the third triangle point
	   rotation - degrees to rotate triangle by

Output: None

Description: Rotates the sight triangles of the NPCs
*****************************************************************************/
void rotateTriangle(vec2_t *p1, vec2_t *p2, vec2_t *p3, float rotation)
{
	//rotation transformation matrix
	float matrix[2][2] = { 0 };

	matrix[0][0] = cos((double)rotation * (PI / 180));
	matrix[0][1] = -sin((double)rotation * (PI / 180));
	matrix[1][0] = sin((double)rotation * (PI / 180));
	matrix[1][1] = cos((double)rotation * (PI / 180));

	//set points 2 and 3 relitive to the origin
	float holder2x = p2->x - p1->x;
	float holder3x = p3->x - p1->x;
	float holder2y = p2->y - p1->y;
	float holder3y = p3->y - p1->y;

	//pass the points through the rotation matrix
	p2->x = (holder2x * matrix[0][0]) + (holder2y * matrix[0][1]);
	p2->y = (holder2x * matrix[1][0]) + (holder2y * matrix[1][1]);

	p3->x = (holder3x * matrix[0][0]) + (holder3y * matrix[0][1]);
	p3->y = (holder3x * matrix[1][0]) + (holder3y * matrix[1][1]);

	//set rotated points back in relation the npc location
	p2->x = p2->x + p1->x;
	p3->x = p3->x + p1->x;
	p2->y = p2->y + p1->y;
	p3->y = p3->y + p1->y;
}

/*****************************************************************************
Author: Anthony Miller

Input: point1 - x and y of the first triangle point
	   point3 - x and y of the second triangle point
	   point2 - x and y of the third triangle point
	   player - x and y position of the player

Output: if the player is found to be in the triangle it will return TRUE (1).
		if the player is found to not be in the triangle it will return FALSE (0).

Description: Checks if the player is within a detection triangle using barycentric coordinates
*****************************************************************************/
int checkDetection(vec2_t p1, vec2_t p2, vec2_t p3, PLAYER player)
{
	int i, j; // looping variables

		//fill the matrix with the passed in values
	float matrix[3][4] = { {1.0f, 1.0f, 1.0f, 1.0f},
							{p1.x, p2.x, p3.x, player.x},
							{p1.y, p2.y, p3.y, player.y} };

	//itterate through the columns
	for (i = 0; i < 3; i++)
	{
		//itterate through the rows of the current column
		for (j = i; j < 3; j++)
		{
			//if the current value is not 1 or 0
			if (!(matrix[j][i] == 1 || matrix[j][i] == 0))
			{
				devideRow(matrix[j], matrix[j][i]);
			}
		}
		//itterate through the rows of the current column again
		for (j = i + 1; j < 3; j++)
		{
			//if the front of the current row is 1
			if (matrix[j][i] == 1)
			{
				subtractRow(matrix[i], matrix[j], 1);
			}
		}
	}

	//itterate back through the matrix from the bottom to the top
	for (i = 2; i >= 0; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (matrix[j][i] != 0)
			{
				subtractRow(matrix[i], matrix[j], matrix[j][i]);
			}
		}
	}

	//if all of the weights are between 0 and 1 then the player is in the triangle
	if ((0 <= matrix[0][3] && matrix[0][3] <= 1) &&
		(0 <= matrix[1][3] && matrix[1][3] <= 1) &&
		(0 <= matrix[2][3] && matrix[2][3] <= 1))
	{
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------


/*****************************************************************************
Author: Anthony Miller

Input: matrix - One row of a matrix
	   value  - The value to multiply with

Output: None

Description: multiply a row of a matrix by a given value
*****************************************************************************/
void devideRow(float matrix[], float value)
{
	int i; // looping variable

		//itterate through the row
	for (i = 0; i < 4; i++)
	{
		//divide the current number by the value
		matrix[i] /= value;
	}
}

/*****************************************************************************
Author: Anthony Miller

Input: matrix - a matrix to have math done to it
	   row1	  - The row of the matrix to subtract with
	   row2   - The row of the matrix to subtract from

Output: None

Description: subtract a row of a matrix from another
*****************************************************************************/
void subtractRow(float row1[4], float row2[4], float multiplyer)
{
	int i; //looping variable
	int positive = TRUE;

	// itterate backwards through the row to be subtracted from
	for (i = 3; i >= 0; i--)
	{
		//if the given number is a negative, then positive becomes FALSE
		if (row2[i] < 0 && row1[i] != 0)
		{
			positive = FALSE;
		}
		//if the given number is positive, then positive becomes TRUE
		else if (row2[i] > 0 && row1[i] != 0)
		{
			positive = TRUE;
		}
	}

	if (positive)
	{
		//itterate throught the array subtracting row 1 from row 2
		for (i = 0; i < 4; i++)
		{
			row2[i] -= (row1[i] * abs(multiplyer));
		}
	}
	else if (!positive)
	{
		//itterate throught the array adding row 1 from row 2
		for (i = 0; i < 4; i++)
		{
			row2[i] += (row1[i] * abs(multiplyer));
		}
	}
}

