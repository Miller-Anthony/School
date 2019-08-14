#include <stdio.h>  /* printf              */
#include <stdlib.h> /* atoi                */
#include "PRNG.h"   /* RandomInt, ut_srand */
#include "list.h"

/*
int RandomInt(int low, int high)
{
  int number;
  number = rand() % (high - low + 1) + low;
  return number;
}
*/

static void test_add_front(void)
{
  int i;
  struct Node *list = NULL;

  printf("\ntest_add_front ========================================\n");
  for (i = 1; i <= 10; i++)
  {
    printf("add %2i to front: ", i);
    add_front(&list, i);
    print_list(list);
  }

  free_list(list);
}

static void test_add_back(void)
{
  int i;
  struct Node *list = NULL;

  printf("\ntest_add_back ========================================\n");
  for (i = 1; i <= 10; i++)
  {
    printf("add %2i to back: ", i);
    add_back(&list, i);
    print_list(list);
  }

  free_list(list);
}

static void test_add_front_back(void)
{
  int i;
  struct Node *list = NULL;

  printf("\ntest_add_front_back ========================================\n");
  for (i = 1; i <= 5; i++)
  {
    printf("add %2i to front and back: ", i);
    add_front(&list, i);
    add_back(&list, i);
    print_list(list);
  }

  free_list(list);
}

static void test_remove(void)
{
  int i;
  struct Node *list = NULL;
  int items[] = {5, 6, 10, 9, 2, 1, 3, 7, 8, 4};

  printf("\ntest_remove ========================================\n");
    /* Populate the list */
  for (i = 1; i <= 10; i++)
    add_front(&list, i);

  printf("Start list : ");
  print_list(list);

    /* These values don't exist, but you need to handle that */
  remove_item(&list, 100);
  remove_item(&list, 99);

    /* Remove "random" order */
  for (i = 0; i < 10; i++)
  {
    printf("Removing %2i: ", items[i]);
    remove_item(&list, items[i]);
    print_list(list);
  }

    /* List should empty, but this is legal */
  printf("Removing  0: ");
  remove_item(&list, 1); 
  print_list(list);

#if 1
  free_list(list); /* should be empty at this point           */
  free_list(NULL); /* This is legal and you need to handle it */
#endif
}

static void test_size(void)
{
  int i;
  struct Node *list = NULL;

  printf("\ntest_size ========================================\n");
  printf("Size is %2i: ", size_list(list));
  print_list(list);

  for (i = 1; i <= 10; i++)
  {
    add_front(&list, i);
    printf("Size is %2i: ", size_list(list));
    print_list(list);
  }

  free_list(list);
}

static void test_sum(void)
{
  int i, sum = 0;
  struct Node *list = NULL;

  printf("\ntest_sum ========================================\n");
  for (i = 1; i <= 10; i++)
    add_front(&list, i);

  sum = sum_list(list);
  print_list(list);
  printf("Sum is %i\n", sum);
  free_list(list);
}

static void test_A(void)
{
  int i;
  struct Node *list = NULL;
  int count = 50;
  int low = 1;
  int high = 20;

  printf("\ntest_A ========================================\n");
  for (i = 1; i <= count; i++)
    add_front(&list, RandomInt(low, high));

  print_list(list);
  printf("Size is %i.\n", size_list(list));
  printf("Sum is %i.\n", sum_list(list));

  for (i = 0; i < count; i++)
  {
    int r = RandomInt(low, high);
    printf("Remove %2i: ", r);
    remove_item(&list, r);
    print_list(list);
  }

  printf("Size is %i.\n", size_list(list));
  printf("Sum is %i.\n", sum_list(list));


  free_list(list);
}

int main(int argc, char **argv)
{
  int test = 0;

    /* An array of 7 function pointers taking nothing and returning nothing */
  void (*Tests[])(void) = {test_add_front,      /* 1 */
                           test_size,           /* 2 */
                           test_sum,            /* 3 */
                           test_add_back,       /* 4 */
                           test_add_front_back, /* 5 */
                           test_remove,         /* 6 */
                           test_A               /* 7 */
                          };

  int count = sizeof(Tests) / sizeof(*Tests);

  if (argc > 1)
    test = atoi(argv[1]);

  ut_srand(1, 0);

    /* If the number is out of range, run all tests */
  if (test <= 0 || test > count)
  {
    int i;
    
    for (i = 0; i < count; i++)
      Tests[i]();
  }
  else
    Tests[test - 1]();

  return 0;
}
