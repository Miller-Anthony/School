#!/bin/bash

basename `pwd`  > build.txt
echo >> build.txt
echo >> build.txt

make clean 2> /dev/null > /dev/null

#GNU
echo >> build.txt
echo g++: >> build.txt
echo ---------------------------- >> build.txt
make GCC=g++ -j4 2>> build.txt > /dev/null

rm *.o 2> /dev/null

#GNU 32-bit
#echo >> build.txt
#echo g++: >> build.txt
#echo ---------------------------- >> build.txt
# Dr. Memory build
#make GCC=g++ LFLAGS=-m32 CFLAGS="-m32 -g -fno-inline -fno-omit-frame-pointer" EXE=driver32.exe -j4 > /dev/null

echo >> build.txt

rm *.o 2> /dev/null
