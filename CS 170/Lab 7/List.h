/*!*************************************************************************
\file       List.h
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #7
\date       03/07/2019
**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

//! namespace CS170
namespace CS170
{
  //! namespace ListLab
  namespace ListLab
  {
    //! Node structure for List class
    struct Node
    {
      
      int number; //!< data portion
      Node *next; //!< pointer portion 

      /*!*******************************************************************
        Conversion constructor

        \param value
          The data for the node
      *********************************************************************/
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

    //! Single-linked list class for CS170 labs
    class List
    {
      public:
          // Default constructor
        List();

          // Destructor
        ~List();
          
          // Adds a node to the end of the list
        void AddToEnd(int value);

          // Adds a node to the front of the list
        void AddToFront(int value);

          // Returns the number of nodes in the list
        int Count() const;
          
          // Finds an item and returns the node that contains it
        Node *FindItem(int value) const;

          // Inserts a new node at the specified position
        void Insert(int value, int position);
        
          // Deletes a node with the specified value (first occurrence only)
        void Delete(int value);

          // Concatenates two lists
        void Concat(const List& Source);

          // Deletes all of the values in the list that are in Items
        void Delete(const List& Items);

          // Inserts a new node in the correct position (sorted small to large)
        void Insert(int value);
        
          // Takes a sorted list and merges it into the list
        void Merge(List& rhs);
        
          // Displays the list
        friend std::ostream& operator<<(std::ostream &os, const List& rhs);
        
      private:
        Node *head_;  //!< Pointer to the front of the list
        
          // Makes a new node to 
        Node* MakeNode(int value) const;
        
          // Frees (deletes) all of the nodes in the list
        void FreeList();

      
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H