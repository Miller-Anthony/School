/**************************************************************************
filename    palindrome1.c
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
   Function: is_palindrome1

Description: check to see if the incoming char array is a palindrome.

     Inputs: phrase[] - Incoming char array.
             length   - Length of the incoming char array.

    Outputs: int -  1 for true or 0 for false.
******************************************************************************/
int is_palindrome1(const char phrase[], int length) 
{
  int i; /*looping variable*/
  
  /*only one char is a palindrome*/
  if (length == 1)
  {
    return TRUE;
  }
  
  /*loop through half the array*/
  for (i = 0; i < length / 2; i++)
  {
    /*if the char being looked at does not match the coresponding char*/
    if(phrase[i] != phrase[length - 1 - i])
    {
      break;
    }
    /*if we got through the whole string*/
    if (i == (length / 2) - 1)
    {
      return TRUE;
    }
  }
  return FALSE;
}