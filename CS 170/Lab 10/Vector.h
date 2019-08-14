/*!*************************************************************************
\file       Vector.h
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #10
\date       03/29/2019

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
//! Array of ints for CS170 labs
class Vector
{
  public:

      // Default constructor
    Vector();

      // Destructor
    ~Vector();

      // Copy constructor
    Vector(const Vector& rhs);

      // Constructor to create a Vector from an array
    Vector(const int array[], unsigned size);

      // Adds an element to the front of the vector
    void push_back(int value);

      // Adds an element to the end of the vector
    void push_front(int value);

      // "Removes" the last element. Does nothing if empty.
    void pop_back();

      // Removes the first element. Does nothing if empty.
    void pop_front();

      // Inserts a new element at the specified position. Causes an
      // abort() if the position is invalid. (Calls check_bounds)
    void insert(int value, unsigned position);

      // Removes an element with the specified value (first occurrence)
    void remove(int value);

      // Deletes the underlying array and sets size_ and capacity_ to 0.
      // Note that this behavior is different than how std::vector
      // implements clear. std::vector does not delete[] the array.
    void clear();

      // Return true if the vector is empty, otherwise, false
    bool empty() const;

      // Copy assignment operator
    Vector& operator=(const Vector& rhs);

      // Concatenates a vector onto the end of this vector.
    Vector& operator+=(const Vector& rhs);

      // Concatenates two Vectors.
    Vector operator+(const Vector& rhs) const;

      // Subscript operators.
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Returns the number of elements in the vector.
    unsigned size() const;

      // Returns the size of the underlying array
    unsigned capacity() const;

      // The number of memory allocations that have occurred
    unsigned allocations() const;

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
