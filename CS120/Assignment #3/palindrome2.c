/**************************************************************************
filename    palindrome2.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Assignment #3
due date    10/25/2018

Brief Description:
  functions the change an array to true of false or preform math bassed on 
  if the index is prime or not.
**************************************************************************/
#define TRUE 1
#define FALSE 0

/******************************************************************************
   Function: is_palindrome2

Description: check to see if the incoming char array is a palindrome.

     Inputs: *phrase   - Pointer to char array.
             length    - Length of the incoming char array.

    Outputs: int -  1 for true 0 for false.
******************************************************************************/
int is_palindrome2(const char *phrase, int length) 
{
  int i;                                     /*looping variable*/
  const char *pHolder = phrase + length - 1; /*pointer to end of the phrase*/
  
  /*only one char is a palindrome*/
  if (length == 1)
  {
    return TRUE;
  }
  
  /*loop through half the array*/
  for (i = 0; i < length / 2; i++)
  {
    /*if the char being looked at does not match the coresponding char*/
    if(*phrase != *pHolder)
    {
      break;
    }
    
    /*increment to the next char to compare*/
    phrase++;
    pHolder--;
    
    /*if we got through the whole string*/
    if (i == (length / 2) - 1)
    {
      return TRUE;
    }
  }
  return FALSE;
}