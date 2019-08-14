/**************************************************************************
filename    scantext.c
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

#define TAB 9
#define NEW_LINE 10
#define SPACE 32

/******************************************************************************
   Function: mystrlen

Description: Calculate how many characters are in the incoming string.

     Inputs: string - A string to check the amount of characters it contains.

    Outputs: The number of characters in the passed in string.
******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0;  /* The number of characters in the string */
  
    /* Count the characters (not including the NUL) */
  while (*string++)
    length++;

  return length;
}

/******************************************************************************
   Function: count_tabs

Description: Count the number of tabs in the passed in string.

     Inputs: string - A string to check how many tabs it contains.

    Outputs: The number of tabs in the passed in string.
******************************************************************************/
int count_tabs(const char *string)
{
  int i;         /* looping variable                 */
  int count = 0; /* the amount of tabs in the string */
  
    /*itterate through the string*/
  for (i = 0; i < mystrlen(string); i++)
  {
      /*if the current character is a tab*/
    if (*(string + i) == TAB)
    {
      count++;
    }
  }
  
  return count;
}

/******************************************************************************
   Function: substitute_char

Description: replace the given characters in a string with new characters.

     Inputs: string   - A string to substitute chars in.
             old_char - The character to replace.
             new_char - The character to replace with.

    Outputs: The number of characters replaced.
******************************************************************************/
int substitute_char(char *string, char old_char, char new_char)
{
  int i;         /* looping variable                                */
  int count = 0; /* the amount of replaced characters in the string */
  
    /* itterate through the string */
  for (i = 0; i < mystrlen(string); i++)
  {
      /* if the current character is old_char */
    if (*(string + i) == old_char)
    {
        /* replace current character with the new_char and increment count */
      *(string + i) = new_char;
      count++;
    }
  }
  
  return count;
}

/******************************************************************************
   Function: calculate_lengths

Description: Calculate the actual and display length of the incoming string.

     Inputs: string         - A string to check how long it is.
             tabsize        - How long a single tab character is displayed as.
             string_length  - The actual length of the string.
             display_length - How long the string will be when displayed.

    Outputs: None.
******************************************************************************/
void calculate_lengths(const char *string, int tabsize,
                       int *string_length, int *display_length)
{
  int i;  /* looping variable */
  
    /* set the initial lengths to zero */
  *string_length = 0;   
  *display_length = 0;
  
    /* itterate through the string */
  for (i = 0; i < mystrlen(string); i++)
  {
      /* if the current character is a tab */
    if (*(string + i) == TAB)
    {
        /* increment the lengths by 1 and the size of a tab respectivly */
      (*string_length)++;
      *display_length += tabsize;
    }
      /* when current character is not a tab increment both lengths by one */
    else
    {
      (*string_length)++;
      (*display_length)++;
    }
  }
}

/******************************************************************************
   Function: count_words

Description: Calculate how many words are in the incoming string.

     Inputs: string - A string to check the amount of words it contains.

    Outputs: The number words found in the string.
******************************************************************************/
int count_words(const char *string)
{
  int i;         /* looping variable                  */
  int count = 0; /* the amount of words in the string */
  
    /* itterate through the string */
  for (i = 0; i < mystrlen(string); i++)
  {
      /* if the current character is white space */
    if (*(string + i) == TAB || *(string + i) == NEW_LINE
        || *(string + i) == SPACE)
    {
        /* itterate through the white space */
      while(*(string + i + 1) == TAB || *(string + i + 1) == NEW_LINE
            || *(string + i + 1) == SPACE)  
      {
        i++;
      }
    }
      /* if the current character is not white space */
    else
      {
          /* itterate through a word until whitespace or the end is found */
        while(*(string + i + 1) != TAB && *(string + i + 1) != NEW_LINE
            && *(string + i + 1) != SPACE && *(string + i + 1) != 0)
        {
          i++;
        }
        count++; /* count a word */
      }
  }
  
  return count;
}