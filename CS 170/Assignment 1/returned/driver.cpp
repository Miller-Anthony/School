#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib> // atoi

#include "WarBoats.h"
#include "PRNG.h"

void PrintShotResult(const CS170::WarBoats::ShotResult &sr)
{
  const char *strings[] = {"HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL"};
  std::cout << strings[static_cast<int>(sr)] << std::endl;
  //if (sr == CS170::WarBoats::srSUNK)
  //  std::cout << "*************************************************\n";
}

void PrintStats(const CS170::WarBoats::ShotStats &stats)
{
  std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
  std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
  std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
  std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void TakeAShot(CS170::WarBoats::Ocean &ocean, const CS170::WarBoats::Point& pt)
{
  CS170::WarBoats::ShotResult sr;
  std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
  sr = CS170::WarBoats::TakeShot(ocean, pt);
  PrintShotResult(sr);
  PrintStats(GetShotStats(ocean));
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;
}

void test1(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);
  std::cout << "\n*************** test1 ***************\n";

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 12;
  CS170::WarBoats::Ocean *theOcean;
  theOcean = CS170::WarBoats::CreateOcean(num_boats, xsize, ysize);
  CS170::WarBoats::Ocean &ocean = *theOcean;

  std::cout << "The empty board" << std::endl;
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 10;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 2;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

      // Illegal placement
  boat.ID = 4;
  location.x = 5;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = CS170::WarBoats::PlaceBoat(ocean, boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;
  CS170::WarBoats::DestroyOcean(theOcean);
}

void test2(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);
  std::cout << "\n*************** test2 ***************\n";

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 8;
  CS170::WarBoats::Ocean *theOcean;
  theOcean = CS170::WarBoats::CreateOcean(num_boats, xsize, ysize);
  CS170::WarBoats::Ocean &ocean = *theOcean;

  std::cout << "The empty board" << std::endl;
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  CS170::WarBoats::DumpOcean(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Point coordinate;

    // Illegal coordinate
  coordinate.x = 10;
  coordinate.y = 5;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // MISS
  coordinate.x = 5;
  coordinate.y = 7;
  TakeAShot(ocean, coordinate);

    // DUPLICATE
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 2;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 3;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // SUNK
  coordinate.x = 4;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);
  CS170::WarBoats::DestroyOcean(theOcean);
}

void test3(void)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);
  std::cout << "\n*************** test3 ***************\n";

  int num_boats = 5;
  int xsize = 10;
  int ysize = 10;
  CS170::WarBoats::Ocean *theOcean;
  theOcean = CS170::WarBoats::CreateOcean(num_boats, xsize, ysize);
  CS170::WarBoats::Ocean &ocean = *theOcean;

  //std::cout << "The empty board" << std::endl;
  //CS170::WarBoats::DumpOcean(ocean);
  //std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #4
  boat.ID = 4;
  location.x = 3;
  location.y = 8;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

    // Boat #5
  boat.ID = 5;
  location.x = 9;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  CS170::WarBoats::PlaceBoat(ocean, boat);

  //std::cout << "The board with " << num_boats << " boats" << std::endl;
  //CS170::WarBoats::DumpOcean(ocean);
  //std::cout << std::endl;

    // Try to sink the boats with random shots
  //int shots = 0;
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      /*
      std::cout << "Shot #"
                << ++shots
                << " at coordinate "
                << coordinate.x
                << ", "
                << coordinate.y
                << "  ";
      */
      sr = CS170::WarBoats::TakeShot(ocean, coordinate);
      //PrintShotResult(sr);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

    /*
    if (sr == CS170::WarBoats::srSUNK)
    {
      PrintShotResult(sr);
      PrintStats(GetShotStats(ocean));
      CS170::WarBoats::DumpOcean(ocean);
      std::cout << std::endl;
    }
    */
  }
  //PrintShotResult(sr);
  PrintStats(GetShotStats(ocean));
  CS170::WarBoats::DumpOcean(ocean);
  CS170::WarBoats::DestroyOcean(theOcean);
}

void test_big(int num_boats, int xsize, int ysize, 
           bool show_sunk = true, bool show_all = false, bool show_end = true)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(3, 4);

  CS170::WarBoats::Ocean *theOcean;
  theOcean = CS170::WarBoats::CreateOcean(num_boats, xsize, ysize);
  CS170::WarBoats::Ocean &ocean = *theOcean;

    // Place the boats randomly in the ocean
  int boats_placed = 0;
  while (boats_placed < num_boats)
  {
    CS170::WarBoats::Boat boat;

    //boat.hits = 0;
    boat.ID = boats_placed + 1;
    CS170::WarBoats::BoatPlacement bp;
    do
    {
        // Pick a random orientation
      boat.orientation = CS170::Utils::Random(0, 1)
                                 ? CS170::WarBoats::oHORIZONTAL
                                 : CS170::WarBoats::oVERTICAL;

        // Pick a random location
      CS170::WarBoats::Point location;
      location.x = CS170::Utils::Random(0, xsize - 1);
      location.y = CS170::Utils::Random(0, ysize - 1);
      boat.position = location;

        // Place the boat
      bp = CS170::WarBoats::PlaceBoat(ocean, boat);

    }while (bp == CS170::WarBoats::bpREJECTED);

    //CS170::WarBoats::DumpOcean(ocean);
    //std::cout << std::endl;
    boats_placed++;
  }
  //std::cout << "Boats placed:\n";
  //CS170::WarBoats::DumpOcean(ocean);
  //std::cout << std::endl;

    // Try to sink the boats with random shots
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      //std::cout << "target: " << coordinate.x << ", " 
      //          << coordinate.y << std::endl;

      sr = CS170::WarBoats::TakeShot(ocean, coordinate);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

    if (show_all)
    {
      PrintShotResult(sr);
      PrintStats(GetShotStats(ocean));
      CS170::WarBoats::DumpOcean(ocean, 4, false);
      std::cout << std::endl;
    }
    else if ( (sr == CS170::WarBoats::srSUNK) && show_sunk)
    {
      PrintShotResult(sr);
      PrintStats(GetShotStats(ocean));
      CS170::WarBoats::DumpOcean(ocean, 4, false);
      std::cout << std::endl;
    }
  }

  if (show_end)
  {
    std::cout << "Final board:\n";
    PrintStats(GetShotStats(ocean));
    CS170::WarBoats::DumpOcean(ocean, 4, false);
    std::cout << std::endl;
  }

  CS170::WarBoats::DestroyOcean(theOcean);
}

void test4(void)
{
  std::cout << "\n*************** test4 ***************\n";
  test_big(50, 30, 30, false, false);
}

void test5(void)
{
  std::cout << "\n*************** test5 ***************\n";
  test_big(5, 15, 9, false, false);
}

//***********************************************************************
//***********************************************************************
//***********************************************************************

typedef void (*TestFn)(void);

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
	if (maxwait + safewait > 0)
		fn();
}

int main(int argc, char **argv)
{
	size_t test_num = 0;
	if (argc > 1)
    test_num = std::atoi(argv[1]);

	struct TimedTest
	{
		void (*test)(void);
		int maxwait;
		int safewait;
	};

	TimedTest Tests[] = {{test1,  2000, 2000},    
											 {test2,  2000, 2000},    
											 {test3,  2000, 2000},    
											 {test4,  2000, 2000},    
											 {test5,  2000, 2000},    
	                    };

	size_t num = sizeof(Tests) / sizeof(*Tests);
	if (test_num == 0)
	{
		for (size_t i = 0; i < num; i++)
			ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
	}
	else if (test_num > 0 && test_num <= num)
	{
		ExecuteTest(Tests[test_num - 1].test, Tests[test_num - 1].maxwait, Tests[test_num - 1].safewait);
	}
}
