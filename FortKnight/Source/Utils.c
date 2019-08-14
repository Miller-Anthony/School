// ---------------------------------------------------------------------------
// Project Name		:	Knightmare
// File Name		  :	Utils.c
// Author			    :	Brayan
// Creation Date	:	1/16/2019
// Purpose			  :	Functions with special utilities
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "stdafx.h"		// Should be included first in every .c file!

#include "AEEngine.h"
#include "Utils.h"
#include <stdlib.h>
// ---------------------------------------------------------------------------

// Libraries
#ifdef _DEBUG
#pragma comment (lib, "Alpha_Engine_D.lib")
#else
#pragma comment (lib, "Alpha_Engine.lib")
#endif

int RandomRange(int min, int max)
{
	return (rand() % (max + 1 - min)) + min;
}

float RandomRangeFloat(float rangeMin, float rangeMax)
{
    return (float)((double)rand() / (RAND_MAX + 1) * (rangeMax - rangeMin) + rangeMin); //from Microsoft
}

float Square(float num)
{
	return num * num;
}

int IntFromFile(const char * filename)
{
    FILE* file;
    fopen_s(&file, filename, "rt");
    char buffer[17] = { 0 };
    if (file)
    {
        fgets(buffer, sizeof(buffer) - 1, file);
        fclose(file);
    }

    return atoi(buffer);
}