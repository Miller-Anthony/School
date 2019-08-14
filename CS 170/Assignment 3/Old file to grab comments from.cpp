/*!*************************************************************************
\file       List.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #7
\date       03/07/2019

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

  + Insert
    Inserts a new node at the specified position
    
  + Delete
    Deletes a node with the specified value (first occurrence only)
    
  + Concat
    Concatenates two lists
    
  + Delete
    Deletes all of the values in the list that are in Items
    
  + Insert
    Inserts a new node in the correct position (sorted small to large)
    
  + Merge
    Takes a sorted list and merges it into the list
    
  + operator<<
    Displays the list
    
    Hours spent on this assignment: 2

  Specific portions that gave you the most trouble: I spent almost a half hour 
    trying to find a computer that had a working version of drmemory.
    The computers in the Academic Support Center were not working, and I had
    to try three in Edison before finding one that worked.
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
        Calculate how many nodes are in the incoming linked list.

      \return
        Number of nodes in the list
    */
    /*************************************************************************/
    int List::Count() const
    {
      int count = 0; // Number of nodes in the list
      Node *list = head_;
      
      while (list != 0)
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
  
        /* if the new node had memory allocated corectly */
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
    Node *List::FindItem(int value) const
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
    
    /*************************************************************************/
    /*!
    
      \brief
        Deletes a node with the specified value (first occurrence only)
        
      \param value
        Value to be deleted from the list.

    */
    /*************************************************************************/
    void List::Delete(int value)
    {
        // If the list is empty
      if (head_ == NULL)
      {
        return;
      }
      
      Node *list = head_; // Pointer to walk the list
      
      if (list->number == value)
      {        
        head_ = head_->next; // Set the front of the list to the next node
        delete list;       // Delete the node
        return;
      }
       
        // While there is more items in the list
      while (list->next->number != value && list->next->next != 0)
      {
          // Move to the next node
        list = list->next;
      }
      
      if (list->next->number == value)
      {
        Node *holder = list->next; // Pointer to the element to be deleted
           
            // Disconect the node to be deleted from the list
        list->next = list->next->next;
        holder->next = 0;
           
          // Delete the node
        delete holder;
      }
    }

    /*************************************************************************/
    /*!
    
      \brief
        Concatenates two lists.
        
      \param Source
        List of nodes to add to the end of the list.

    */
    /*************************************************************************/
    void List::Concat(const List& Source)
    {
      Node *second = Source.head_; // Pointer to walk the list
  
        // While there is a list to walk through
      while(second->next != 0)
      {       
          // Add the node to the end of the list and step to the next
        AddToEnd(second->number);
        second = second->next;
      }
        // Add the last node to the list
      AddToEnd(second->number);
    }

    /*************************************************************************/
    /*!
    
      \brief
        Deletes all of the values in the list that are in Items.
        
      \param Items
        Second list full of values to remove.

    */
    /*************************************************************************/
    void List::Delete(const List& Items)
    {
      Node *list = Items.head_; // Pointer to walk the passed in list
        
        // While there is a list to walk through
      while (list->next != 0)
      {
          // Delete the node(s) and step to the next node
        Delete(list->number);
        list = list->next;
      }
        // Delete the last value from the list
      Delete(list->number);
    }

    /*************************************************************************/
    /*!
    
      \brief
        Inserts a new node in the correct position (sorted small to large).
        
      \param value
        Value to be put in the new node.

    */
    /*************************************************************************/
    void List::Insert(int value)
    {
        // If there is no list yet
      if(head_ == NULL)
      {
        AddToFront(value);
        return;
      }
      
      int position = 0;   // Track current list position
      Node *list = head_; // Pointer to walk the list
      
        // While there is a list to walk through
      while (list->next != 0)
      {
          // If the value is larger than the node
        if (list->number <= value)
        {
            // Increment to the next node
          list = list->next;
          ++position;
        }
          // If the value is smaller than the node, stop looking
        if (list->number >= value)
        {
          break;
        }
      }
      
        // Make sure the position is correct if at end of list
      if(list->number <= value)
      {
        ++position;
      }
      
      Insert(value, position);
    }
    
    /*************************************************************************/
    /*!
    
      \brief
        Takes a sorted list and merges it into the list.
        
      \param rhs
        Sorted list to merge into the list object.

    */
    /*************************************************************************/
    void List::Merge(List& rhs)
    {
      Node *leftList;
      Node *rightList;
      
        //If there is a list
      if(head_ != NULL)
      {
          //Setup a pointer to the first node of the left list. (left)
        leftList = head_;
      }
      else
      {
        head_ = rhs.head_;
        rhs.head_ = NULL;
        return;
      }
      
       //If a list was passed in
      if(rhs.head_ != NULL)
      {
          //Setup a pointer to the first node of the right list (right)
        rightList = rhs.head_;
      }
      else
      {
        return;
      }
        //Setup a pointer to point to the head of the new list
      Node *firstNew = NULL;
        //Setup a pointer to point to the tail of the new list
      Node *lastNew = NULL;
      
      //While both pointers (left and right) are pointing at a node
      while(leftList != NULL && rightList != NULL)
      {
          //If the left node is less than or equal to the right node, 
        if(leftList->number <= rightList->number)
        {
            //Add the left node to the new list
          if(firstNew == NULL)
          {
              //Set the front and end of the list to the currant left node
            firstNew = leftList;
            lastNew = leftList;
          }
          else
          {
              //Append the left node to the end of the list
            lastNew->next = leftList;
              //Move the end of the list to the new end of the list
            lastNew = lastNew->next;
          }
          
          //Move the left pointer to the next node in the left list
          leftList = leftList->next;
        }
        //Else  (The left node is greater than the right node)
        else
        {
            //Add the right node to the new list
          if(firstNew == NULL)
          {
              //Set the front and end of the list to the currant right node
            firstNew = rightList;
            lastNew = rightList;
          }
          else
          {
              //Append the right node to the end of the list
            lastNew->next = rightList;
              //Move the end of the list to the new end of the list
            lastNew = lastNew->next;
          }
          
          //Move the right pointer to the next node in the right list
          rightList = rightList->next;
        }
      }

        //If the right side is empty and the left side still has nodes
      if(leftList != NULL)
      {
          //Add all of the nodes from the left side to the end of the new list
        lastNew->next = leftList;
      }
      
        //If the left side is empty and the right side still has nodes
      if(rightList != NULL)
      {
          //Add all of the nodes from the right side to the end of the new list
        lastNew->next = rightList;
      }
      
        // Update the heads of the lists to the new values.
      head_ = firstNew;
      rhs.head_ = NULL;
    }
    
    /*************************************************************************/
    /*!
    
      \brief
        Displays the list.
        
      \param os
        The stream being outputted to.
        
      \param rhs
        The list that is being displayed.
      
      \return 
        The output stream.

    */
    /*************************************************************************/
    std::ostream& operator<<(std::ostream &os, const List& rhs)
    {
      Node *list = rhs.head_; // Pointer to walk the list
      
        // While there is still list to walk
      while (list != 0)
      {
          //send the node to the os and step to the next node
        os << list->number << "   ";
        list = list->next;
      }
      return os;
    }
  } // namespace ListLab
} // namespace CS170
