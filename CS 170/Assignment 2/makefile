# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
#OUTDIR=gnu/
ERASE=rm
OBJECTS=Ocean.o driver-big.o PRNG.o
EXE=warboats

# Targets ========================================

WarShips : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS)

Ocean.o : Ocean.cpp
	$(CC) -o Ocean.o $(CFLAGS) Ocean.cpp
	
driver-sample.o : driver-sample.cpp
	$(CC) -o driver-sample.o $(CFLAGS) driver-sample.cpp
  
driver-big.o : driver-big.cpp
	$(CC) -o driver-big.o $(CFLAGS) driver-big.cpp
  
PRNG.o : PRNG.cpp
	$(CC) -o PRNG.o $(CFLAGS) PRNG.cpp

clean :
	$(ERASE) $(EXE) $(OBJECTS)
  
memory :
	drmemory -batch -pause_at_error -no_summary -- $(EXE).exe
  
run :
	$(EXE) >> myout.txt
  
tablen :
	tablen List.cpp
  
diff :
	diff --strip-trailing-cr myout.txt output2.txt
  
big :
	g++ -Wall -Wextra -Werror -Wconversion -O -ansi -pedantic -g -o warboats driver-big.cpp Ocean.cpp PRNG.cpp

