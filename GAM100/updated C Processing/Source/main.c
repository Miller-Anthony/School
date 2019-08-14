//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
// course:	GAM100-F18
//
// brief:	Main entry point for the sample project
//			of the C_Processing library
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Engine.h"

// main() the starting point for the program
// Run() is used to tell the program which init and update functions to use.
int main(void)
{    
    Run(EngineInit, EngineUpdate);
    return 0;
}
