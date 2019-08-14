/*!*************************************************************************
\file       Vector.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Lab Week #12
\date       04/12/2019

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
    
  + swapv
    Swaps the contents of other with this Vector (Constant time)
    
  + reverse
      Reverses the order of the elements (Linear time)
  
  + shrink_to_fit
      Reallocates an array to match the size of the number of elements

  + selection_sort
      Sorts the elements using a selection sort.

  + bsearch
      Searches the vector using a binary search.
      
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
    
  + operator==
    Equality operator (Linear time)
    
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
    template to swap two of any data type
          
  \param a
    Left hand side data to be swapped
    
  \param b
    Right hand side data to be swapped

  */
  /***********************************************************************/ 
  template <typename T>
  void swap(T &a, T& b)
  { 
    T temp = a;
    a = b;
    b = temp;
  }

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
    array_ = new int[rhs.size_];  // Allocate a new array
    
      // fr each element in rhs
    for (unsigned i = 0; i < rhs.size_; ++i)
    {
      array_[i] = rhs.array_[i];  // Assign its coresponding value to the array
    }
    
    size_ = rhs.size_;      // Set the size to the size of rhs
    capacity_ = rhs.size_;  // Set the capacity to the size of rhs
    allocs_ = 1;            // Increment number of allocations
    
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
    array_ = new int[size];  // Allocate a new array
    
      // For the number of size
    for(unsigned i = 0; i < size; ++i)
    {
      array_[i] = array[i];  // Assign its coresponding value to the array
    }
    size_ = size;      // Set the size of the vector to the passed in size
    capacity_ = size;  // Set the capacity to the passed in size
    allocs_ = 1;       // Increment the number of allocs
  }

  /***********************************************************************/
  /*!

  \brief
    Destructor that delets the vector
  */
  /***********************************************************************/
  Vector::~Vector()
  {
      // If there is an array delete it
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
    for(unsigned i = size_; i > 0; --i)
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
      // If the vector is emprty, do nothing
    if(empty())
    {
      return;
    }
    
      //for the size of the array
    for(unsigned i = 0; i < size_; ++i)
    {
        // assign the value of the next element to the current one
      array_[i] = array_[i + 1];
    }
    
    --size_;  // Decrement size
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
    check_bounds(position);  // Make sure the position is within bounds
    
      // If the new element would go out of bounds, grow the array
    if (size_ == capacity_)
    {
      grow();
    }
    
      // For every element after the insertpoint
    for(unsigned i = size_; i > position; --i)
    {
        // Assign the value of the previous node to the next
      array_[i] = array_[i - 1];
    }
    
      // Insert the new value in its position and increment size
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
      // For each element in the array
    for(unsigned i = 0; i < size_; ++i)
    {
        // If the current element has the value we are looking for
      if (array_[i] == value)
      {
          // For each element after the one we are looking for
        for(; i < size_; ++i)
        {
            // Assign the current elements value to the next
          array_[i] = array_[i + 1];
        }
      }
    }
    --size_; // Decrement size
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
    if (array_)
    {
      delete[] array_;
    }
    array_ = NULL;
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
    Swaps the contents of other with this Vector (Constant time)
          
  \param other
    Second vector to swap the data with this vector.

  */
  /***********************************************************************/
  void Vector::swapv(Vector &other)
  {
      // Swap all the data of the two vectors
    swap(array_, other.array_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
    swap(allocs_, other.allocs_);
  }

  /***********************************************************************/
  /*!

  \brief
    Reverses the order of the elements (Linear time)
          
  */
  /***********************************************************************/
  void Vector::reverse()
  {
      // For half of the vector
    for (unsigned i = 0; i < size_ / 2; ++i)
    {
        //Swap it with the second half
      swap(array_[i], array_[(size_ - 1) - i]);
    }
  }
  
  /***********************************************************************/
  /*!

  \brief
    Reallocates an array to match the size of the number of elements

  */
  /***********************************************************************/
  void Vector::shrink_to_fit()
  {
      // If the capacity is larger than the size
    if (size_ != capacity_)
    {
      int *holder = new int[size_];  // Allocate a new array
      
        // for each element in the vector
      for (unsigned i = 0; i < size_; ++i)
      {
        holder[i] = array_[i];  // Assign the element to the new array
      }
      
      swap(array_, holder);  // Swap the old array for the new one
      
      capacity_ = size_;  // Set the capacity to the size
      ++allocs_;          // Increment the number of allocs
      
      delete[] holder;  // Delete the old array
    }
  }

  /***********************************************************************/
  /*!

  \brief
    Sorts the elements using a selection sort.

  \return 
    number of swaps/comparisons that occurred.
  */
  /***********************************************************************/
  Vector::SortResult Vector::selection_sort()
  {
    SortResult holder;    // Hold the results of the sort
    holder.compares = 0;  // Set the initial number of compares
    holder.swaps = 0;     // Set the initial number of swaps
    int smallLoc = 0;     // initialize location
    int smallNum = 0;     // Initialize small numer
    
      // Itterate through the vector
    for(unsigned i = 0; i < size_; ++i)
    {
      smallLoc = i;          // Set the location to the loop count
      smallNum = array_[i];  // Set the smallest number to the current element
      
        // The rest of the elements of the vector
      for(unsigned j = i + 1; j < size_; ++j)
      {
          // If the next element is smaller than the first
        if(smallNum > array_[j])
        {
          smallLoc = j;          // Store the location of the smaller number
          smallNum = array_[j];  // Store the smallest number
        }
        holder.compares = holder.compares + 1; // Increment compares
      }
      
        // If there was a smaller number in the vector after point i
      if(smallNum < array_[i])
      {
        swap(array_[i], array_[smallLoc]);  // Swap the two values of the vector
        holder.swaps = holder.swaps + 1;    // Increment the number of swaps
      }
    }
    return holder;
  }

  /***********************************************************************/
  /*!

  \brief
    Searches the vector using a binary search.
          
  \param value
    Second vector to copy the data on to this vector.

  \return 
    A reference to this vector with the data of the right vector.
  */
  /***********************************************************************/
  int Vector::bsearch(int value) const
  {
    unsigned middle = size_ / 2;  // Set the middle of the vector
    unsigned right = size_;       // Set the end of the vector
    unsigned left = 0;            // Set the start of the vector
    
      // While middle stays in and there is still vector to look through
    while(size_ > middle && array_[middle] != value)
    {
        // If the value is less that where we are looking
      if (value < array_[middle])
      {
          // Set the right to just left of where the middle was
        right = middle - 1;
          
          // Set the middle to between the left and new right
        middle = right - (right - left) / 2;
      }
      
        // If where we are looking is less than what we are looking for
      else if (array_[middle] < value)
      {
          // Set the left to just right of where the middle was
        left = middle + 1;
        
          // Set the middle to between the new left and right
        middle = left + (right - left) / 2;
      }
    }
    
    // if the middle went outside the vector
    if (size_ < middle)
    {
      return NO_INDEX;
    }
    
      // Return the index that was found
    return middle;
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
      // If the are not the same vector
    if (this != &rhs)
    {
        // If the rhs is bigger
      if(rhs.size_ > capacity_)
      {
          // Allocate a new array
        int *holder = new int[rhs.size_];
      
          // For each element in rhs
        for(unsigned i= 0; i < rhs.size_; ++i)
        {
            // assign the rhs value to the new array
          holder[i] = rhs.array_[i];
        }
      
        int *old = array_;      // Store the old array
        array_ = holder;        // Assign the new array to the vector
        capacity_ = rhs.size_;  // Set the new capacity of the vector
        allocs_ = rhs.allocs_;  // Set the new number of allocs
        
        delete[] old;  // Deleter the old vector
      }
      
        // If lhs is bigger
      else
      {
          // For each element in rhs
        for(unsigned i = 0; i < rhs.size_; ++i)
        {
            // assign rhs stored value to lhs
          array_[i] = rhs.array_[i];
        }
      }
      size_ = rhs.size_;  // Set the new size of the vector
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
      // Grow the array until it can fit both vectors
    while(size_ + rhs.size_ > capacity_)
    {
      grow();
    }
    
      // For each element in rhs
    for(unsigned i = size_; i < size_ + rhs.size_; ++i)
    {   
        // Add the rhs element to the lhs array
      array_[i] = rhs.array_[i - size_];
    }
    
      // Increase the size by the size of the rhs
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
    Vector holder;  // Vector to hold temp data
    
      // Allocate a new array to hold both vectors
    holder.array_ = new int[size_ + rhs.size_];
    
      // For each element in lhs
    for (unsigned i = 0; i < size_; ++i)
    {
      holder.array_[i] = array_[i]; // Assign the element to the new array
    }
    
      // for each element of the rhs
    for(unsigned i = size_; i < size_ + rhs.size_; ++i)
    {
        // Assign the element to the new array
      holder.array_[i] = rhs.array_[i - size_];
    }
    
      //Set holder stats to a combination of the two vectors stats
    holder.size_ = size_ + rhs.size_;
    holder.capacity_ = size_ + rhs.size_;
    
      // Set allocs of the new vector
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
      // Check bounds then return the value at index if good
    check_bounds(index);
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
      // Check bounds then return the value at index if good
    check_bounds(index);
    return *(array_ + index);
  }

  /***********************************************************************/
  /*!

  \brief
    Equality operator (Linear time)
          
  \param rhs
    Second vector to compare this vector to

  \return 
    Returns true if both vectors are the same size or it returns false.
  */
  /***********************************************************************/  
  bool Vector::operator==(const Vector& rhs) const
  {
      // If vector sizes are the same
    if (size_ == rhs.size_)
    {
        // If they are the same vector
      if(this == &rhs)
      {
        return true;
      }
      
        // For each element of the vectors
      for(unsigned i = 0; i < size_; ++i)
      {
          // If the current value is not the same
        if (array_[i] != rhs.array_[i])
        {
          return false;
        }
      }
      return true;
    }
    
    return false;
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
      throw SubscriptError(index);
    }
  }

  /***********************************************************************/
  /*!

  \brief
    Make a new node to be added to the linked list

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
    for(unsigned i = 0; i < size_; ++i)
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
