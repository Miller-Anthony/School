/*!*************************************************************************
\file       fibonacci.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #3
\date       01/31/2019

\brief
    Contains a function displaying the fibonacci sequence
  
  -fibonacci
    Shows up to the given fibonacci sequence.
**************************************************************************/

#include <iostream> // cout
#include <iomanip>  // 

/*!*****************************************************************************
\fn void fibonacci(int max)

\brief 
    Takes in a number, then outputs the fibonacci sequence up to the
    inputted number.

\param max
    The highest number of the fibonacci sequence to go to.

\return 
    N/A 
******************************************************************************/
void fibonacci(int max)
{
  std::cout << "           Fibonacci        Fibonacci" << std::endl;
  std::cout << " N           number          quotient" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << " 0             0                  N/A" << std::endl;
  std::cout << " 1             1                  N/A" << std::endl;

  int count = max;
  int fib1 = 0, fib2 = 1;
  for (int i = 2; i <= count; i++)
  {
    int next = fib1 + fib2;
    
    // Add statements to print here...
    std::cout << std::fixed << std::setprecision(16);
    std::cout << std::setw(2) << i;
    std::cout << std::setw(14) << next;
    std::cout << std::setw(21) << (double)next/(double)fib2 << '\n';

    fib1 = fib2;
    fib2 = next;
  }
}
