/**************************************************************************
filename    sieve.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Lab Week #7
due date    10/24/2018

Brief Description:
  functions the change an array to true of false or preform math bassed on 
  if the index is prime or not.
**************************************************************************/
#include <stdio.h> /* printf      */
#include <math.h>  /* sqrt        */
#include "sieve.h" /* TRUE, FALSE */

/******************************************************************************
   Function: seive

Description: go through an array setting its elements to one or zero depending 
             on if the current index number is a prime or not.

     Inputs: array[] - array that will have each element set to one or zero.
             size    - size of the incoming array.

    Outputs: N/A 
******************************************************************************/
void sieve(int array[], int size)
{
  int i, j; /*looping variables*/
  
  array[0] = array[1] = FALSE; /*0 and 1 are not prime numbers*/
  
  /*set all array elements above 1 to true*/
  for (i = 2; i < size; i++)
  {
    array[i] = TRUE;
  }
  
  /*itterate through the array looking for prime numbers*/
  for (i = 2; i < sqrt(size); i++)
  {
    /*if the current element of the array is set to tue*/
    if (array[i])
    {
      /*go through the array setting multiples of the current element to false*/
      for (j = i * 2; j < size; j += i)
      {
        array[j] = FALSE;
      }
    }
  }
}

/******************************************************************************
   Function: twin_primes

Description: look through prime numbers and return a count of how many 
             twin primes there are in the list.

     Inputs: primes[] - Array where the elements tell if the index number
                        is prime or not.
             size     - Size of the passed in array.

    Outputs: int - the number of twin primes found
******************************************************************************/
int twin_primes(const int primes[], int size)
{
  int i;         /*looping variable*/
  int count = 0; /*the number of twin primes found*/
  
  /*itterate through the array*/
  for (i = 0; i < size; i++)
  {
    /*if the current element and next possible prime are true*/
    if (primes[i] == TRUE && primes[i + 2] == TRUE)
    {
      /*increase count and print what twin primes were found*/
      count++;
      printf("twin prime #%4i: %4i and %4i\n", count, i, i + 2);
    }
  }
  
  /*return the number of twin primes found*/
  return count;
}

/******************************************************************************
   Function: brun_constant

Description: Add the recipricals of each twin prime togeather in the array and
             return the sum.

     Inputs: primes[] - Array where the elements tell if the index number
                        is prime or not.
             size     - Size of the passed in array.

    Outputs: double -  Brun's Constant
******************************************************************************/
double brun_constant(const int primes[], int size)
{
  int i;               /*looping variable*/
  double holder = 0.0; /*holds baun's constant*/
  
  /*itterate through the array*/
  for (i = 0; i < size; i++)
  {
    /*if the current element and next possible prime are true*/
    if (primes[i] == TRUE && primes[i + 2] == TRUE)
    {
      /*add the reciprical of the */
      holder += 1.0 / i + 1.0 / (i + 2.0);
    }
  }
  return holder;
}