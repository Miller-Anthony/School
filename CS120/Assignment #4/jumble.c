/**************************************************************************
filename    jumble.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Assignment #4
due date    11/01/2018

Brief Description:
  return string length and encode or decode strings.
**************************************************************************/

#include "jumble.h"
#include <stdio.h>

/******************************************************************************
   Function: mystrlen

Description: get the legth of a given string.

     Inputs: string -  any string you want the length of.

    Outputs: int -  length of the passed in string.
******************************************************************************/
int mystrlen(const unsigned char *string)
{
  int i = 0; /*looping variable*/
  
  while(*string)
  {
    string++;
    i++;
  }
  return i;
}

/******************************************************************************
   Function: mystrlen

Description: Encode or decode a given string using the given password.

     Inputs: string   -  The string to encode or decode.
             password -  The string to encode or decode the other string.
             method   -  Whether you are encoding or decodeing.
             passes   -  The number of times you will encode or decode.

    Outputs: None
******************************************************************************/
void jumble(unsigned char *string, const unsigned char *password, 
            enum CODE_METHOD method, int passes)
{
  int i, j, k; /*looping variables*/
  
  /*do a full encoding or decoding with each pass*/
  for(i = 0; i < passes; i++)
  {
    /*itterate through the passed in string*/
    for (j = 0; j < mystrlen(string); j++)
    {
      /*itterate through both password and string for the length of password*/
      for(k = 0; k < mystrlen(password) && j < mystrlen(string); k++, j++)
      {
        /*if method is set to encode*/
        if (!method)
        {
          /*string address offset by j modified by password adress offset by k*/
          *(string + j) += *(password + k);
        }
        /*if method is set to decode*/
        else
        {
          /*string address offset by j modified by password adress offset by k*/
          *(string + j) -= *(password + k);
        }
      }
    }
  }
}