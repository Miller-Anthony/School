/**************************************************************************
filename    main.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Assignment #5
due date    11/13/2018

Brief Description:
  Functions for counting tabs, length and words in/of a string, or changing a
  a given character to something else.
**************************************************************************/

#include <stdio.h> /* printf */

/* Prototype from tablen.c */
void tablen(const char *filename);

int main(int argc, char **argv)
{
    /* Must be given a filename */
  if (argc < 2)
  {
    printf("Usage: tablen filename\n");
    printf("where: filename - file to process.\n");
    return -1;
  }

  tablen(argv[1]);

  return 0;
}