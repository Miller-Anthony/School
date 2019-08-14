/******************************************************************************
filename    Utils.h
author      Brayan
DP email    brayan.lopez@digipen.edu
course      GAM150

Brief Description:
This file includes the public interface of utility functions

******************************************************************************/
#pragma once

#include "targetver.h" /* required by Windows */

//returns a random int in range [min, max]
int RandomRange(int min, int max);
//returns a random float in range [min, max]
float RandomRangeFloat(float rangeMin, float rangeMax);
//squares a float
float Square(float num);
//Gets an integer from a file (max integer length is 16 digits)
int IntFromFile(const char * filename);