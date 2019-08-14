#include <stdio.h> /* printf */

/* Prints a calendar for the month and year */
void print_calendar(int month, int year);

int main(void)
{
  int year;  /* The current year  */
  int month; /* The current month */

    /* Print all calendars in the range 1900-2000, inclusive */
  for (year = 1900; year <= 2000; year++)
  {
    for (month = 1; month <= 12; month++)
    {
      print_calendar(month, year);
      printf("\n");
    }
  }

  return 0;
}