/**************************************************************************
filename    sieve.h
author      Anthony Miller
DP email    anthony.m@digipen.edu
course      CS120
section     B
assignment  Lab Week #7
due date    10/24/2018

Brief Description:
  Header file for sieve.c
**************************************************************************/
#define FALSE 0
#define TRUE  1

void sieve(int array[], int size);
int twin_primes(const int primes[], int size);
double brun_constant(const int primes[], int size);