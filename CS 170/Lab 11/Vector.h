/*!*************************************************************************
\file       Vector.h
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #11
\date       04/05/2019

\brief
    Various functions to crate and manage a vector array
**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

//! namespace CS170
namespace CS170
{
//! Error class for CS170 labs
class SubscriptError
{
  public:
    /***********************************************************************/
    /*!

    \brief
      Cunstructor for a SubscriptError
          
    \param Subscript
      The subscript that was trying to be accessed and caused an error

    \return 
      A reference to this vector with the data of the right vector.
    */
    /***********************************************************************/
    SubscriptError(int Subscript) : subscript_(Subscript) {};
    
    /***********************************************************************/
    /*!

    \brief
      grabs and returns the subscript that was attempted to be accessed

    \return 
      The subscript that was trying to be accessed and caused an error
    */
    /***********************************************************************/
    int GetSubscript() const { return subscript_; }

  private:
    int subscript_;  //!< the subscript value of the error
};

//! Array of ints for CS170 labs
class Vector
{
  public:

      // Default constructor
    Vector();

      // Destructor
    ~Vector();

      // Adds an element to the back of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items.
    void push_back(int value);

      // Adds an element to the front of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items. All items to the right must be
      // shifted over one element to the right.
    void push_front(int value);

      // Subscript operators for const and non-const
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Deletes the underlying array and sets size_ and capacity_ to 0.
      // Note that this behavior is different than how std::vector
      // implements clear. std::vector does not delete[] the array.
    void clear();

      // Return true if the vector is empty, otherwise, false
    bool empty() const;

      // Returns the number of elements in the vector.
    unsigned size() const;

      // Returns the size of the underlying array
    unsigned capacity() const;

      // The number of memory allocations that have occurred
    unsigned allocations() const;

      // Copy constructor
    Vector(const Vector& rhs);

      // Constructor to create a Vector from an array
    Vector(const int array[], unsigned size);

      // Removes the last element. Does nothing if empty.
    void pop_back();

      // Removes the first element. Does nothing if empty.
    void pop_front();

      // Inserts a new element at the specified position. Now throws an
      // exception if the position is invalid. (Calls check_bounds 
      // which is the function that is actually throwing.)
    void insert(int value, unsigned position);

      // Removes an element with the specified value (first occurrence)
    void remove(int value);

      // Assignment operator
    Vector& operator=(const Vector& rhs);

      // Concatenates a vector onto the end of this vector.
    Vector& operator+=(const Vector& rhs);

      // Concatenates two Vectors.
    Vector operator+(const Vector& rhs) const;

      // Swaps the contents of other with this Vector (Constant time)
    void swapv(Vector &other);

      // Reverses the order of the elements (Linear time)
    void reverse();

      // Equality operator (Linear time)
      // Both vectors must be the same size or it returns false.
    bool operator==(const Vector& rhs) const;

      // Reallocates an array to match the size of the number
      // of elements. If size == capacity, does nothing.
    void shrink_to_fit();

  private:
    int *array_;        //!< The dynamically allocated array
    unsigned size_;     //!< The number of elements in the array
    unsigned capacity_; //!< The allocated size of the array
    unsigned allocs_;   //!< Number of allocations (resizes)

    // Private methods...
    void check_bounds(unsigned index) const;
    void grow();
    
    // Other private methods...
};

} // namespace CS170

#endif // VECTOR_H
