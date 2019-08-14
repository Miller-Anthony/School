#include <stdio.h>
#include "histogram.h"

#define NUM_LETTERS 26

int main(void)
{
  int spaces;               /* The number of spaces in the string                 */
  int total;                /* The number of letters (a..z, A..Z) in the string   */
  int other;                /* The number of other characters in the string       */
  int letters[NUM_LETTERS]; /* The number of each individual letter in the string */

    /* Simple test sentence */
  const char *a = "This is simple - a sentence with spaces - and other punctuations.";

    /* Call function and print out results. Do you understand the second argument? */
  total = GetCounts(a, letters, &spaces, &other);
  printf("Count of letters is: %i, spaces: %i, other: %i\n", total, spaces, other);

  return 0;
}