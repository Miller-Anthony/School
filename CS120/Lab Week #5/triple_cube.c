/**************************************************************************
filename    triple_cube.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Lab Week #5
due date    10/10/2018

Brief Description:
  Contains functions that output based on cubed data
**************************************************************************/
#include "stdio.h" /*printf*/

/******************************************************************************
   Function: print_cubes

Description: itterates through all 3 digit numbers, then prints to screen if
             the cubed sum is equivalent to the initial number.

     Inputs: N/A

    Outputs: N/A 
******************************************************************************/
void print_cubes(void)
{
  int i = 100;   /*looping variable         */
  int hundreds;  /*stores the hundreds digit*/
  int tens;      /*stroes the tens digit    */
  int ones;      /*stores the ones digit    */
  int sum;       /*stores the cubed sum     */
  
  /*loop through all three digit numbers*/
  while (i < 1000)
  {
    /*seperate the three digits*/
    ones = i % 10;
    tens = (i / 10) % 10;
    hundreds = i / 100;
    
    /*cube the three digits*/
    ones = ones * ones * ones;
    tens = tens * tens * tens;
    hundreds = hundreds * hundreds * hundreds;
    
    sum = ones + tens + hundreds; /*add the cubed numbers togeather*/
    
    /*output if the cubed sum is the same as the initial number*/
    if(i == sum)
    {
      printf("%d has the cube property. (%d + %d + %d)\n",
              i, hundreds, tens, ones);
    }
    
    i++; /*increment the itteration*/
  }
}

/******************************************************************************
   Function: print_pythagorean_triples

Description: check for pythagorean theorem values up between the low and high
             values passed in.

     Inputs: int - the number of iterations or how acurate pi will be.

    Outputs: N/A 
******************************************************************************/
void print_pythagorean_triples(int low, int high)
{
  int i, j, k;    /*looping variables                      */
  int count = 1;  /*counts how many triples have been found*/

  /*cycle through numbers to check if they follow the pythagorean theorem*/
  for (i = low; i < high; i++)
    for (j = i + 1; j < high; j++)
      for (k = j + 1; k < high; k++)
        /*check to see if current itteration follows pythagorean theorem*/
        if (i * i + j * j== k * k)
        {
           printf("Triple #%3i: %3i,%3i,%3i --> %4i + %4i = %4i\n",
                   count, i, j, k, i * i, j * j, k * k);
           count++; /**/
        }
}