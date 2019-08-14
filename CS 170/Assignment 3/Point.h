/*!*************************************************************************
\file       Point.h
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Assignment #3
\date       03/13/2019
**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // istream, ostream

namespace CS170
{
  class Point
  {
    public:
        // Constructors (2)
      Point();
      Point(const double& x, const double& y);
      
        // Overloaded operators (14 member functions)
      Point operator%(const double& degree);
      double operator-(const Point& pt) const;
      Point operator^( const Point& pt) const;
      Point& operator+=(const Point& pt);
      Point& operator+=(const double& op);
      Point operator-(const double& op) const;
      Point& operator++();
      Point operator++(int);
      Point& operator--();
      Point operator--(int);
      Point operator-() const;
      Point operator+(const Point& pt) const;
      Point operator+(const double& op) const;
      Point operator*(const double& op) const;
      
      
        // Overloaded operators (2 friend functions)
      friend std::ostream& operator<<(std::ostream& os, const Point& pt);
      friend std::istream& operator>> (std::istream& is, Point& pt);
      
    private:
      double x_; //!< The x-coordinate of a Point
      double y_; //!< The y-coordinate of a Point

        // Helper functions
      double DegreesToRadians(double degrees) const;
      double RadiansToDegrees(double radians) const;
  };
  
    // Overloaded operators (2 non-member, non-friend functions)
    Point operator+(const double& op, const Point& pt);
    Point operator*(const double& op, const Point& pt);
    
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
