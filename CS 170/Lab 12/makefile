# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
#OUTDIR=gnu/
ERASE=rm
OBJECTS=Vector.o driver.o PRNG.o
EXE=gnu

# Targets ========================================

gnu : Vector.o driver.o PRNG.o
	$(CC) -o $(EXE) $(OBJECTS)

Vector.o : Vector.cpp
	$(CC) -o Vector.o $(CFLAGS) Vector.cpp
	
driver.o : driver.cpp
	$(CC) -o driver.o $(CFLAGS) driver.cpp

PRNG.o : PRNG.cpp
	$(CC) -o PRNG.o $(CFLAGS) PRNG.cpp

clean :
	$(ERASE) $(EXE) $(OBJECTS)
  
memory :
	drmemory -batch -no_summary -- $(EXE).exe
  
run :
	gnu.exe > myout.txt
  
tablen :
	tablen Vector.cpp
  
diff :
	diff --strip-trailing-cr myout.txt output-all.txt

