# Macros ========================================

CC=
CFLAGS=

ERASE=rm
OBJECTS=hw-gnu.o
EXE=hw-gnu

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS)

hw-gnu.o : hw.cpp
	$(CC) -o hw-gnu.o $(CFLAGS) hw.cpp
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)
