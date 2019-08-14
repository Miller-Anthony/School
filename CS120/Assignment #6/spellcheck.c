/**************************************************************************
filename    spellcheck.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Assignment #6
due date    11/29/2018

Brief Description:
  Spell checking and dictionary information functions.
**************************************************************************/
#include <string.h> /* strlen strcpy     */
#include <stdio.h>  /* FILE fopen fclose feof */

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h"

#define CASE_DIFFERENCE 32 /* difference between ASCII upper and lower case */

/******************************************************************************
   Function: mystrupr

Description: Change all lower case letters in the given string to upper case.

     Inputs: string - Pointer to the start of a string.

    Outputs: Pointer to the start of the modified string.
******************************************************************************/
char *mystrupr(char *string)
{
  char *holder = string; /* pointer to first character of passed in string */
  
    /* while string is not null */
  while(*string)
  {
      /* if the currant character is lower case */
    if('a' <= *string || *string >= 'z' )
    {
        /* change lower case letter to upper case */
      *string -= CASE_DIFFERENCE;
    }
      /* itterate to next char of string */
    string++;
  }
  
  return holder;

}

/******************************************************************************
   Function: info

Description: Look through given dictionary and store information about it.

     Inputs: dictionary - File containing the list of words to look through.
             dinfo      - Struct to store info about the given dictionary.

    Outputs: If the file did not open -2. If the file opened with no errors -1.
******************************************************************************/
int info(const char *dictionary, struct DICTIONARY_INFO *dinfo)
{
  FILE *pFile;                 /* Pointer to a file                           */
  char holder[LONGEST_WORD];  /* Character array to hold incoming file lines */
  
    /* Initialise the data of the information struct */
    dinfo->shortest = LONGEST_WORD;
    dinfo->longest = 0;
    dinfo->count = 0;
  
  pFile = fopen(dictionary, "r"); /* Open the given file */
  
    /* If the file did not open, return an error */
  if (pFile == NULL)
  {
    return FILE_ERR_OPEN;  /* -2 */
  }
  
    /* While it is not the end of the file */
  while(!feof(pFile))
  {
      /* If a new line was gotten */
    if(fgets(holder, LONGEST_WORD, pFile))
    {
      int length = strlen(holder) - 1; /* Length of the new line */
      
        /* If length of the current line is more than the current longest */
      if (length > dinfo->longest)
      {
        dinfo->longest = length;  /* Set longest length to new longest */
      }
        /* If length of the current line is less than the current shortest */
      if(length < dinfo->shortest)
      {
        dinfo->shortest = length; /* Set shortest length to new shortest */
      }
      dinfo->count = dinfo->count + 1; /* itterate the word count */
    }
  }

    /* Cose the given file */
  fclose(pFile);

  return FILE_OK;  /* -1 */


}

/******************************************************************************
   Function: spell_check

Description: Search for the given word in the given dictionary to see if the
             word is spelled correctly.

     Inputs: dictionary  - File containing the list of words to look through.
             word        - The word to look for in the given dictionary.

    Outputs: If the word is found 1. If the word is not found 2. if the file
             does not open -2.
******************************************************************************/
int spell_check(const char *dictionary, const char *word)
{
  FILE *pFile;                    /* Pointer to a file                  */
  char holder[LONGEST_WORD];      /* Array to hold incoming file lines  */
  char copy[LONGEST_WORD] = {0};  /* Holds a copy of the passed in word */
  
  
  pFile = fopen(dictionary, "r"); /* Open the given file */
  
    /* If the file did not open */
  if (pFile == NULL)
  {
    return FILE_ERR_OPEN;  /* -2 */
  }
  
  strcpy(copy, word);  /* Copy the passed in word           */
  mystrupr(copy);      /* Set the copied word to upper case */
  
    /* While it is not the end of the file */
  while(!feof(pFile))
  {
      /* If a new line was gotten */
    if(fgets(holder, LONGEST_WORD, pFile))
    {
      mystrupr(holder);                /* Set current word to upper case */
      holder[strlen(holder) - 1] = 0;  /* Replace '\n' with '\0' */
      
        /* If the passed in word is found in the dictionary */
      if(!strcmp(holder, copy))
      {
          /* Cose the given file */
        fclose(pFile);
        return WORD_OK;  /* 1 */
      }
    }
  }

    /* Cose the given file */
  fclose(pFile);
  
  return WORD_BAD;  /* 2 */

}

/******************************************************************************
   Function: word_lengths

Description: Calculate how many words are in the dictionary with length equal
             to or less than the passed in maximum.

     Inputs: dictionary - File containing the list of words to look through.
             lengths    - Array where the index holds the number of words of 
                          the coresponding length.
             count      - Max length of words to look for.

    Outputs: If the file did not open -2. If the file opened with no errors -1.
******************************************************************************/
int word_lengths(const char *dictionary, int lengths[], int count)
{
  FILE *pFile;                /* Pointer to a file                           */
  char holder[LONGEST_WORD];  /* Character array to hold incoming file lines */
  char last[LONGEST_WORD];    /* Array to check if it is the end of file     */
  
  
  pFile = fopen(dictionary, "r");  /* Open the passed in file */
  
    /* If the file did not open return an error message */
  if (pFile == NULL)
  {
    return FILE_ERR_OPEN;  /* -2 */
  }
  
    /* While it is not the end of the file */
  while(!feof(pFile))
  {
    int length;  /* How long a given line is */
    
    strcpy(last, holder);  /* copy the lest word */
    
      /* If a new line was gotten and new word is not the same as last word*/
    if(fgets(holder, LONGEST_WORD, pFile) && strcmp(last, holder))
    {
      length = strlen(holder) - 1; /* Get the length of the new line */
      
        /* If the length of the current line is less than the maximum length */
      if(length <= count)
      {
        lengths[length]++;  /* Increment the count of the words length */
      }
    }
  }

    /* Cose the given file */
  fclose(pFile);

  return FILE_OK;  /* -1 */
}

/******************************************************************************
   Function: words_starting_with

Description: Count the number of words in the given dictionary that start with
             the passed in letter.

     Inputs: dictionary  - File containing the list of words to look through.
             letter      - The letter that the counted words start with.

    Outputs: The number of word that start with the given letter.
******************************************************************************/
int words_starting_with(const char *dictionary, char letter)
{
  FILE *pFile;                /* Pointer to a file                           */
  char holder[LONGEST_WORD];  /* Character array to hold incoming file lines */
  int count = 0;              /* Number of words that start with letter      */
  
  
  pFile = fopen(dictionary, "r"); /* Open the passed in file */
  
    /* If the file did not open return an error message */
  if (pFile == NULL)
  {
    return FILE_ERR_OPEN;  /* -2 */
  }
  
  mystrupr(&letter);
  
    /* While we are not at the end of the file */
  do
  {
      /* If a new line was gotten */
    if(fgets(holder, LONGEST_WORD, pFile))
    {
      mystrupr(holder);                   /* Set the wor to upper case */
    
        /* If current word starts with the given letter */
      if (holder[0] == letter)
      {
        break;
      }
    }
  } while (!feof(pFile));
  
    /* While the current word starts with the given letter */
  while (holder[0] == letter)
  {
      /* If a new line was gotten */
    if(fgets(holder, LONGEST_WORD, pFile))
    {
      count++;           /* Increment the count       */
      mystrupr(holder);  /* Set the wor to upper case */
    }
    
  }
  
    /* Close the given file */
  fclose(pFile);
  
  return count;
}
