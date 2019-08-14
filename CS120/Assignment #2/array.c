/**************************************************************************
filename    array.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Assignment #2
due date    10/18/2018

Brief Description:
  Contains functions that manipulate vector arrays in various ways.
**************************************************************************/

/******************************************************************************
   Function: reverse_array

Description: Flip all the elements in an int array.

     Inputs: a[]  - An array of any size.
             size - The size of the incoming array.

    Outputs: N/A
******************************************************************************/
void reverse_array(int a[], int size)
{
  int i; /*looping variable*/
  int holder; /*holds a value while switching array elements around*/
  
  /*Loop through half the array while switching elements with the second half*/
  for (i = 0; i < size / 2; i++)
  {
    /*replace a left element with the coresponding right element*/
    holder = a[i];
    a[i] = a[size - 1 - i];
    a[size - 1 - i] = holder;
  }
} 

/******************************************************************************
   Function: add_arrays

Description: Add the two passed in arrays togeather into the third.

     Inputs: a[]  - First array to add.
             b[]  - Second array to add.
             c[]  - An array to hold the sum of the other arrays.
             size - The size of the arrays passed in.

    Outputs: N/A
******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
  int i; /*looping variable*/
  
  /*itterate through the arrays*/
  for (i = 0; i < size; i++)
  {
    /*put the sum of the same element from a and b into c*/
    c[i] = a[i] + b[i];
  }
}

/******************************************************************************
   Function: scalar_multiply

Description: Multiply the given array by the passed in scalar.

     Inputs: a[]        - An array to multiply.
             size       - Size of the array passed in.
             multiplier - The number to multiply the array by.

    Outputs: N/A
******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i; /*loop variable*/
  
  /*itterate through the array*/
  for (i = 0; i < size; i++)
  {
    a[i] *= multiplier; /*multiply the current element by the multiplier*/
  }
}

/******************************************************************************
   Function: dot_product

Description: Evaluate and return the dot product of two vectors.

     Inputs: a[]  - First vector to get the dot product of.
             b[]  - Second vector to get the dot product of.
             size - Size of the arrays past in.

    Outputs: int - the dot product of the two incoming arrays
******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int i; /*loop variable*/
  int holder = 0; /*holds the value of the dot product to be returned*/
  
  /*itterate through the arrays*/
  for (i = 0; i < size; i++)
  {
    holder += a[i] * b[i]; /*increase holder by current elements product*/
  }
  
  return holder;
}

/******************************************************************************
   Function: cross_product

Description: Take the cross product of a and b, putting it into c.
             Only works with arrays with size 3

     Inputs: a[] - First vector to get the cross product of.
             b[] - Second vector to get the cross product of.
             c[] - Vector holding the cross product of the other two vectors.

    Outputs: N/A
******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
  /*cross product equation filling out the c array*/
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
}