/**************************************************************************
filename    numbers.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     D
assignment  3
due date    9/26/2018
Brief Description:
 This program asks for 3 numbers between 0 and 9.999, then outputs their
 sin, cos, tan and arctan for the user to see
**************************************************************************/
#include <stdio.h> /*printf, scanf*/
#include <math.h>  /*sin, cos, tan, atan*/

int main(void)
{
  float num1 = 0;  /*First number from input*/
  float num2 = 0;  /*Second number from input*/
  float num3 = 0;  /*Third number from input*/
  
  /*promt user for, then recieve 3 numbers to be converted trigonometrically*/
  printf("Enter 3 numbers between 0 and 9.999: \n");
  scanf("%f %f %f", &num1, &num2, &num3);
  
  /*print the header for the output*/
  printf("Number      sin      cos      tan      atan\n");
  printf("-------------------------------------------\n");
  
  /*outputs sin, cos, tan and arctan for the first input*/
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n",
         num1, sin(num1), cos(num1), tan(num1), atan(num1));
  
  /*outputs sin, cos, tan and arctan for the second input*/
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n",
         num2, sin(num2), cos(num2), tan(num2), atan(num2));
  
  /*outputs sin, cos, tan and arctan for the third input*/
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n",
         num3, sin(num3), cos(num3), tan(num3), atan(num3));
  
  return 0;
}