/******************************************************************************/
/*!
\file   Ocean.h
\author Anthony Miller
\par    email: Anthony.M\@digipen.edu
\par    DigiPen login: Anthony.M
\par    Course: CS170
\par    Section: A
\par    Assignment #2
\date   2/28/2019
\brief  
    This file contains the Ociean class for use with the Warboats game.
      
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

#include "WarBoats.h" //ShotResult, BoatPlacement, Point, boat, ShotStats 

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  //!< Length of a boat
    const int HIT_OFFSET = 100; //!< Add this to the boat ID

    /*!
      This class represents the "board" in WarBoats
    */
    class Ocean
    {
      public:
        
        // Public methods...
        Ocean(int num_boats, int x_quadrants, int y_quadrants);
        ~Ocean();
        ShotResult TakeShot(const Point &coordinate);
        BoatPlacement PlaceBoat(const Boat& boat);
        ShotStats GetShotStats() const;
          // Provided
        const int *GetGrid(void) const;
        Point GetDimensions(void) const;

      private:
        int *grid_;        //!< The 2D ocean
        int x_quadrants_;  //!< Ocean size along x-axis
        int y_quadrants_;  //!< Ocean size along y-axis
        
        // Other private members...
        ShotStats stats_;   //!< Status of the attack
        int num_boats_;     //!< Number of boats in the ocean
        Boat *boats_;       //!< The dynamic array of boats
    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
