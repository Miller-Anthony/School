# Macros ========================================

CC=g++
CFLAGS=-g -O -Wall -ansi -pedantic -Wextra -Wconversion -Werror
LFLAGS=
ERASE=rm
MAINFILE=Ocean
OBJECTS=driver.o $(MAINFILE).o PRNG.o
EXE=driver.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LFLAGS)

driver.o : driver.cpp WarBoats.h PRNG.h
	$(CC) -c -o driver.o $(CFLAGS) driver.cpp

$(MAINFILE).o : $(MAINFILE).cpp $(MAINFILE).h WarBoats.h
	$(CC) -c -o $(MAINFILE).o $(CFLAGS) $(MAINFILE).cpp

PRNG.o : PRNG.cpp PRNG.h
	$(CC) -c -o PRNG.o $(CFLAGS) PRNG.cpp

all : 
	$(MAKE) $(EXE)

rebuild : 
	$(MAKE) clean
	$(MAKE)

clean :
	$(ERASE) $(EXE) $(OBJECTS)
