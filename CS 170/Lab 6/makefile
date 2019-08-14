# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
#OUTDIR=gnu/
ERASE=rm
OBJECTS=List.o driver.o
EXE=gnu

# Targets ========================================

gnu : List.o driver.o
	$(CC) -o $(EXE) List.o driver.o

List.o : List.cpp
	$(CC) -o List.o $(CFLAGS) List.cpp
	
driver.o : driver.cpp
	$(CC) -o driver.o $(CFLAGS) driver.cpp

clean :
	$(ERASE) $(EXE) List.o driver.o
  
memory :
	drmemory -batch -no_summary -- $(EXE).exe
  
run :
	$(EXE) >> myout.txt
  
tablen :
	tablen List.cpp
  
diff :
	diff --strip-trailing-cr myout.txt output-all.txt

