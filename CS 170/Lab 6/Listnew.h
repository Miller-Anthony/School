////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace ListLab
  {
    struct Node
    {
      int number; // data portion
      Node *next; // pointer to next node in list

        // Conversion constructor
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

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
          // Only finds the first occurrence of value
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

          // Displays the list
        friend std::ostream& operator<<(std::ostream &os, const List& rhs);

      private:
        Node *head_;
        Node* MakeNode(int value) const;

          // Other private stuff ...
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H
