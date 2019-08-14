#include <iostream> // cout, endl
#include <ctime>    // time_t, clock
#include <cstdlib>  // atoi
#include "Vector.h"
#include "PRNG.h"

#define PRINT_RESULTS
bool gShowTime = false;

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = CS170::Utils::Random(low, high); 
  return number;
}

void Shuffle(int *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    int r = CS170::Utils::Random(0, 2 << 29) % size;
    int t = array[i];
    array[i] = array[r];
    array[r] = t;
  }
}  

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

#ifdef PRINT_RESULTS
void PrintSortResults(const CS170::Vector::SortResult& results)
{
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
}
#else
void PrintSortResults(const CS170::Vector::SortResult&)
{
}
#endif

void TestSelectionSort1(int count)
{
  std::cout << "\n********** TestSelectionSort1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count * 2));

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();

  PrintSortResults(results);
  Print(a);
}

void TestSelectionSort2(int count)
{
  std::cout << "\n********** TestSelectionSort2 **********\n";
  CS170::Vector a;

  std::cout << "push_back " << count << " integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(i);

  Print(a);
  results = a.selection_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(5);

  Print(a);
  results = a.selection_sort();
  PrintSortResults(results);
  Print(a);
}

void TestSelectionSortStress(int count)
{
  std::cout << "\n********** TestSelectionSortStress **********\n";
  CS170::Vector a;

  CS170::Utils::srand(6, 0);

  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count));

  CS170::Vector::SortResult results = a.selection_sort();

  PrintSortResults(results);
  for (unsigned i = 1; i < static_cast<unsigned>(count); i *= 2)
    std::cout << a[i] << "  ";
  std::cout << std::endl;
  //Print(a);
}

void TestBSearch1(int count)
{
  std::cout << "\n********** TestBSearch1 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 10 random integers:\n";
  for (unsigned i = 0; i < static_cast<unsigned>(count); i++)
  {
    a.push_back(RandomInt(1000, 9999));
    b.push_back(a[i]);
  }

  Print(a);
  a.selection_sort();
  Print(a);

  for (unsigned i = 0; i < a.size(); i++)
  {
    int index = a.bsearch(b[i]);
    if (index != CS170::Vector::NO_INDEX)
      std::cout << "Index of " << b[i] << " is " << index << std::endl;
    else
      std::cout << b[i] << " is not in the vector" << std::endl;
  }
    // Doesn't exist
  int index = a.bsearch(99);
  if (index != CS170::Vector::NO_INDEX)
    std::cout << "Index of 99 is " << index << std::endl;
  else
    std::cout << "99 is not in the vector" << std::endl;
}

void TestBSearchStress(int count)
{
  std::cout << "\n********** TestBSearchStress **********\n";
  CS170::Vector a;

  int *ia = new int[count * 2];

  std::cout << "Generating...\n";
  for (int i = 0; i < count * 2; i++)
    ia[i] = i;

  std::cout << "Shuffling...\n";
  Shuffle(ia, count * 2);

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(ia[i]);

  //Print(a);
  a.selection_sort();
  //Print(a);

  std::cout << "Searching...\n";
  std::time_t start = std::clock();
  for (int i = 0; i < count; i++)
  {
    for (int j = 0; j < count; j++)
    {
      int index = a.bsearch(ia[i]);
      if ((j == 0) && !(i % 1000))
        std::cout << "Index of " << ia[i] << " is " << index << std::endl;
    }
  }
  std::time_t end = std::clock();
  std::cout << "Done...\n";
  if (gShowTime)
    std::cout << "Elapsed time: " <<  (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

  delete [] ia;
}

int main(int argc, char **argv)
{
  CS170::Utils::srand(1, 0);

  int test = 0;
  if (argc > 1)
    test = std::atoi(argv[1]);

  struct TestInfo
  {
    void (*fn)(int);
    int count;
  };

  TestInfo Tests[] = {
                        {TestSelectionSort1,         10}, // 1 
                        {TestSelectionSort1,         20}, // 2 
                        {TestSelectionSort2,         10}, // 3 
                        {TestSelectionSort2,         20}, // 4 
                        {TestBSearch1,               10}, // 5 
                        {TestBSearch1,               20}, // 6 
                        {TestBSearchStress,        5000}, // 7 
                        {TestSelectionSortStress, 10000}  // 8 
                     };

  int num = static_cast<int>(sizeof(Tests) / sizeof(*Tests));

  if (test == 99)
  {
    for (int i = 0; i < num - 2; i++)
      Tests[i].fn(Tests[i].count);
  }
  else if (test > 0)
  {
    Tests[test - 1].fn(Tests[test - 1].count);
  }
  else
  {
    for (int i = 0; i < num; i++)
      Tests[i].fn(Tests[i].count);
  }

  return 0;
}
