/**************************************************************************
filename    primes1.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Lab Week #6
due date    10/17/2018

Brief Description:
  Contains functions that output based on cubed data
**************************************************************************/
#include <stdio.h> /*printf*/

#define FALSE 0
#define TRUE  1

/******************************************************************************
   Function: is_prime

Description: Evaluate and return if the passed in number is prime.

     Inputs: number - Any number to see if it is prime or not.

     Outputs: 1 for true or 0 for false.
******************************************************************************/
int is_prime(int number)
{
  int i; /*looping variable*/
  
  /*because 2 is the only even prime, return true if that was passed in*/
  if (number == 2)
  {
    return TRUE;
  }
  /*if the number was less than 2 or even it cant be prime*/
  else if (number < 2 || number % 2 == 0)
  {
    return FALSE;
  }
  /*if the number was not caught by above logic should check for prime*/
  else
  {
    /*loop through all odd numbers until half of the passed in number*/
    for (i = 3; i <= number / 2; i += 2)
    {
      /*if the number can be evenly devided, it is not a prime*/
     if (number % i == 0)
     {
        return FALSE;
     }   
    }
    return TRUE;
  }
}

/******************************************************************************
   Function: conjecture

Description: Print to screen a sum for all even numbers between the values
             passed in that consists of two primes.

     Inputs: low - Lowest number that a sum will be calculated for.
             high - Highest number that a sum will be calculated for.

    Outputs: N/A 
******************************************************************************/
void conjecture(int low, int high)
{
  int i, j; /*loop variables*/
  
  /*itterate through even sums from low to high*/
  for (; low <= high; low += 2)
  {
    int found = FALSE; /*holds if the current number has had a sum found*/
    
    /*loop through first number of the sum*/
    for (i = 2; i < high; i++)
    {
      /*when the first number is prime and a sum has not been found*/
      if (is_prime(i) && !found)
      {
        /*loop through second number of the sum*/
        for (j = i; j < high; j++)
        {
          /*when the two numbers equal the sum and are prime*/
          if (low == i + j && is_prime(j))
          {
            printf("%3i = %3i + %3i\n", low, i, j);
            found = TRUE;
            break;
          }
        }
      }
    }
      found = FALSE; /*when done looking for current sum, reset if found*/
  }
}