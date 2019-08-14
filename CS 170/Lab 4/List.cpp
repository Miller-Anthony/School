/*!*************************************************************************
\file       List.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #4
\date       02/07/2019

\brief
    Various functions to crate and manage a linked list
  
  + AddToEnd
    Adds a node to the end of the list

  + AddToFront
    Adds a node to the front of the list

  + Count
    Returns the number of nodes in the list

  + FindItem
    Finds an item and returns the node that contains it

  + FreeList
    Frees (deletes) all of the nodes in the list

  + PrintList
    Prints all of the nodes values

  + Insert
    Inserts a new node at the specified position
**************************************************************************/

#include <iostream> // cout, endl
#include "List.h"

namespace CS170
{
  namespace ListLab
  {
    namespace 
    {
      /***********************************************************************/
      /*!

        \brief
          Make a new node to be added to the linked list
          
        \param value
          value to put in the node.

        \return 
          Node for a linked list
      */
      /***********************************************************************/
      struct Node* MakeNode(int value)
      {
        struct Node *pNode = new Node; // Allocate memory
        pNode->number = value;         // Set number
        pNode->next = 0;               // Set next (no next yet)

        return pNode;
      }
    }

    /*************************************************************************/
    /*!

      \brief
        Print all nodes in a given linked list to the screen.

      \param list
        Pointer to the start of a linked list.

    */
    /*************************************************************************/
    void PrintList(struct Node *list)
    {
      while (list)
      {
        std::cout << list->number << "   ";
        list = list->next;
      }
      std::cout << std::endl;
    }

    /*************************************************************************/
    /*!

      \brief
        Calculate how many nodes are in the incoming linked list.

      \param list
        Pointer to the start of a linked list.

      \return
        Number of nodes in the list
    */
    /*************************************************************************/
    int Count(struct Node *list)
    {
      int count = 0; // Number of nodes in the list
      
      while (list)
      {
        count++;
        list = list->next;
      }
      
      return count;
    }
    
    /*************************************************************************/
    /*!
    
      \brief
        Create and add a new node to the end of the given linked list.

      \param pList
        The pointer to the start of the linked list.
            
      \param value
        Value to be put in the new node.

    */
    /*************************************************************************/
    void AddToEnd(Node **pList, int value)
    {
        /* new node to be added to the list */
      struct Node *holder = MakeNode(value);
  
        /* if the ne node had memory allocated corectly */
      if (holder != NULL)
      {
          /* if the list is not empty */
        if(*pList != NULL)
        {
            /* pointer to walk to the end of list */
          struct Node *pWalker = *pList;
    
            /* while not at the end of the list */
          while (pWalker->next != NULL)
          {
              /* move to next node in the list */
            pWalker = pWalker->next;
          }
          /* add the new lode to the list */
          pWalker->next = holder;
        }
        
        /* if the list is empty */
        else
        {
            /* set the list to be the new node */
          *pList = holder;
        }
      }
    }

    /*************************************************************************/
    /*!

      \brief
        Create a new node and put it in the front of the given list.

      \param pList
        The pointer to the start of the linked list.
        
      \param value
        Value to be put in the new node.

    */
    /*************************************************************************/
    void AddToFront(Node **pList, int value)
    {
        /* make a new node and allocate momory for it */
      struct Node *holder = MakeNode(value);
  
        /* if the new node memory was successfully allocated */
      if (holder != NULL)
      {
          /* set next for the new node to the passed in list */
        holder->next = *pList;
      }
        /* make the new node the start of the list */
      *pList = holder;
    }

    /*************************************************************************/
    /*!

      \brief
        Finds an item and returns the node that contains it.

      \param list
        The pointer to the start of the linked list.
        
      \param value
        Value that is being looked for in a node.

      \return
        A node with the given value
    */
    /*************************************************************************/
    Node *FindItem(Node *list, int value)
    {
      struct Node *pWalker = list; /* pointer to the next node in the list */
  
        /* while there are still nodes in the list */
      while (pWalker != NULL)
      {
          /* If the current node contains what is being looked for */
        if(pWalker->number == value)
        {
          return pWalker;
        }
        pWalker = pWalker->next;
      }
      return pWalker;
    }

    /*************************************************************************/
    /*!
    
      \brief
        Free all nodes in a given list.

      \param pList
        Pointer to the head of a linked list.

    */
    /*************************************************************************/
    void FreeList(Node *pList)
    {
      struct Node *pWalker = pList; /* Pointer to the next node in the list */
  
        /* While there are still nodes in the list */
      while (pWalker != NULL)
      {
        pWalker = pList->next;  /* Set the next node                 */
        delete pList;           /* Delete current node               */
        pList = pWalker;        /* Set current node to the next node */
      }
    }

    /*************************************************************************/
    /*!
    
      \brief
        Inserts a new node at the specified position.

      \param pList
        Pointer to the head of a linked list.
        
      \param value
        Value to be put in the new node.
        
      \param position
        Where in the list to put the new node.

    */
    /*************************************************************************/
    void Insert(Node **pList, int value, int position)
    {
        /* If the position is at the front, add the node and exit early */
      if (position == 0)
      {
        AddToFront(pList, value);
        return;
      }
      
      int count = 1;                 /* Track current position of the list */
      struct Node *pWalker = *pList; /* Pointer to walk the list           */
      
        /* While there is still a list to go through and not to position */
      while(count < position && pWalker->next != NULL)
      {
          /* Walk the list and increment the count */
        pWalker = pWalker->next;
        count++;
      }
    
        /* If the list did not end before getting to position */
      if (count == position)
      {
        struct Node *holder = MakeNode(value); /* New node for the list */

          /* Add the new node to the list */
        holder->next = pWalker->next;
        pWalker->next = holder;
      }
    }
  } // namespace ListLab
} // namespace CS170
