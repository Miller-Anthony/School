# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
#OUTDIR=gnu/
ERASE=rm
OBJECTS=Vector.o driver.o
EXE=gnu

# Targets ========================================

gnu : Vector.o driver.o
	$(CC) -o $(EXE) Vector.o driver.o

Vector.o : Vector.cpp
	$(CC) -o Vector.o $(CFLAGS) Vector.cpp
	
driver.o : driver.cpp
	$(CC) -o driver.o $(CFLAGS) driver.cpp

clean :
	$(ERASE) $(EXE) Vector.o driver.o
  
memory :
	drmemory -batch -no_summary -- $(EXE).exe
  
run :
	gnu.exe > myout.txt
  
tablen :
	tablen Vector.cpp
  
diff :
	diff --strip-trailing-cr myout.txt output-all.txt

