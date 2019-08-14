/*!*************************************************************************
\file       Point.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Assignment #3
\date       03/13/2019

\brief
    Various overloaded functions to manipulate a points data
  
  + RadiansToDegrees
    Translates an angle from degrees to radians
    
  + RadiansToDegrees
    Translates an angle from radians to degrees
    
  + Point
    Default Constructor
    
  + Point
    Constructor for a point taking in its cordinates
    
  + operator%
    Overloads the % operator to rotate the point by the passed in angle

  + operator-
    Overloads the - operator to get the difference between the points
    
  + operator^
    Overloads the ^ operator to get the midpoint between two points
    
  + operator+=
    Overloads the += operator to increment a apoint by a point
    
  + operator+=
    Overloads the += operator to increment a apoint by a scalar
    
  + operator-
    Overloads the - operator to subtract a scalar from a point
    
  + operator++
    Overloads the ++ increase the x and y cordinates by 1
    
  + operator++
    Overloads the ++ increase the x and y cordinates by 1
    
  + operator--
    Overloads the -- decrease the x and y cordinates by 1
    
  + operator--
    Overloads the -- decrease the x and y cordinates by 1
      
  + operator-
    Overloads the - operator to get negative of the point

  + operator+
    Overloads the + operator to increment a point by a point
    
  + operator+
    Overloads the + operator to increment a point by a scalar
    
  + operator*
    Overloads the * operator to multiply a point by a scalar
   
  + operator<<
    Output a formated point to the output stream
    
  + operator>>
    Read the points x and y cordinates from the input stream
    
  + operator+
    Overloads the + operator to add a scalar to a point
    
  + operator*
    Overloads the * operator to get a point op times larger than pt
    
    Hours spent on this assignment: 4

  Specific portions that gave you the most trouble: Nothing really gave me any
    issues. It just took a bit of time to implement the 22 total functions. 
    Though it didnt help my time that I was watching tv while doing the coding.
**************************************************************************/

#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

  const double PI = 3.1415926535897;  //!< value of pi
  const double EPSILON = 0.00001;     //!< value to check for non negative zero

  //////////////////////////////////////////////////////////////////////////////
  // private member functions 
  /***********************************************************************/
  /*!
   \brief
    Translates an angle from degrees to radians
        
  \param degrees
    Angle in degrees

  \return 
    Angle in radians
  */
  /***********************************************************************/
  double Point::DegreesToRadians(double degrees) const
  {
    return (degrees * PI / 180.0);
  }

  /***********************************************************************/
  /*!
   \brief
    Translates an angle from radians to degrees
        
  \param radians
    Angle in radians

  \return 
    Angle in degrees
  */
  /***********************************************************************/
  double Point::RadiansToDegrees(double radians) const
  {
    return (radians * 180.0 / PI);
  }


  //////////////////////////////////////////////////////////////////////////////
  // 16 public member functions (2 constructors, 14 operators) 

  /***********************************************************************/
  /*!
   \brief
    Default constructor for a Point
  */
  /***********************************************************************/
  Point::Point()
  {
      // Set the x and y cordinates
    x_ = 0;
    y_ = 0;
  }

  /***********************************************************************/
  /*!
   \brief
    Constructor for a point taking in its cordinates
        
  \param x
    X cordinate for the point

  \param y
    Y cordinate for the point
  */
  /***********************************************************************/
  Point::Point(const double& x, const double& y)
  {
      // Set the x and y cordinates
    x_ = x;
    y_ = y;
  }

  /***********************************************************************/
  /*!
   \brief
    Overloads the % operator to rotate the point by the passed in angle
        
  \param degrees
    Angle in degrees

  \return 
    A point rotated around the origin by the angle
  */
  /***********************************************************************/
  Point Point::operator%(const double& degrees)
  {
    Point holder;                             // A rotated point to return
    double rads = DegreesToRadians(degrees);  // convert degreen to radians
    
      //rotate the point and store the new x and y cordinates
    holder.x_ = (this->x_ * cos(rads)) + (this->y_ * -sin(rads));
    holder.y_ = (this->x_ * sin(rads)) + (this->y_ * cos(rads));
    
      // If value is between -EPSILON and +EPSILON, make it 0.0
    if (holder.x_ > -EPSILON && holder.x_ < EPSILON)
    {
      holder.x_ = 0.0;
    }
    
      // If value is between -EPSILON and +EPSILON, make it 0.0
    if (holder.y_ > -EPSILON && holder.y_ < EPSILON)
    {
      holder.y_ = 0.0;
    }
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the - operator to get the difference between the points
        
  \param pt
    Point to compare distance to

  \return 
    Distance between the two points
  */
  /***********************************************************************/
  double Point::operator-(const Point& pt) const
  {
      // get the square of the difference between the points
    double x = (pt.x_ - this->x_) * (pt.x_ - this->x_);
    double y = (pt.y_ - this->y_) * (pt.y_ - this->y_);
    
      // Return the square root of the difference of the points
    return sqrt(x + y);
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the ^ operator to get the midpoint between two points
        
  \param pt
    Point to compare distance to

  \return 
    Midpoint between the two points
  */
  /***********************************************************************/
  Point Point::operator^( const Point& pt) const
  {
    Point holder;  //  The midpoint between the two points

    holder.x_ = (this->x_ + pt.x_) / 2;  // Figure out the middle x cordinate
    holder.y_ = (this->y_ + pt.y_) / 2;  // Figure out the middle y cordinate
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the += operator to increment a apoint by a point
        
  \param pt
    Point to increment the point by

  \return 
    A point incremented by the other point
  */
  /***********************************************************************/
  Point& Point::operator+=(const Point& pt)
  {
      // increment the x and y coordinate
    this->x_ += pt.x_;
    this->y_ += pt.y_;
    
    return *this;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the += operator to increment a apoint by a scalar
        
  \param op
    Scalar to increment the point by

  \return 
    A point incremented by the scalar
  */
  /***********************************************************************/
  Point& Point::operator+=(const double& op)
  {
      // Increment the x and y values
    this->x_ += op;
    this->y_ += op;
    
    return *this;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the - operator to subtract a scalar from a point
        
  \param op
    Scalar to decrement the point by

  \return 
    A point decremented by the scalar
  */
  /***********************************************************************/
  Point Point::operator-(const double& op) const
  {
    Point holder;  // Point with subtracted value
    
      //  Store the decremented x and y values
    holder.x_ = this->x_ - op;
    holder.y_ = this->y_ - op;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
  \brief
    Overloads the ++ increase the x and y cordinates by 1

  \return 
    A point 1 more than before
  */
  /***********************************************************************/
  Point& Point::operator++()
  {
      // Increment the values by 1
    this->x_++;
    this->y_++;
    
    return *this;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the ++ increase the x and y cordinates by 1

  \return 
    A point 1 more than before
  */
  /***********************************************************************/
  Point Point::operator++(int)
  {
    Point holder(this->x_, this->y_);  // A new point at the old point values
    
      // Increment the x and y values
    this->x_++;
    this->y_++;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the -- decrease the x and y cordinates by 1

  \return 
    A point 1 less than before
  */
  /***********************************************************************/
  Point& Point::operator--()
  {
      // Decrement the x and y values
    this->x_--;
    this->y_--;
    
    return *this;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the -- decrease the x and y cordinates by 1

  \return 
    A point 1 less than before
  */
  /***********************************************************************/
  Point Point::operator--(int)
  {
    Point holder(this->x_, this->y_);  // A new point at the old point values
    
     // Decrement the x and y values
    this->x_--;
    this->y_--;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the - operator to get negative of the point
        
  \return 
    Negative version of the point
  */
  /***********************************************************************/
  Point Point::operator-() const
  {
    Point holder;  // A point with the negative x and y values
    
      // Get the negative x and y values
    holder.x_ = this->x_ * -1;
    holder.y_ = this->y_ * -1;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the + operator to increment a point by a point
        
  \param pt
    Point to increase the point by

  \return 
    The sum of two points
  */
  /***********************************************************************/
  Point Point::operator+(const Point& pt) const
  {
    Point holder;  // A point incremented by another point
    
      // Get the x and y value sums
    holder.x_ = this->x_ + pt.x_;
    holder.y_ = this->y_ + pt.y_;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the + operator to increment a point by a scalar
        
  \param op
    scalar to increase the point by

  \return 
    Point increased by the given scalar
  */
  /***********************************************************************/
  Point Point::operator+(const double& op) const
  {
    Point holder;  // A point incremented by a scalar
    
      // Get the x and y value incremented by the scalar
    holder.x_ = this->x_ + op;
    holder.y_ = this->y_ + op;
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the * operator to multiply a point by a scalar
        
  \param op
    Scalar to multiply the point by

  \return 
    Point multiplied by the given scalar
  */
  /***********************************************************************/
  Point Point::operator*(const double& op) const
  {
    Point holder;  //  A new point multiplied by a scalar
    
      // Get the scalar multiple values of x and y
    holder.x_ = this->x_ * op;
    holder.y_ = this->y_ * op;
    
    return holder;
  }

  //////////////////////////////////////////////////////////////////////////////
  // 2 friend functions (operators)

  /***********************************************************************/
  /*!
   \brief
    Output a formated point to the output stream
        
  \param os
    The stream to output to
    
  \param pt
    Point to output to the stream

  \return 
    The output stream withthe o=point given to it
  */
  /***********************************************************************/
  std::ostream& operator<<(std::ostream& os, const Point& pt)
  {
    os << "(" << pt.x_ << ", " << pt.y_ << ")";
    return os;
  }

  /***********************************************************************/
  /*!
   \brief
    Read the points x and y cordinates from the input stream
        
  \param is
    The Stream to get input from
    
  \param pt
    Point input to

  \return 
    The input stream
  */
  /***********************************************************************/
  std::istream& operator>> (std::istream& is, Point& pt)
  {
    is >> pt.x_ >> pt.y_;
    return is;
  }


  //////////////////////////////////////////////////////////////////////////////
  // 2 non-members, non-friends (operators)

  /***********************************************************************/
  /*!
   \brief
    Overloads the + operator to add a scalar to a point
  
  \param op
    Scalar to add to a point

  \param pt
    Point to add a scalar too
    
  \return 
    A point incremented by a scalar
  */
  /***********************************************************************/
  Point operator+(const double& op, const Point& pt)
  {
    return pt + op;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Overloads the * operator to get a point op times larger than pt
        
  \param op
    Value to multiply a point by
    
  \param pt
    Point to multiply by a given skalar

  \return 
    A point that has been multiplied by the passed in scalar
  */
  /***********************************************************************/
  Point operator*(const double& op, const Point& pt)
  {
    return pt * op;
  }


} // namespace CS170



