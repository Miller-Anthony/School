/**************************************************************************
filename    pi.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Assignment #1
due date    10/09/2018

Brief Description:
  Includes functions that calculate the value of pi using the circle method
  and the Leibniz method.
**************************************************************************/
#include "math.h" /*sqrt*/

/******************************************************************************
   Function: circle_pi

Description: calculates pi using the Circle method.

    Inputs: int - the number of rectangles used to get an estimation of pi.

    Outputs: A double representation as close to pi as possible.
******************************************************************************/
double circle_pi(int rectangles)
{
  int i;                /*looping variable                          */
  double pi = 0.0;      /*holder for the aproximation of pi         */
  double radius = 2.0;  /*radius of the circle                      */
  double midPoint;      /*midpoint of the current rectangle         */
  double area;          /*stores the area of the current rectangle  */
  double base;          /*stores the base of all rectangles         */
  double height;        /*stores the height of the current rectangle*/

  base = (radius / (double)rectangles); /*calculate the base of all rectangles*/

  midPoint = base / 2.0; /*calculate the midpoint of the first rectangle*/

  /*loop through making rectangles and adding them*/
  for(i = 0; i < rectangles; i++)
  {
    /*calculate the height of the current rectangle*/
    height = sqrt((radius * radius) - (midPoint * midPoint));
    
    area = base * height; /*calculate the area of the current triangle*/
    pi += area;/*increase pi by the current rectangle*/
    midPoint += base; /*set midpoint of next rectangle*/
  }
  return pi; /*send the closes posible number to pi*/
}

/******************************************************************************
   Function: leibniz_pi

Description: calculates pi using the Leibniz method.

    Inputs: int - the number of iterations or how acurate pi will be.

    Outputs: A double representation as close to pi as possible.
******************************************************************************/
double leibniz_pi(int iterations)
{
  double i = 0;     /*looping variable                     */
  double pi = 0;    /*holder for the aproximation of pi / 4*/


  /*loop until all itterations have been gone through*/
  while(i < iterations)
  {
    /*on odd iterations subtract*/
    if((int)i % 2)
    {
      /*calculate the next fraction needed based off the current itteration*/
      pi -= 1.0 / ((i * 2.0) + 1.0);
    }
    /*on zero and even iterations add*/
    else
    {
      /*calculate the next fraction needed based off the current itteration*/
      pi += 1.0 / ((i * 2.0) + 1.0);
    }
    i++; /*increment the itteration*/
  }
  return pi * 4.0; /*multiply by 4 to send back a number close to pi*/
}