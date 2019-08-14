/**************************************************************************
filename    histogram.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Lab Week #9
due date    11/07/2018

Brief Description:
  Functions for counting chars in a string, printing out a count of the letter
  characters and returning the average weight and highest occurance letter.
**************************************************************************/

#include <stdio.h>     /* printf      */
#include <ctype.h>     /* toupper     */
#include "histogram.h" /* lab defines */

/******************************************************************************
   Function: GetCounts

Description: Calculate how many letters (indavidual and total), spaces and
             other char's are in the incoming sentance.

     Inputs: sentence - A string to check amount and type of chars it contains.
             letters  - A count of letters coresponding to elements (0 = A).
             spaces   - Will hold the number of spaces in the sentance.
             other    - Will hold the number of other chars in the sentence.

    Outputs: The number of letters characters in the passed in sentence.
******************************************************************************/
int GetCounts(const char *sentence, int letters[], int *spaces, int *other)
{
  int i;         /*looping variabe                            */
  int count = 0; /*The total number of letters in the sentance*/
  
  /*initialize the letters array to all zeroes*/
  for(i = 0; i < NUM_LETTERS; i++)
  {
    letters[i] = 0;
  }
  
  /*initiate spaces and others to 0*/
  *spaces = 0;
  *other = 0;
  
  /*itterate through the passed in string*/
  do
  {
    char holder = toupper(*sentence); /*hold the current char of the string*/
    
    /*if the current char is a letter*/
    if ('A' <= holder && holder <= 'Z')
    {
      /*increment the coresponding array element and the count of letters*/
      letters[holder - 'A']++;
      count++;
    }
    /*if the current char is a space*/
    else if(*sentence == ' ')
    {
      *spaces += 1;
    }
    /*if the current char is anything else*/
    else
    {
      *other += 1;
    }
  }   while(*(++sentence));
  return count;
}

/******************************************************************************
   Function: PrintHistogram

Description: Print to screen an * for each count of a given letter in the
             passed in array.

     Inputs: letters - a count of letters coresponding to elements (0 = A).

    Outputs: None.
******************************************************************************/
void PrintHistogram(const int letters[])
{
  int i, j; /*looping variables*/
  
  /*itterate through the array of letter counts*/
  for (i = 0; i < NUM_LETTERS; i++)
  {
    printf("%c:", 'A' + i); /*print out the letter you are currently counting*/
    
    /*print a '*' for each count for the given letter*/
    for (j = 0; j < letters[i]; j++)
    {
      printf("*");
    }
    printf("\n"); /*print a new line after finishing the asterisks*/
  }
}

/******************************************************************************
   Function: GetStatistics

Description: Determine the average weight of the letters and what letter 
             appears more ofthen than the rest.

     Inputs: letters    - A count of letters coresponding to elements (0 = A).
             average    - The average weight of the letters counted.
             max_letter - The letter with the greatest count.
             max_count  - Count of the letter that appears the most.

    Outputs: None.
******************************************************************************/
void GetStatistics(const int letters[], double *average,
                   char *max_letter, int *max_count)
{
  int i;             /*looping variable                                    */
  double holder = 0; /*hold the total to be devided by number of letters   */
  *max_letter = 'A'; /*set initial value so it will always return something*/
  *max_count = 0;    /*set initial value so it will always return something*/
  
  /*itterate through the letters array*/
  for(i = 0; i < NUM_LETTERS; i++)
  {
    /*increase the holder based on the weight and count of the current char*/
    holder += (i + 1) * letters[i];
    
    /*if the count of the current letter is more than the largest count so far*/
    if (*max_count < letters[i])
    {
      /*store the current letter and its count to be returned*/
      *max_letter = 'A' + i;
      *max_count = letters[i];
    }
  }
  
  *average = holder / NUM_LETTERS; /*calculate the average to be returned*/
}