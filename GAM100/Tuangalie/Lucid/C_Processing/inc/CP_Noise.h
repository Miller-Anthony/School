//---------------------------------------------------------
// file:	CP_Noise.h
// author:	Justin Chambers
// brief:	Header for all noise helper functions
//
// DO NOT INCLUDE THIS HEADER IN YOUR PROJECTS DIRECTLY
// SEE: C_Processing.h
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include "CP_Export.h"

// noise - returns a value in the range [0, 1.0] based on three dimensional input values
DLL_EXPORT double noise(double x, double y, double z);

// Sets the seed value for noise().
// By default, noise() produces different results each time the program is run.
// Explicitly set the seed parameter to a constant to return the same pseudo - random numbers each time the software is run.
DLL_EXPORT void noiseSeed(int seed);
