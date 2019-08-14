/**************************************************************************
filename    calendar.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Assignment #4
due date    10/31/2018

Brief Description:
  Tell if a year is a leapyear, what day the given date falls on and prints
  out a calendar of the given month.
**************************************************************************/

#include <stdio.h>

#define TRUE  1
#define FALSE 0

/******************************************************************************
   Function: is_leapyear

Description: Calculate if the passed in year is a leapyear or not.

     Inputs: year - any year to see if it is a leapyear.

    Outputs: int - 1 if it is a leap year, 0 if it is not.
******************************************************************************/
int is_leapyear(int year)
{
  /*if the year is devisible by 4*/
  if(!(year % 4))
  {
    /*if the year is devisible by 100*/
    if(!(year % 100))
    {
      /*if the year is devisible by 400*/
      if(!(year % 400))
      {
        return TRUE;
      }
      return FALSE;
    }
    return TRUE;
  }
  return FALSE;
}

/******************************************************************************
   Function: day_of_the_week

Description: Calculate what day of the week the given date is on.

     Inputs: day   - day of the month.
             month - Month of the year.
             year  - Year of the date .

    Outputs: int - the day of the week as an int, with 1 for Sunday through 
                   7 for Saturday.
******************************************************************************/
int day_of_the_week(int day, int month, int year)
{
  /*Key values for the arithmatic in this equation*/
  int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
  int year_keys[] = {4, 2, 0, 6};
  int holder; /*holds the day of the week to return*/

  /*Extract the last 2 digits of the year and devide it by 4*/
  holder = (year % 100) / 4;
  
  /*add the day of the month and the key value of the month*/
  holder += (day + month_keys[month - 1]);
  
  /*if the monthe is Jan or Feb and it is a leapyear*/
  if(month < 3 && is_leapyear(year))
  {
    holder--; /*subtract 1 from the total*/
  }
  
  /*subtract 400 from the year until it falls in the key range*/
  while( year > 2099)
  {
    year -= 400;
  }
  
  /*add the given year key value depending on what year is passed in*/
  holder += year_keys[(year / 100) - 17];

  /*add the last two digits of the year then devide it by 7 before returning*/
  holder += (year % 100);
  holder %= 7;
  
  /*if the number to return is 0, return 7 instead*/
  if(holder == 0)
  {
    return 7;
  }

  return holder;
}

/******************************************************************************
   Function: print_calendar

Description: Print out the days of the month in calendar form for the passed 
             in month and year.

     Inputs: month - The month to print out.
             year  - The year to print out.

    Outputs: None
******************************************************************************/
void print_calendar(int month, int year)
{
  /*array holding the total number of days in each month*/
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  
  /*an array holding the names of each month*/
  char *months[] = {"January",   "February", "March",    "April", 
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};
  int i; /*looping variable*/

  /*if it is a leapyear february has an extra day*/
  if(is_leapyear(year))
  {
    days_in_month[1]++;
  }
    /* Print calendar header */
  printf("%s, %i\n", months[month - 1], year);
  printf("Su Mo Tu We Th Fr Sa\n");
  printf("---------------------\n");
  
  /*print the blanks in the first row of the dates*/
  for(i = 1; i < day_of_the_week(1, month, year); i++)
  {
    printf("   ");
  }
  
  /*set i to the first day of the month for the loop*/
  i = 1;
  
  /*continue looping until it has gone through each day of the month*/
  while (i <= days_in_month[month - 1])
  {
    /*add days to the row until it has reached the end of the week or month*/
    while(day_of_the_week(i, month, year) < 7 && i < days_in_month[month - 1])
    {
      printf("%2d ",i++);
    }
    printf("%2d \n",i++);
  }
  
}