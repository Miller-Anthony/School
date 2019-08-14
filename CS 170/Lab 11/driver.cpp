#include "Vector.h"
#include <iostream> // cout, endl

void Print(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 0; i < array.size(); i++)
  {
    std::cout << array[i] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void PrintPartial(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 1; i < array.size(); i *= 2)
  {
    std::cout << array[i - 1] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void TestSwap1()
{
  std::cout << "\n********** TestSwap1 **********\n";
  CS170::Vector a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 5; i++)
    b.push_back(10 * (i + 1));

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,b:\n";
  a.swapv(b);
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,c:\n";
  a.swapv(c);
  std::cout << "a: ";
  Print(a);
  std::cout << "c: ";
  Print(c);

  std::cout << "swapv b,b:\n";
  b.swapv(b);
  std::cout << "b: ";
  Print(b);
}

void TestReverse1()
{
  int count = 10;
  std::cout << "\n********** TestReverse1 **********\n";
  CS170::Vector a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  std::cout << "Remove last element:\n";
  a.pop_back();
  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);
}

void TestReverse2()
{
  int count = 10;
  std::cout << "\n********** TestReverse2 **********\n";
  CS170::Vector a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  while (!a.empty())
  {
    if (a.size() % 2) // odd
    {
      std::cout << "Remove last element:\n";
      a.pop_back();
    }
    else // even
    {
      std::cout << "Remove first element:\n";
      a.pop_front();
    }
    Print(a);
    a.reverse();
    std::cout << "Reversed:\n";
    Print(a);
  }
}

void TestEqual1()
{
  std::cout << "\n********** TestEqual1 **********\n";
  CS170::Vector a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 10; i++)
    b.push_back(i + 1);

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of a:\n";
  a.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of b:\n";
  b.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "change last element of b to 100:\n";
  b[b.size() - 1] = 100;
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";
}

/*
  Before C++17, the exception output was undefined. Now, it is guaranteed
  to print out the text before the exception gets thrown. This means that 
  this define is no longer needed. However, it's still fine and will work
  with all compilers.
*/
#define SAFE_EXCEPTION
void TestSubscriptEx()
{
  std::cout << "\n********** TestSubscriptEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia) / sizeof(*ia));
  std::cout << "Construct from int array:\n";

  const CS170::Vector a(ia, size); // const
  CS170::Vector b(ia, size);       // non-const
  Print(a);
  Print(b);

  try
  {
    unsigned index = a.size() * 2; // illegal
    std::cout << "accessing subscript on const vector: a[" << index << "]" << std::endl;
    #ifdef SAFE_EXCEPTION
      std::cout << "a[" << index << "] = ";
      std::cout.flush();
      std::cout << a[index] << std::endl;
    #else
      std::cout << "a[" << index << "] = " << a[index] << std::endl;
    #endif
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }

  try
  {
    unsigned index = b.size() * 2; // illegal
    std::cout << "accessing subscript on non-const vector: b[" << index << "]" << std::endl;
    #ifdef SAFE_EXCEPTION
      std::cout << "b[" << index << "] = ";
      std::cout.flush();
      std::cout << b[index] << std::endl;
    #else
      std::cout << "b[" << index << "] = " << b[index] << std::endl;
    #endif
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }
}

void TestInsertEx()
{
  std::cout << "\n********** TestInsertEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia) / sizeof(*ia));
  std::cout << "Construct from int array:\n";
  CS170::Vector a(ia, size);
  Print(a);

  try
  {
    unsigned index = a.size() * 3; // illegal
    std::cout << "insert integer at index " << index << ":\n";
    a.insert(99, index);
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }
}

void TestSwapStress()
{
  std::cout << "\n********** TestSwapStress **********\n";
  CS170::Vector a, b, c;

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
  {
    a.push_back(i);
    b.push_back(i * 2);
    c.push_back(i * 3);
  }

  std::cout << "Swapping...\n";
  CS170::Vector x;
  for (int i = 0; i < 1000001; i++)
  {
    a.swapv(b);
    b.swapv(c);
    c.swapv(a);
  }

  PrintPartial(a);
  PrintPartial(b);
  PrintPartial(c);

  std::cout << "Done...\n";
}

void TestShrink1()
{
  std::cout << "\n********** TestShrink1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 8 integers:\n";
  for (int i = 0; i < 8; i++)
    a.push_back(i);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "pop last 3:\n";
  a.pop_back();
  a.pop_back();
  a.pop_back();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "push_back one integer:\n";
  a.push_back(100);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);
}

int main()
{
  TestSwap1();
  TestReverse1();
  TestReverse2();
  TestEqual1();
  TestShrink1();
  TestSubscriptEx();
  TestInsertEx();
  TestSwapStress();

  return 0;
}
