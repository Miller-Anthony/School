/******************************************************************************/
/*!
\file   Ocean.cpp
\author Anthony Miller
\par    email: Anthony.M\@digipen.edu
\par    DigiPen login: Anthony.M
\par    Course: CS170
\par    Section: A
\par    Assignment #2
\date   2/28/2019
\brief  
    This file contains the implementation of the following functions for the 
    WarBoats assignment.
      
    Functions include:
    
       + Ocean
          Makes an ocean object to hold game information
         
       + ~Ocean
          Free all the memory allocated for the ocean object
         
       + TakeShot
          Attempt to hit a boat on the ocean grid
         
       + PlaceBoat
          Add a boat to the ocean grid
         
       + GetShotStats
          Get the current stats of the game
          
       + GetGrid
          Get the current grid state of the object
          
       + GetDimensions
          Get dimensions of the object's grid
          
    
  Hours spent on this assignment: 2

  Specific portions that gave you the most trouble: Huntind down memory bugs 
          using drmemory is not easy, becasue all it tells you is what 
          function the issue was in. Makes me want to instal linux just to be
          able to use Valgrind. (still nervous there may be memory bugs that
          Valgrind will find when drmemory wouldnt)
*/
/******************************************************************************/

#include "WarBoats.h" //Orientation, ShotResult, DamageType, BoatPlacement, 
                      //Point, Boat, ShotStats
#include "Ocean.h"

namespace CS170
{

  namespace WarBoats
  {
    /**************************************************************************/
    /*!
      \brief
        Constructor for the 
      
      \param num_boats
        The number of boats to be put in the ocean.
      
      \param x_quadrants
        The number of columns to be generated.
      
      \param y_quadrants
        The number of rows to be generated.
    */
    /**************************************************************************/
    Ocean::Ocean(int num_boats, int x_quadrants, int y_quadrants)
    {     
        /* Create a grid to store boat locations */
      int *gridHolder = new int[y_quadrants * x_quadrants];
      
        /* Attach set all the grid values to 0 */
      grid_ = gridHolder;
      for(int i = 0; i < y_quadrants; i++)
      {
        for (int j = 0; j < x_quadrants; j++)
        {
          grid_[i * x_quadrants + j] = 0;
        }
      }

        /* Create the boats to place in the grid */
      struct Boat *boatHolder = new Boat[num_boats];
      
        /* Attach boats to the ocean struct */
      boats_ = boatHolder;
      
        /* for each boat, set its stats to zero */
      for(int i = 0; i < num_boats; i++)
      {
        boats_[i].hits = 0;
        boats_[i].ID = 0;
        boats_[i].orientation = oHORIZONTAL;
        boats_[i].position.x = 0;
        boats_[i].position.y = 0;
      }
      
        /* Set the oceans stat values to 0 */
      stats_.hits = 0;
      stats_.misses = 0;
      stats_.duplicates = 0;
      stats_.sunk = 0;
        
        /* Set the remaining ocean fields to the passed in values */
      num_boats_ = num_boats;
      x_quadrants_ = x_quadrants;
      y_quadrants_ = y_quadrants;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Destrestructor for the Ocean.
    */
    /**************************************************************************/
    Ocean::~Ocean()
    {
        /* Create a pointer to the grid, then delete it */
      delete[] grid_; //delete the grid
      
        /* Create a pointer to the boats, then delete it */
      delete[] boats_; //delete the boats
    }
    
    /**************************************************************************/
    /*!
      \brief
        Attempt to hit a boat in the ocean grid at the given coordinates.
      
      \param coordinate
        The coordinates to take a shot at
        
      \return
        Hit, Miss, Sunk, Duplicate, or Illegal depending on the 
        result of the shot.
      */
    /**************************************************************************/
    ShotResult Ocean::TakeShot(const Point &coordinate)
    {
        /* Shot is out of the ocean (grid) */
      if(coordinate.x < 0 ||
         coordinate.y < 0 ||
         coordinate.x > x_quadrants_ ||
         coordinate.y > y_quadrants_)
      {
        return srILLEGAL;
      }

        /* Store the value at the sot location */
      int value = grid_[coordinate.y * x_quadrants_ + coordinate.x];

        /* If the location was already targeted */
      if (value == dtBLOWNUP || value > HIT_OFFSET)
      {
        stats_.duplicates++;
        return srDUPLICATE;
      }
      
        /* if there is no ship and has not been targeted */
      else if (value == dtOK)
      {
        stats_.misses++;
        grid_[coordinate.y * x_quadrants_ + coordinate.x] = dtBLOWNUP;
        return srMISS;
      }

        /* set the targeted location to struck and increment the hit count */
      stats_.hits++;
      boats_[value - 1].hits++;
      grid_[coordinate.y * x_quadrants_ + coordinate.x] += HIT_OFFSET;
      
        /* if the boat was sunk, increment the sunk boat count */
      if(boats_[value - 1].hits >= BOAT_LENGTH)
      {
        stats_.sunk++;
        return srSUNK;
      }
      
      return srHIT;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Try to place a boat in the ocean grid. 
      
      \param boat
        The boat to try to add to the ocean grid.
        
      \return
        0 if accepted or 1 if rejected.
    */
    /**************************************************************************/
    BoatPlacement Ocean::PlaceBoat(const Boat& boat)
    {
        /* trying to place the boat outside the ocean */
      if(boat.position.x < 0 || boat.position.y < 0 ||
         boat.position.x >= x_quadrants_ || boat.position.y >= y_quadrants_ ||
        (boat.position.x + BOAT_LENGTH >= x_quadrants_ && 
         boat.orientation == oHORIZONTAL) ||
        (boat.position.y + BOAT_LENGTH >= y_quadrants_ && 
         boat.orientation == oVERTICAL))
      {
        return bpREJECTED;
      }
      
        /* Check the grid based on the orientation of the boat */
      switch (boat.orientation)
      {
        case oHORIZONTAL:
        {
            /* for the length of the boat */
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
              /* look to see if ocean spot is occupied */
            if(grid_[boat.position.y * x_quadrants_
               + boat.position.x + i] != 0)
            {
              return bpREJECTED;
            }
          }
          break;
        }
        case oVERTICAL:
        {
            /* for the length of the boat */
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
              /* look to see if ocean spot is occupied */
            if(grid_[(boat.position.y + i) * x_quadrants_
               + boat.position.x] != 0)
            {
              return bpREJECTED;
            }
          }
          break;
        }
        default:
        {
          return bpREJECTED;
        }
      }      
      
        /* Place the boat in the ocean based on its orientation */
      switch (boat.orientation)
      {
        case oHORIZONTAL:
        {
            /* for the length of the boat */
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
              /* set appropriate grid value to boat id to track the boat */
            grid_[boat.position.y * x_quadrants_ 
                       + boat.position.x + i] = boat.ID;
          }
          break;
        }
        case oVERTICAL:
        {
            /* for the length of the boat */
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
              /* set appropriate grid value to boat id to track the boat */
            grid_[(boat.position.y + i) * x_quadrants_
                       + boat.position.x] = boat.ID;
          }
          break;
        }
      } 

        /* Set data for coresponding boat stored in ocean to passed in boat */
      boats_[boat.ID - 1].ID = boat.ID;
      boats_[boat.ID - 1].orientation = boat.orientation;
      boats_[boat.ID - 1].position = boat.position;
      
      return bpACCEPTED;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Get the current statistics of the game.
        
      \return
        Current stats of the game
    */
    /**************************************************************************/
    ShotStats Ocean::GetShotStats() const
    {
      return stats_;
    }

    /**************************************************************************/
    /*!
      \brief
        Get the current grid state of the object.
      
      \return
        The current grid state
    */
    /**************************************************************************/
    const int *Ocean::GetGrid() const
    {
      return grid_;
    }
  
    /**************************************************************************/
    /*!
      \brief
        Get dimensions of the object's grid
      
      \return
        A point representing the dimensions of the grid
    */
    /**************************************************************************/
    Point Ocean::GetDimensions() const
    {
      Point pt = {x_quadrants_, y_quadrants_};
      return pt;
    }

  } // namespace WarBoats

} // namespace CS170

