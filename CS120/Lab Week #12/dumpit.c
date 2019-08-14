/**************************************************************************
filename    dumpit.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Lab #12
due date    12/02/2018

Brief Description:
  Display the hex data of a passed in file.
**************************************************************************/
#include <stdio.h>  /* printf sprintf puts */
#include <string.h> /* strlen strcat */

/* Longest formatted line is 75 characters */
#define MAXLEN 75
 
/*******************************************************************************
   Function: format

Description: Given an array of characters, format the characters as a line of
             hexadecimal numbers, including file offset and ASCII letters. Only
             the printable ASCII characters are displayed. Non-printable 
             characters are displayed as a period. The file offset is shown
             as a hexadecimal number.

     Inputs:  inbuf - The array of characters to format.
             outbuf - The formatted array, including offset and ASCII letters. 
              count - The number of characters in the input array.
             offset - The value of the 6-digit offset.

    Outputs: None. However, the outbuf parameter has been modified for the
             client.
*******************************************************************************/
void format(const char* inbuf, char *outbuf, int count, int offset)
{
  int i;                      /* Loop variable             */
  char holder[MAXLEN] = {0};  /* Holder for formatted data */
  
    /* Set the current offset */
  sprintf(outbuf, "%06X", offset);

   /* Format hex data for each char in inbuf */
  for (i = 0; i < count ; i++)
  {
      /* Add a space before each hex number */
    strcat(outbuf, " ");
    
      /* Format each byte as a hex number */  
    sprintf(holder, "%02X", (unsigned char)*(inbuf + i));
    
      /* Add the hex number to the end of buffer */
    strcat(outbuf, holder);
    
      /* Add an extra space between the 8th and 9th number */
    if(i == 7)
    {
      strcat(outbuf, " ");
    }
  }
  
    /* If the line was not long enough to add a space */
  if (i < 8)
  {
      /* Add the space anyways */
    strcat(outbuf, " ");
  }
  
    /* If the incoming line was not the full length */
  for(; i < 16; i++)
  {
      /* Fill in the remaining slots with spaces */
    strcat(outbuf, "   ");
  } 

    /* Put space between the hex and actual line */
  strcat(outbuf, "   ");
  
    /* Go through the input buffer again */
  for (i = 0; i < count; i++)
  {
      /* If the character is printable */
    if(31 < *(inbuf + i) && *(inbuf + i) < 127)
    {
        /* Append the ASCII representation of the character */ 
      sprintf(holder, "%c", *(inbuf + i));
    }
      /* If the character is not printable */
    else
    {
        /* Print a period instead */
      sprintf(holder, ".");
    }
      /* Add the formatted character to the end of buffer */
    strcat(outbuf, holder);
  }
}

/*******************************************************************************
   Function: dump

Description: Given a filename, read in the bytes and print their hexadecimal
             values to the screen. If the character is printable, print the
             character as well.
             
     Inputs: filename - The name of the file to dump in hex.

    Outputs: N/A
*******************************************************************************/
void dump(const char *filename)
{
  int offset = 0;  /* Current bit offset of the file */
  FILE *pFile;     /* Pointer to a file              */
  
    /* Open the file for read in binary */
  pFile = fopen(filename, "rb");
  
    /* If the file did not open */
  if (pFile == NULL)
  {
    /* print error message and return */
    printf("Can't open %s for binary read.\n", filename);
    return;
  }
    /* Print the filename to the screen followed by a colon */
  printf("\n%s:\n", filename);
  
    /* Print the first header line */
  printf("       00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n");
  
    /* Print the second header line */
  printf("-------------------------------------");
  printf("-------------------------------------\n");
  
    /* For all bytes in the file */
  while (!feof(pFile))
  {
    char holder[MAXLEN] = {0};  /* Array to hold incoming file lines  */
    char output[MAXLEN] = {0};  /* Array to be formatted for printing */
    int count;
    
    /* Read in bytes 16 at a time*/
    count = fread(holder, sizeof(char), 16, pFile);
    
    /* Format bytes using the format function above */
    format(holder, output, count, offset++ * 16);
    
    /* Print formatted string */
    puts(output);
  }

    /* Close the file */
  fclose(pFile);
}