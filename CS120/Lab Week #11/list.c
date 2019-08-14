/**************************************************************************
filename    list.c
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Programming Lab Week #11
due date    11/21/2018

Brief Description:
  Functions to modify or get information about nodes of linked lists.
**************************************************************************/

#include <stdio.h>   /* printf              */
#include <stdlib.h>  /* malloc              */
#include "list.h"    /* function prototypes */

/******************************************************************************
   Function: add_front

Description: Create a new node and put it in the front of the given list.

     Inputs: list  - The pointer to the start of the linked list.
             value - Value to be put in the new node.

    Outputs: None.
******************************************************************************/
void add_front(struct Node **list, int value)
{
    /* make a new node and allocate momory for it */
  struct Node *new = malloc(sizeof(struct Node));
  
    /* if the new node memory was successfully allocated */
  if (new != NULL)
  {
      /* set values for the new node */
    new->number = value;
    new->next = *list;
  
      /* make the new node the start of the list */
    *list = new;
  }
}

/******************************************************************************
   Function: add_back

Description: Create and add a new node to the end of the given linked list.

     Inputs: list  - The pointer to the start of the linked list.
             value - Value to be put in the new node.

    Outputs: None.
******************************************************************************/
void add_back(struct Node **list, int value)
{
    /* new node to be added to the list */
  struct Node *new = malloc(sizeof(struct Node));
  
    /* if the ne node had memory allocated corectly */
  if (new != NULL)
  {
      /* set the values for new node */
    new->number = value;
    new->next = NULL;
  
      /* if the list is not empty */
    if(*list != NULL)
    {
      struct Node *pWalker = *list; /* pointer to walk to the end of list */
    
        /* while not at the end of the list */
      while (pWalker->next != NULL)
      {
          /* move to next node in the list */
        pWalker = pWalker->next;
      }
      /* add the new lode to the list */
      pWalker->next = new;
    }
    
      /* if the list is empty */
    else
    {
        /* set the list to be the new node */
      *list = new;
    }
  }
}

/******************************************************************************
   Function: free_list

Description: Free all nodes in a given list.

     Inputs: list - Pointer to the head of a linked list.

    Outputs: None.
******************************************************************************/
void free_list(struct Node *list)
{
  struct Node *pWalker = list; /* pointer to the next node in the list */
  
    /* while there are still nodes in the list */
  while (pWalker != NULL)
  {
    pWalker = list->next;  /* set the next node                 */
    free(list);            /* free current node                 */
    list = pWalker;        /* set current node to the next node */
  }
}

/******************************************************************************
   Function: print_list

Description: Print all nodes in a given linked list to the screen.

     Inputs: list - Pointer to the start of a linked list.

    Outputs: None.
******************************************************************************/
void print_list(const struct Node *list)
{
    /* while there are nodes in the list */
  while (list != NULL)
  {
    printf(" %2i", list->number); /* print the current node to the screen */
    list = list->next;            /* set current node to the next node    */
  }
  printf("\n"); /* after finishing printing all the nodes, print a new line */
}

/******************************************************************************
   Function: remove_item

Description: remove a node of the given value from a linked list.

     Inputs: list  - Pointer to a pointer of the start of a linked list.
             value - The value to remove from the list.

    Outputs: None.
******************************************************************************/
void remove_item(struct Node **list, int value)
{
  struct Node *pOther = *list; /* pointer to the start of the list */
  
    /* if the list is empty */
  if (pOther == NULL)
  {
    return;
  }
    /* if the first node is the value to be removed */
  else if (pOther->number == value)
  {
    *list = pOther->next; /* set the passed in pointer to the next node */
    pOther->next = NULL;  /* set the first nodes next to null           */
    free(pOther);         /* free the first pointer                     */
  }
    /* if there are more noces to check */
  else if(pOther->next != NULL)
  {
    struct Node *pWalker = pOther->next; /* pointer to walk through the list */
    
      /* walk through the list until the end or the value is found */
    while (pWalker->next != NULL && pWalker->number != value)
    {
      pWalker = pWalker->next; /* set current node to next node     */
      pOther = pOther->next;   /* set previous node to current node */
    }
      /* if the value to remove was found */
    if(pWalker->number == value)
    {
      pOther->next = pWalker->next; /* set previous nodes next to next node */
      pWalker->next = NULL;         /* set current nodes next to null       */
      free(pWalker);                /* free the current node                */
    }
  }
}

/******************************************************************************
   Function: size_list

Description: Calculate how many nodes are in the incoming linked list.

     Inputs: list - Pointer to the start of a linked list.

    Outputs: The number of nodes in the passed in list.
******************************************************************************/
int size_list(const struct Node *list)
{
  int count = 0; /* the number of nodes in the linked list */
  
    /* while there is a node to read */
  while (list)
  {
    list = list->next;  /* set current node to the next node */
    count++;            /* increment the count by one        */
  }
  
  return count;
}

/******************************************************************************
   Function: sum_list

Description: Calculate the sum of the values in the incoming linked list.

     Inputs: list - Pointer to the start of a linked list.

    Outputs: The sum of the value stored in each node of the list passed in.
******************************************************************************/
int sum_list(const struct Node *list)
{
  int sum = 0;  /* the sum ofthe numbers in the linked list */

  
    /* while there is a node to read */
  while (list)
  {
    sum += list->number; /* add the value of the current node to the sum */
    list = list->next;   /* set current node to the next node            */
  }
  
  return sum;
}