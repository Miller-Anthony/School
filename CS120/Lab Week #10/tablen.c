/**************************************************************************
filename    tablen.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Assignment #5
due date    11/14/2018

Brief Description:
  Reads in a given file then prints a report on how many tabs and lines over 80
  characters there were.
**************************************************************************/

#include <stdio.h>   /* printf */
#include <string.h>  /* strlen */

#define MAX_LINE_LENGTH 1000  /* Assumed max length of a line           */
#define TAB 9                 /* Decimal value for a tab character      */
#define NEW_LINE 10           /* Decimal value for a new line character */
#define NUL '\0'              /* Char representation for string nul     */
#define LINE_LENGTH 80        /* Max length a line should be            */
#define ERROR 0               /* File failed to open                    */
#define SUCCESS 1             /* File opened and things ran correctly   */
#define ZERO 0                /* Zero                                   */

/******************************************************************************
   Function: countingTabs

Description: Open the given file and count the number of tabs in it, printing
             out a report on where the tabs are and how many total were found.

     Inputs: filename - The path for the file to open.

    Outputs: 1 if the file opened and things ran properly or 0 if the file did
             not open.
******************************************************************************/
int countingTabs(const char *filename)
{
  int i;             /* Looping variable                             */
  int lines = ZERO;  /* counts the current line number being read in */
  int tabs = ZERO;   /* count of total tabs in the file              */
  FILE * fp;         /* pointer to a file that will be read in       */
  
    /* Open the given file in read mode */
  fp = fopen(filename, "r");
  
    /* If the file failed to open, return 0 */
  if(!fp)
  {
    return ERROR;
  }
  
    /* read until the end of the file (fp) */
  while(!feof(fp))
  {
      /* character array to hold the lines read in from the file */
    char holder[MAX_LINE_LENGTH];
    
      /* if a line was read in successfully */
    if (fgets(holder, MAX_LINE_LENGTH, fp))
    {
      int length = strlen(holder);     /* the length of the current line     */
      int theseTabs = ZERO;            /* stores number of tabs for the line */
      lines++;                         /* Increment the line we are on       */
      
        /* Itterate through the current line */
      for (i = ZERO; i < length; i++)
      {
          /*if the current character is a tab increment the tab count*/
        if (holder[i] == TAB)
        {
          theseTabs++;
        }
          /* if it is the last character, replace it with a nul char */
        else if (holder[i] == NEW_LINE)
        {
          holder[i] = NUL;
        }
      }
        /* if any tabs were found */
      if (theseTabs)
      {
          /* increase the total number of tabs and print the line report */
        tabs += theseTabs;
        printf("#%3i: (tabs:%2i) |%s|\n", lines, theseTabs, holder);
      }
    }
  }
  
    /* make sure to close the file */
  fclose(fp);
  
    /* if there were any tabs */
  if (tabs)
  {
      /* print how many tabs were found in the file */
    printf("*****  TABS IN USE  *****: ");
    printf("Number of tabs in the file is %i.\n", tabs);
  }
    
  return SUCCESS;
}

/******************************************************************************
   Function: lineLength

Description: Calculate how many lines are are longer than 80 characters.

     Inputs: filename - The path for the file to open.

    Outputs: 1 if the file opened and things ran properly or 0 if the file did
             not open.
******************************************************************************/
int lineLength(const char *filename)
{
  int line = ZERO;       /* Looping variable                         */
  int lineTotal = ZERO;  /* Total number of lines over 80 characters */
  int longLine = ZERO;   /* Line number of the longest line          */
  int longChar = ZERO;   /* Amount of characters in the longest line */
  FILE * fp;             /* pointer to the file to open              */

    /* Open the given file in read mode */
  fp = fopen(filename, "r");
  
    /* If the file failed to open, return 0 */
  if(!fp)
  {
    return ERROR;
  }

    /* Read until the end of the file (fp) */
  while(!feof(fp))
  {
      /* Character array to hold the lines read in from the file */
    char holder[MAX_LINE_LENGTH];
    
      /* If a line was read in successfully */
    if (fgets(holder, MAX_LINE_LENGTH, fp))
    {
      int length = strlen(holder) - 1;  /* length of the current line */
      holder[length] = NUL;             /* Set the last char to nul   */
      line++;                           /* Increment the line count   */
      
        /*If length of the line is more than 80*/
      if (length > LINE_LENGTH)
      {
        lineTotal++;  /* increment how many lines are over 80 characters */
          /* Print out a report on the line that is over 80 characters */
        printf("#%3i: (%3i) |%s|\n", line, length, holder);
        
          /* If this is the longest line so far, update longest line stats */
        if(longChar < length)
        {
          longLine = line;
          longChar = length;
        }
      }
    }
  }
  
    /* make sure to close the file */
  fclose(fp);
  
    /* if any lines were over 80 characters */
  if(lineTotal)
  {
      /* print out a report on how many lines were over 80 characters */
    printf("***** LINE TOO LONG *****: %i lines longer than 80.", lineTotal);
    printf(" Longest line is %i at %i chars.\n", longLine, longChar);
  }
  
  return SUCCESS;
  
}

/******************************************************************************
   Function: tablen

Description: Calculate how many characters are in the incoming string.

     Inputs: string - A string to check the amount of characters it contains.

    Outputs: The number of characters in the passed in string.
******************************************************************************/
void tablen(const char *filename)
{
    /* If countingTabs if able to open its file */
  if(countingTabs(filename))
  {
      /* count lines that are to long */
    lineLength(filename);
  }
    /* If the file failed to open */
  else
  {
      /* print out that the file didnt open */
    printf("Can't open %s for read.", filename);
  }
}