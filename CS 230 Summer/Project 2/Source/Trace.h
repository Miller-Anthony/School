//------------------------------------------------------------------------------
//
// File Name:	Trace.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
// - Open "trace.log" for writing in text mode.
// - Perform error handling in the event that the file failed to open.
void TraceInit();

// Output a message to the Tracing/Logging file.
// - Print the given message to the file if it was opened successfully.
// - Also print the message to the console window.
// - Every message must be printed on its own line.
// - There must be no blank lines between messages.
void TraceMessage(const char * formatString, ...);

// Shutdown the Tracing/Logging module.
// - Close the file if-and-only-if the file was opened successfully
void TraceShutdown();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

