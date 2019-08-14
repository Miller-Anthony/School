////////////////////////////////////////////////////////////////////////////////
#ifndef WARBOATS_H
#define WARBOATS_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace WarBoats
  {
    struct Ocean; //!< Forward declaration for the Ocean 

    enum Orientation { oHORIZONTAL, oVERTICAL };
    enum ShotResult { srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL };
    enum DamageType { dtOK = 0, dtBLOWNUP = -1 };
    enum BoatPlacement { bpACCEPTED, bpREJECTED };

      //! A coordinate in the Ocean
    struct Point
    {
      int x; //!< x-coordinate (column)
      int y; //!< y-coordinate (row)
    };

      //! A boat in the Ocean
    struct Boat
    {
      int hits;                 //!< Hits taken so far
      int ID;                   //!< Unique ID 
      Orientation orientation;  //!< Horizontal/Vertical
      Point position;           //!< x-y coordinate (left-top)
    };

      //! Statistics of the "game"
    struct ShotStats
    {
      int hits;       //!< The number of boat hits
      int misses;     //!< The number of boat misses
      int duplicates; //!< The number of duplicate (misses/hits)
      int sunk;       //!< The number of boats sunk
    };

      // The interface
    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants);
    void DestroyOcean(Ocean *theOcean);
    ShotResult TakeShot(Ocean &ocean, const Point &coordinate);
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat);
    ShotStats GetShotStats(const Ocean &ocean);

      // Provided
    void DumpOcean(const Ocean &ocean, int width = 4, bool extraline = false, 
                   bool showboats = true);

  } // namespace WarBoats

} // namespace CS170

#endif // WARBOATS_H
////////////////////////////////////////////////////////////////////////////////
