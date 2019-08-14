/*!*************************************************************************
\file       List.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #5
\date       02/14/2019

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
    
    Hours spent on this assignment: 1

  Specific portions that gave you the most trouble: I have had practice with
    object creation before, so it was no issue converting List.cpp to a class
**************************************************************************/

#include <iostream> // cout, endl
#include "List.h"

/*******************************************************************/
/*******************************************************************/
namespace CS170
{
  namespace ListLab
  {
    List::List()
    {
      head_ = 0;
    }
    
    List::~List()
    {
      FreeList();
    }

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
    Node* List::MakeNode(int value) const
    {
        // The Node constructor sets the value, and sets next to 0.
      return new Node(value);
    }

    /*************************************************************************/
    /*!

      \brief
        Print all nodes in a given linked list to the screen.

    */
    /*************************************************************************/
    void List::PrintList() const
    {
      Node *list = head_;
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

      \return
        Number of nodes in the list
    */
    /*************************************************************************/
    int List::Count()
    {
      int count = 0; // Number of nodes in the list
      Node *list = head_;
      
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
            
      \param value
        Value to be put in the new node.

    */
    /*************************************************************************/
    void List::AddToEnd(int value)
    {
        /* new node to be added to the list */
      struct Node *holder = MakeNode(value);
      Node *list = head_;
  
        /* if the ne node had memory allocated corectly */
      if (holder != 0)
      {
          /* if the list is not empty */
        if(list != 0)
        {
            /* while not at the end of the list */
          while (list->next != 0)
          {
              /* move to next node in the list */
            list = list->next;
          }
          /* add the new lode to the list */
          list->next = holder;
        }
        
        /* if the list is empty */
        else
        {
            /* set the list to be the new node */
          head_ = holder;
        }
      }
    }

    /*************************************************************************/
    /*!

      \brief
        Create a new node and put it in the front of the given list.
        
      \param value
        Value to be put in the new node.

    */
    /*************************************************************************/
    void List::AddToFront(int value)
    {
        /* make a new node and allocate momory for it */
      struct Node *holder = MakeNode(value);
      Node *list = head_;
  
        /* if the new node memory was successfully allocated */
      if (holder != 0)
      {
          /* set next for the new node to the passed in list */
        holder->next = list;
      }
        /* make the new node the start of the list */
      head_ = holder;
    }

    /*************************************************************************/
    /*!

      \brief
        Finds an item and returns the node that contains it.
        
      \param value
        Value that is being looked for in a node.

      \return
        A node with the given value
    */
    /*************************************************************************/
    Node *List::FindItem(int value)
    {
      Node *list = head_; /* pointer to the next node in the list */
  
        /* while there are still nodes in the list */
      while (list != 0)
      {
          /* If the current node contains what is being looked for */
        if(list->number == value)
        {
          return list;
        }
        list = list->next;
      }
      return list;
    }

    /*************************************************************************/
    /*!
    
      \brief
        Free all nodes in a given list.

    */
    /*************************************************************************/
    void List::FreeList()
    {
      Node *list = head_; /* Pointer to the next node in the list */
  
        /* While there are still nodes in the list */
      while (list != 0)
      {
        list = head_->next;  /* Set the next node                 */
        delete head_;        /* Delete current node               */
        head_ = list;        /* Set current node to the next node */
      }
    }

    /*************************************************************************/
    /*!
    
      \brief
        Inserts a new node at the specified position.
        
      \param value
        Value to be put in the new node.
        
      \param position
        Where in the list to put the new node.

    */
    /*************************************************************************/
    void List::Insert(int value, int position)
    {
        /* If the position is at the front, add the node and exit early */
      if (position == 0)
      {
        AddToFront(value);
        return;
      }
      
      int count = 1;      /* Track current position of the list */
      Node *list = head_; /* Pointer to walk the list           */

        /* While there is still a list to go through and not to position */
      while(count < position && list->next != 0)
      {
          /* Walk the list and increment the count */
        list = list->next;
        count++;
      }
    
        /* If the list did not end before getting to position */
      if (count == position)
      {
        struct Node *holder = MakeNode(value); /* New node for the list */

          /* Add the new node to the list */
        holder->next = list->next;
        list->next = holder;
      }
    }
  } // namespace ListLab
} // namespace CS170
