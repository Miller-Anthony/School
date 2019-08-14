# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
#OUTDIR=gnu/
ERASE=rm
OBJECTS=Point.o driver-sample.o
EXE=points

# Targets ========================================

Points : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS)

Point.o : Point.cpp
	$(CC) -o Point.o $(CFLAGS) Point.cpp
	
driver-sample.o : driver-sample.cpp
	$(CC) -o driver-sample.o $(CFLAGS) driver-sample.cpp
  
driver-big.o : driver-big.cpp
	$(CC) -o driver-big.o $(CFLAGS) driver-big.cpp

clean :
	$(ERASE) $(EXE) $(OBJECTS)
  
memory :
	drmemory -batch -pause_at_error -no_summary -- $(EXE).exe
  
run :
	$(EXE).exe > myout.txt
  
tablen :
	tablen Point.cpp
  
diff :
	diff --strip-trailing-cr myout.txt output2.txt
  
big :
	g++ -Wall -Wextra -Werror -Wconversion -O -ansi -pedantic -g -o warboats driver-big.cpp Ocean.cpp PRNG.cpp

