//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix2D.h"

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void devideRow(float matrix[], float value);
void subtractRow(float row1[3], float row2[3], float multiplyer);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// This function sets the matrix equal to the identity matrix.
void Matrix2DIdentity(Matrix2D *pResult)
{
	//for each row
	for (int i = 0; i < 3; i++)
	{
		//for each column
		for (int j = 0; j < 3; j++)
		{
			//set a diagnal line of 1's
			if (i == j)
			{
				pResult->m[i][j] = 1;
			}
			else
			{
				pResult->m[i][j] = 0;
			}
		}
	}
}

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
// (NOTE: Care must be taken when pResult = pMtx.)
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	int i, j; // looping variables

	//make sure pResult is the identity matrix
	Matrix2DIdentity(pResult);

	if (pMtx->m[0][2] == 0 && pMtx->m[1][2] == 0)
	{
		// holds the value to devide by for finding transpose
		float holder = (pMtx->m[0][0] * pMtx->m[1][1]) - (pMtx->m[0][1] * pMtx->m[1][0]);

		//do the math so set the transpose
		pResult->m[0][0] = pMtx->m[1][1] / holder;
		pResult->m[0][1] = -pMtx->m[0][1] / holder;
		pResult->m[1][0] = -pMtx->m[1][0] / holder;
		pResult->m[1][1] = pMtx->m[0][0] / holder;
	}
	else
	{
		//a matrix to do math on
		float matrix[3][3] = { 0 };

		//itterate through the columns
		for (i = 0; i < 3; i++)
		{
			//itterate through the rows of the current column
			for (j = i; j < 3; j++)
			{
				//fill the matrix with the passed in values
				matrix[j][i] = pMtx->m[j][i];
			}
		}


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
					devideRow(pResult->m[j], matrix[j][i]);
				}
			}
			//itterate through the rows of the current column again
			for (j = i + 1; j < 3; j++)
			{
				//if the front of the current row is 1
				if (matrix[j][i] == 1)
				{
					subtractRow(matrix[i], matrix[j], 1);
					subtractRow(pResult->m[i], pResult->m[j], 1);
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
					subtractRow(pResult->m[i], pResult->m[j], pResult->m[j][i]);
				}
			}
		}
	}
}

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
// Result = Mtx0*Mtx1
// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D holder;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			holder.m[j][i] = (pMtx0->m[j][0] * pMtx1->m[0][i]) + (pMtx0->m[j][1] * pMtx1->m[1][i]) + (pMtx0->m[j][2] * pMtx1->m[2][i]);
		}
	}

	*pResult = holder;
}

// This function creates a translation matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	//make sure pResult is the identity matrix
	Matrix2DIdentity(pResult);

	//set the translation values
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// This function creates a scaling matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j && i == 0)
			{
				pResult->m[i][j] = x;
			}
			else if (i == j && i == 1)
			{
				pResult->m[i][j] = y;
			}
			else if (i == j && i == 2)
			{
				pResult->m[i][j] = 1;
			}
			else
			{
				pResult->m[i][j] = 0;
			}
		}
	}
}

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
// (Hint: This function must initialize all matrix values.)
// Save the resultant matrix in Result.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Matrix2DRotDeg(Matrix2D *pResult, float angle)
{
	Matrix2DRotRad(pResult, (angle * (float)M_PI) / 180);
}

// This matrix creates a rotation matrix from "Angle" whose value is in radians.
// (Hint: This function must initialize all matrix values.)
// Save the resultant matrix in Result.
void Matrix2DRotRad(Matrix2D *pResult, float angle)
{
	//make sure pResult is the identity matrix
	Matrix2DIdentity(pResult);

	//set the rotation values
	pResult->m[0][0] = cosf(angle);
	pResult->m[0][1] = -sinf(angle);
	pResult->m[1][0] = sinf(angle);
	pResult->m[1][1] = cosf(angle);
}

// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
// Result = Mtx * Vec.
// (NOTE: Care must be taken when pResult = pVec.)
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	//for special case for pResult = pVec so that you dont change the values in the second rows computations
	Vector2D holder;
	holder.x = pVec->x;
	holder.y = pVec->y;

	//add in 3rd dimention multiplication
	pResult->x = (pMtx->m[0][0] * holder.x) + (pMtx->m[0][1] * holder.y) + pMtx->m[0][2];
	pResult->y = (pMtx->m[1][0] * holder.x) + (pMtx->m[1][1] * holder.y) + pMtx->m[1][2];
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

/*****************************************************************************
Author: Anthony Miller

Input: matrix - One row of a matrix
	   value  - The value to multiply with

Output: None

Description: devide a row of a matrix by a given value
*****************************************************************************/
void devideRow(float matrix[], float value)
{
	int i; // looping variable

		//itterate through the row
	for (i = 0; i < 3; i++)
	{
		//divide the current number by the value
		matrix[i] /= value;
	}
}

/*****************************************************************************
Author: Anthony Miller

Input: row1	  - The row of the matrix to subtract with
	   row2   - The row of the matrix to subtract from


Output: None

Description: subtract a row of a matrix from another row
*****************************************************************************/
void subtractRow(float row1[3], float row2[3], float value)
{
	int i; //looping variable
	int positive = true;

	// itterate backwards through the row to be subtracted from
	for (i = 2; i >= 0; i--)
	{
		//if the given number is a negative, then positive becomes FALSE
		if (row2[i] < 0 && row1[i] != 0)
		{
			positive = false;
		}
		//if the given number is positive, then positive becomes TRUE
		else if (row2[i] > 0 && row1[i] != 0)
		{
			positive = true;
		}
	}

	if (positive)
	{
		//itterate throught the array subtracting row 1 from row 2
		for (i = 0; i < 3; i++)
		{
			row2[i] -= (row1[i] * fabsf(value));
		}
	}
	else if (!positive)
	{
		//itterate throught the array adding row 1 from row 2
		for (i = 0; i < 3; i++)
		{
			row2[i] += (row1[i] * fabsf(value));
		}
	}
}