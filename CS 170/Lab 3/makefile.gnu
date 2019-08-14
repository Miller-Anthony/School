# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion -c
OUTDIR=gnu/
ERASE=rm
OBJECTS=fibonacci.o main.o
EXE=fib

# Targets ========================================

fib : fibonacci.o main.o
	$(CC) -o $(OUTDIR)$(EXE) $(OUTDIR)fibonacci.o $(OUTDIR)main.o

fibonacci.o : fibonacci.cpp
	$(CC) -o $(OUTDIR)fibonacci.o $(CFLAGS) fibonacci.cpp
	
main.o : main.cpp
	$(CC) -o $(OUTDIR)main.o $(CFLAGS) main.cpp

clean :
	$(ERASE) $(OUTDIR)$(EXE) $(OUTDIR)fibonacci.o $(OUTDIR)main.o

