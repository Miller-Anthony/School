//------------------------------------------------------------------------------
//
// File Name:	Trace.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>		// va_copy()

#include "Trace.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.
static FILE *fp;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
void TraceInit()
{
	fopen_s(&fp, ".\\trace.log", "wt"); //open trace.log in write mode

		//if the file did not open properly
	if (!fp)
	{
		perror( "perror says open failed" );
	}
}

// Output a message to the Tracing/Logging file.
void TraceMessage(const char * formatString, ...)
{
    if (fp)
    {
        va_list argument;	                //holds the extra information passed into the function to modify the string
        va_start(argument, formatString);	//grab the extra information to modify the string

          //print message to the output file
        _vfprintf_l(fp, formatString, NULL, argument);
        fprintf(fp, "\n");

        //print message to the command window
        _vfprintf_l(stdout, formatString, NULL, argument);
        printf("\n");

        va_end(argument);	//signafy that we are done with the extra information
    }
}

// Shutdown the Tracing/Logging module.
void TraceShutdown()
{
		//if the file is not null, close the file
	if (fp)
	{
		fclose(fp);
	}
	
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

