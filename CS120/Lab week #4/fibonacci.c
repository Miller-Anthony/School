/**************************************************************************
filename    fibonacci.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  week #4 lab
due date    10/03/2018

Brief Description:
  This program asks for a number between 2 and 46, then outputs the 
  fibonacci sequence up to the inputted number
**************************************************************************/
#include <stdio.h> /*printf, scanf*/

#define EXIT 1  /*number needed to exit the program*/
#define MAX 46  /*maximum number that can be entered*/
#define START 2   /*minimum number that can be entered without exiting*/

/**************************************************************************
  Function: running

Description: takes user input and outputs corisponding amount of the 
             fibonacci sequence.

  Inputs: None

  Outputs: tells the system it exited proporly
******************************************************************************/
int main(void)
{
  double fibQuot;   /*quotient for current intervul of the fibinacci sequence*/
  int i;            /*looping variable                                       */
  int fibNum;       /*the number the user inputs                             */
  int first = 0;    /*number used for fib sequence                           */
  int second = 1;   /*number used for fib sequence                           */
  int holder;       /*hold a number while calulating the next phib numbers   */
  
  /*keep asking for input until a valid input is entered*/
  do
  {
    /*prompt user for input*/
    printf("Enter the Fibonacci number to calculate.\n");
    printf("The number must be an integer between 2 and 46. ");
    printf("(Enter 1 to quit): ");
    
    /*get user input*/
    scanf("%i", &fibNum);
    
  } while(EXIT > fibNum || fibNum > MAX);
    
  /*if user enters 1, exit program*/
  if(fibNum == EXIT)
  {
    return 0;
  }
  
  /*display the header for the sequence*/
  printf("\n           Fibonacci        Fibonacci\n");
  printf(" N           number          quotient\n");
  printf("-------------------------------------\n");
  
  /*display the first two of the sequence*/
  printf(" 0             0                  N/A\n");
  printf(" 1             1                  N/A\n");
  
  /*itterate through the fib sequence until reaching the input number*/
  for(i = START; i <= fibNum; i++)
  {
    /*recalculate the fib numbers for the next sequence*/
    holder = first + second;
    first = second;
    second = holder;
    
    /*get the info for printf*/
    fibQuot = (double)second / (double)first;
    
    /*output current fib sequence info*/
    printf("%2i    %10i   %.16f\n", i, second, fibQuot);
    
  }
  
  return 0;
}