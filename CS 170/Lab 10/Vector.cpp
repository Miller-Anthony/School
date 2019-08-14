/*!*************************************************************************
\file       Vector.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #10
\date       03/29/2019

\brief
    Various functions to crate and manage a vector array
  
  + push_back
    Adds an element to the front of the vector

  + push_front
    Adds an element to the end of the vector

  + pop_back
    "Removes" the last element. Does nothing if empty.

  + pop_front
    Removes the first element. Does nothing if empty.

  + Insert
    Inserts a new element at the specified position.
    
  + remove
    Removes an element with the specified value (first occurrence)
    
  + clear
    Deletes the underlying array and sets size_ and capacity_ to 0.
    
  + empty
    Return true if the vector is empty, otherwise, false
    
  + operator=
    Copy assignment operator
    
  + operator+=
    Concatenates a vector onto the end of this vector.
    
  + operator+
    Concatenates two Vectors.
    
  + operator[]
    Overload the [] operator to allow for easy array traversal
    
  + operator[]
    Overload the [] operator to allow for easy array traversal
    
  + size
    Returns the number of elements in the vector.
    
  + capacity
    Returns the size of the underlying array
    
  + allocations
    The number of memory allocations that have occurred
    
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
  
   // Copy constructor
  /***********************************************************************/
  /*!

  \brief
    Copy constructor
          
  \param rhs
    Vector to create a copy of
  */
  /***********************************************************************/
  Vector::Vector(const Vector& rhs)
  {
    array_ = new int[rhs.size_];
    
    for (unsigned int i = 0; i < rhs.size_; ++i)
    {
      array_[i] = rhs.array_[i];
    }
    
    size_ = rhs.size_;
    capacity_ = rhs.size_;
    allocs_ = 1;
    
  }
  
    // Constructor to create a Vector from an array
  /***********************************************************************/
  /*!

  \brief
    Constructor to create a Vector from an array
          
  \param array
    Values to store in the created vector
    
  \param size
    Size of the vector to create
  */
  /***********************************************************************/
  Vector::Vector(const int array[], unsigned size)
  {
    array_ = new int[size];
    for(unsigned int i = 0; i < size; ++i)
    {
      array_[i] = array[i];
    }
    size_ = size;
    capacity_ = size;
    allocs_ = 1;
  }

  /***********************************************************************/
  /*!

  \brief
    Destructor that delets the vector
  */
  /***********************************************************************/
  Vector::~Vector()
  {
    if(array_)
    {
      delete[] array_;
    }
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
    if(size_ >= capacity_)
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
    if(size_ >= capacity_)
    {
      grow();
    }
    
      // Move all data in the vector back by one
    for(unsigned int i = size_; i > 0; --i)
    {
      array_[i] = array_[i - 1];
    }
    
      // Assign the new value at the front and increment the size count
    array_[0] = value;
    ++size_;
  }
  
    // 
  /***********************************************************************/
  /*!

  \brief
    "Removes" the last element. Does nothing if empty.
  */
  /***********************************************************************/
  void Vector::pop_back()
  {
    if(!empty())
    {
      array_[size_ - 1] = 0;
      //decrease the size so it doesnt look at what was the end 
    --size_;
    }
  }
 
  /***********************************************************************/
  /*!

  \brief
    Removes the first element. Does nothing if empty.
  */
  /***********************************************************************/
  void Vector::pop_front()
  {
    if(empty())
    {
      return;
    }
    
    for(unsigned int i = 0; i < size_; ++i)
    {
      array_[i] = array_[i + 1];
    }
    
    --size_;
  }

  /***********************************************************************/
  /*!

  \brief
    Inserts a new element at the specified position.
          
  \param value
    Number to insert into the vector at the given position.

  \param position
    Position to insert the given value into the vector.
  */
  /***********************************************************************/
  void Vector::insert(int value, unsigned position)
  {
    check_bounds(position);
    
    if (size_ == capacity_)
    {
      grow();
    }
    
    for(unsigned int i = size_; i > position; --i)
    {
      array_[i] = array_[i - 1];
    }
    
    array_[position] = value;
    ++size_;
  }

  /***********************************************************************/
  /*!

  \brief
    Removes an element with the specified value (first occurrence)
          
  \param value
    Number to look for and remove from the vector.

  */
  /***********************************************************************/
  void Vector::remove(int value)
  {
    for(unsigned int i = 0; i < size_; ++i)
    {
      if (array_[i] == value)
      {
        for(; i < size_; ++i)
        {
          array_[i] = array_[i + 1];
        }
      }
    }
    --size_;
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
    Copy assignment operator.
          
  \param rhs
    Second vector to copy the data on to this vector.

  \return 
    A reference to this vector with the data of the right vector.
  */
  /***********************************************************************/
  Vector& Vector::operator=(const Vector& rhs)
  {
    if (this != &rhs)
    {
      if(rhs.size_ > capacity_)
      {
        int *holder = new int[rhs.size_];
      
        for(unsigned int i= 0; i < rhs.size_; ++i)
        {
          holder[i] = rhs.array_[i];
        }
      
        int *old = array_;
        array_ = holder;
        capacity_ = rhs.size_;
        allocs_ = rhs.allocs_;
        
        delete[] old;
      }
      else
      {
        for(unsigned int i = 0; i < rhs.size_; ++i)
        {
          array_[i] = rhs.array_[i];
        }
      }
      size_ = rhs.size_;
    }    
    return *this;
  }

  /***********************************************************************/
  /*!

  \brief
    Concatenates a vector onto the end of this vector.
          
  \param rhs
    Second vector to add to the end of this vector.

  \return 
    A reference to this vector with the right vector added to the end.
  */
  /***********************************************************************/
  Vector& Vector::operator+=(const Vector& rhs)
  {
    
    while(size_ + rhs.size_ > capacity_)
    {
      grow();
    }
    
    for(unsigned int i = size_; i < size_ + rhs.size_; ++i)
    {   
      array_[i] = rhs.array_[i - size_];
    }
    
    size_ += rhs.size_;
    
    return *this;
  }

  /***********************************************************************/
  /*!

  \brief
    Concatenates two Vectors.
          
  \param rhs
    Second vector to add to the end of the left vector.

  \return 
    A copy of the left hand vector with the right vector added to the end.
  */
  /***********************************************************************/
  Vector Vector::operator+(const Vector& rhs) const
  {
    Vector holder;
    
    holder.array_ = new int[size_ + rhs.size_];
    
    for (unsigned int i = 0; i < size_; ++i)
    {
      holder.array_[i] = array_[i];
    }
    
    for(unsigned int i = size_; i < size_ + rhs.size_; ++i)
    {
      holder.array_[i] = rhs.array_[i - size_];
    }
    
    holder.size_ = size_ + rhs.size_;
    holder.capacity_ = size_ + rhs.size_;
    holder.allocs_ = 1;
    
    return holder;
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
