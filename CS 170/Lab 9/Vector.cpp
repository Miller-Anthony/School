/*!*************************************************************************
\file       Vector.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #9
\date       03/22/2019

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

  Specific portions that gave you the most trouble: There were no significant
    Issues while coding this file.
**************************************************************************/

#include "Vector.h"
#include <iostream>  // cout
#include <cstdlib>   // abort

namespace CS170
{
  /***********************************************************************/
  /*!

  \brief
    Default constructor for a vector
  */
  /***********************************************************************/
  Vector::Vector() : array_(0), size_(0), capacity_(0), allocs_(0)
  {
    
  }

  /***********************************************************************/
  /*!

  \brief
    Destructor that delets the vector
  */
  /***********************************************************************/
  Vector::~Vector()
  {
    delete[] array_;
  }

  /***********************************************************************/
  /*!

  \brief
    Adds an element to the back of the vector
          
  \param value
    Value to inset into the vector
  */
  /***********************************************************************/
  void Vector::push_back(int value)
  {
      // If the vector is already full, grow its capacity
    if(size_ == capacity_)
    {
      grow();
    }
    
      // Assign the new value at the back and increment the size count
    array_[size_] = value;
    ++size_;
  }

  /***********************************************************************/
  /*!

  \brief
    Adds an element to the front of the vector
          
  \param value
    Value to inset into the vector
  */
  /***********************************************************************/
  void Vector::push_front(int value)
  {
      // If the vector is already full, grow its capacity
    if(size_ == capacity_)
    {
      grow();
    }
    
      // Move all data in the vector back by one
    for(int i = size_; i >= 0; --i)
    {
      array_[i] = array_[i - 1];
    }
    
      // Assign the new value at the front and increment the size count
    array_[0] = value;
    ++size_;
  }

  /***********************************************************************/
  /*!

  \brief
    Overload the [] operator to allow for easy array traversal
          
  \param index
    Offset value for pointer arithmatic.

  \return 
    Copy of the value at the passed in index
  */
  /***********************************************************************/
  int Vector::operator[](unsigned index) const
  {
    return *(array_ + index);
  }

  /***********************************************************************/
  /*!

  \brief
    Overload the [] operator to allow for easy array traversal
          
  \param index
    Offset value for pointer arithmatic.

  \return 
    reference to the value at the passed in index
  */
  /***********************************************************************/  
  int& Vector::operator[](unsigned index)
  {
    return *(array_ + index);
  }

  /***********************************************************************/
  /*!

  \brief
    Deletes the underlying array and sets size_ and capacity_ to 0.
  */
  /***********************************************************************/
  void Vector::clear()
  {
      //Delet the array and set its data to 0;
    delete[] array_;
    size_ = 0;
    capacity_ = 0;
  }

  /***********************************************************************/
  /*!

  \brief
    Check to see if the vector is empty or not

  \return 
    true if the vector is empty, otherwise, false
  */
  /***********************************************************************/
  bool Vector::empty() const
  {
    return size_ == 0;
  }

  /***********************************************************************/
  /*!

  \brief
    Returns the number of elements in the vector

  \return 
    Number of elements in the vector
  */
  /***********************************************************************/
  unsigned Vector::size() const
  {
    return size_;
  }

  /***********************************************************************/
  /*!

  \brief
    Returns the size of the underlying array
          
  \return 
    Size of the underlying array
  */
  /***********************************************************************/
  unsigned Vector::capacity() const
  {
    return capacity_;
  }

  /***********************************************************************/
  /*!

  \brief
    Returns the number of memory allocations that have occurred

  \return 
    Number of times the array has grown.
  */
  /***********************************************************************/
  unsigned Vector::allocations() const
  {
    return allocs_;
  }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

  /***********************************************************************/
  /*!

  \brief
    Make a new node to be added to the linked list
          
  \param index
    value to put in the node.
  */
  /***********************************************************************/
  void Vector::check_bounds(unsigned index) const
  {
      // Don't have to check for < 0 because index is unsigned
    if (index >= size_)
    {
      std::cout << "Attempting to access index " << index << ".";
      std::cout << " The size of the array is " << size_ << ". Aborting...\n";
      std::abort();
    }
  }

  /***********************************************************************/
  /*!

  \brief
    Make a new node to be added to the linked list
          
  \param value
    value to put in the node.
  */
  /***********************************************************************/
  void Vector::grow()
  {
      // Double the capacity
    if (capacity_)
      capacity_ *= 2;
    else
      capacity_ = 1;
      
      // Rest of the code here...
    int *holder = new int[capacity_];  // New array with doubled capacity
      
      // Coppy old array data to the new one
    for(unsigned int i = 0; i < size_; ++i)
    {
      holder[i] = array_[i];
    }
    
      // Assign the new array as the current one
    int *old = array_;
    array_ = holder;
    
    // delete the old array and increment how many times the array has grown
    delete[] old;
    ++allocs_;
  }

} // namespace CS170
