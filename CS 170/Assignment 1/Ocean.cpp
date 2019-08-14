/******************************************************************************/
/*!
\file   Ocean.cpp
\author Anthony Miller
\par    email: Anthony.M\@digipen.edu
\par    DigiPen login: Anthony.M
\par    Course: CS170
\par    Section: A
\par    Assignment #1
\date   2/08/2019
\brief  
    This file contains the implementation of the following functions for the 
    WarBoats assignment.
      
    Functions include:
    
       + CreateOcean
          Makes an ocean object to hold game information
         
       + DestroyOcean
          Free all the memory allocated for the ocean object
         
       + TakeShot
          Attempt to hit a boat on the ocean grid
         
       + PlaceBoat
          Add a boat to the ocean grid
         
       + GetShotStats
          Get the current stats of the game
          
       + DumpOcean
          Print out all the information about the current game
    
  Hours spent on this assignment: 8

  Specific portions that gave you the most trouble: I spent about two hours
    trying to figure out what seemed to be a memory bug. A bug where after
    finishing the program and trying to destroy the ocean it would just stop
    and crash after a few seconds. I tried changing the DestroyOcean function 
    as well as many other things. But then what ended up fixing it was switching
    to a different computer, where the bug was not reproducable.
*/
/******************************************************************************/


#include "WarBoats.h"
#include "Ocean.h"
#include <iostream> // cout, endl
#include <iomanip>  // setw

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  //!< Length of a boat
    const int HIT_OFFSET = 100; //!< Add this to the boat ID

    /**************************************************************************/
    /*!
      \brief
        Creates an ocean of specified dimensions for the number of 
        boats to be placed in it.
      
      \param num_boats
        The number of boats to be put in the ocean.
      
      \param x_quadrants
        The number of columns to be generated.
      
      \param y_quadrants
        The number of rows to be generated.
        
      \return
        Ocean object to store game data in
    */
    /**************************************************************************/
    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
    {
        /* The ocean to be populated and returned */
      struct Ocean *holder = new Ocean;
      
        /* Create a grid to store boat locations */
      int *gridHolder = new int[y_quadrants * x_quadrants];
      
        /* Attach set all the grid values to 0 */
      holder->grid = gridHolder;
      for(int i = 0; i < y_quadrants; i++)
      {
        for (int j = 0; j < x_quadrants; j++)
        {
          gridHolder[i * y_quadrants + j] = 0;
        }
      }
           
        /* Create the boats to place in the grid */
      struct Boat *boatHolder = new Boat[num_boats];
      
        /* Attach boats to the ocean struct */
      holder->boats = boatHolder;        
           
        /* for each boat, set its stats to zero */
      for(int i = 0; i < num_boats; i++)
      {
        holder->boats[i].hits = 0;
        holder->boats[i].ID = 0;
        holder->boats[i].orientation = oHORIZONTAL;
        holder->boats[i].position.x = 0;
        holder->boats[i].position.y = 0;
       // }
      }
         
        /* Set the oceans stat values to 0 */
      holder->stats.hits = 0;
      holder->stats.misses = 0;
      holder->stats.duplicates = 0;
      holder->stats.sunk = 0;
        
        /* Set the remaining ocean fields to the passed in values */
      holder->num_boats = num_boats;
      holder->x_quadrants = x_quadrants;
      holder->y_quadrants = y_quadrants;
      
      return holder;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Destroys a passed in ocean by de-allocatin the memory.
      
      \param theOcean
        The Ocean to delete
    */
    /**************************************************************************/
    void DestroyOcean(Ocean *theOcean)
    {
        /* Create a pointer to the grid, then delete it */
      int *holdInt = theOcean->grid;
      delete[] holdInt;
      
        /* Create a pointer to the boats, then delete it */
      struct Boat *boatHolder = theOcean->boats;
      delete[] boatHolder;

      delete theOcean;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Attempt to hit a boat in the ocean grid at the given coordinates.
             
      \param ocean
        The Ocean containing what is being shot at
      
      \param coordinate
        The coordinates to take a shot at
        
      \return
        Hit, Miss, Sunk, Duplicate, or Illegal depending on the 
        result of the shot.
      */
    /**************************************************************************/
    ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
    {
        /* Shot is out of the ocean (grid) */
      if(coordinate.x < 0 ||
         coordinate.y < 0 ||
         coordinate.x > ocean.x_quadrants ||
         coordinate.y > ocean.y_quadrants)
      {
        return srILLEGAL;
      }

        /* Store the value at the sot location */
      int value = ocean.grid[coordinate.y * ocean.x_quadrants + coordinate.x];

        /* If the location was already targeted */
      if (value == dtBLOWNUP || value > HIT_OFFSET)
      {
        ocean.stats.duplicates++;
        return srDUPLICATE;
      }
      
        /* if there is no ship and has not been targeted */
      else if (value == dtOK)
      {
        ocean.stats.misses++;
        ocean.grid[coordinate.y * ocean.x_quadrants + coordinate.x] = dtBLOWNUP;
        return srMISS;
      }

        /* set the targeted location to struck and increment the hit count */
      ocean.stats.hits++;
      ocean.boats[value - 1].hits++;
      ocean.grid[coordinate.y * ocean.x_quadrants + coordinate.x] += HIT_OFFSET;
      
        /* if the boat was sunk, increment the sunk boat count */
      if(ocean.boats[value - 1].hits >= BOAT_LENGTH)
      {
        ocean.stats.sunk++;
        return srSUNK;
      }
      
      return srHIT;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Try to place a boat in the ocean grid. 
      
      \param ocean
        The Ocean to add a boat to
      
      \param boat
        The boat to try to add to the ocean grid.
        
      \return
        0 if accepted or 1 if rejected.
    */
    /**************************************************************************/
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
    {
        /* trying to place the boat outside the ocean */
      if(boat.position.x < 0 || boat.position.y < 0 ||
        (boat.position.x + 4 > ocean.x_quadrants && 
         boat.orientation == oHORIZONTAL) ||
        (boat.position.y + 4 > ocean.y_quadrants && 
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
          for (int i = 0; i <= BOAT_LENGTH; i++)
          {
              /* look to see if ocean spot is occupied */
            if(ocean.grid[boat.position.y * ocean.x_quadrants
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
          for (int i = 0; i <= BOAT_LENGTH; i++)
          {
              /* look to see if ocean spot is occupied */
            if(ocean.grid[(boat.position.y + i) * ocean.x_quadrants 
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
            ocean.grid[boat.position.y * ocean.x_quadrants 
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
            ocean.grid[(boat.position.y + i) * ocean.x_quadrants
                       + boat.position.x] = boat.ID;
          }
          break;
        }
      } 

        /* Set data for coresponding boat stored in ocean to passed in boat */
      ocean.boats[boat.ID - 1].ID = boat.ID;
      ocean.boats[boat.ID - 1].orientation = boat.orientation;
      ocean.boats[boat.ID - 1].position = boat.position;
      
      return bpACCEPTED;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Get the current statistics of the game.
      
      \param ocean
        The Ocean to get stats from
        
      \return
        Current stats of the game
    */
    /**************************************************************************/
    ShotStats GetShotStats(const Ocean &ocean)
    {
      return ocean.stats;
    }

     
    /**************************************************************************/
    /*!
      \brief
        Prints the grid (ocean) to the screen.
      
      \param ocean
        The Ocean to print
      
      \param field_width
        How much space each position takes when printed.
      
      \param extraline
        If true, an extra line is printed after each row. If false, no extra
        line is printed.
        
      \param showboats
        If true, the boats are shown in the output. (Debugging feature)
    */
    /**************************************************************************/
    void DumpOcean(const CS170::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats)
    {
        // For each row
      for (int y = 0; y < ocean.y_quadrants; y++)
      {
          // For each column
        for (int x = 0; x < ocean.x_quadrants; x++)
        {
            // Get value at x/y position
          int value = ocean.grid[y * ocean.x_quadrants + x];
    
            // Is it a boat that we need to keep hidden?
          if ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) )
            value = 0;
    
          std::cout << std::setw(field_width) << value;
        }
        std::cout << std::endl;
        if (extraline)
          std::cout << std::endl;
      }
    }

  } // namespace WarBoats
} // namespace CS170
