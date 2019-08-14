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

          //print out the current list
        void PrintList() const;
          
          // Adds a node to the end of the list
        void AddToEnd(int value);

          // Adds a node to the front of the list
        void AddToFront(int value);

          // Returns the number of nodes in the list
        int Count();
          
        // Finds an item and returns the node that contains it
        Node *FindItem(int value);

          // Inserts a new node at the specified position
        void Insert(int value, int position);
        
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
