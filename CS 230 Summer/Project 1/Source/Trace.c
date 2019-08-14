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
static FILE * traceFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
void TraceInit()
{
	// TODO: Open "trace.log" for writing (text mode).
	// fopen_s:
	// https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(stdio%2Ffopen_s);k(fopen_s);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true

	// Error handling:
	// https://msdn.microsoft.com/en-us/library/9t0e6085.aspx
	fopen_s(&traceFile, "trace.log", "wt");

	if (!traceFile)
	{
		printf("Trace file failed to open\n");
	}
}

// Output a message to the Tracing/Logging file.
void TraceMessage(const char * formatString, ...)
{
	if (formatString)
	{
		va_list argument;	//holds the extra information passed into the function to modify the string
		va_start(argument, formatString);	//grab the extra information to modify the string


		// TODO: Write the message to the Tracing/Logging file.
		if (traceFile)
		{
			//print message to the output file
			_vfprintf_l(traceFile, formatString, NULL, argument);
			fprintf(traceFile, "\n");
		}

		// TODO: Also print the message to the console window.
		_vfprintf_l(stdout, formatString, NULL, argument);
		printf("\n");

		va_end(argument);	//signafy that we are done with the extra information
	}
}

// Shutdown the Tracing/Logging module.
void TraceShutdown()
{
	// TODO: Close "trace.log" if it has been opened successfully.
	if (traceFile)
	{
		fclose(traceFile);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

