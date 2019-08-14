//------------------------------------------------------------------------------
//
// File Name:	Stream.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230SU19
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
// Forward References:
//------------------------------------------------------------------------------

typedef FILE*	Stream;

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

// Open a file for reading.
// (NOTE: Use fopen_s() with the "rt" option.)
// (NOTE: You must generate the following trace message if the file was not opened successfully:
//	  TraceMessage("Error: StreamOpen could not open file %s; %s", fileName, errorMsg);
//	  Where errorMsg is a char array containing the error message obtained using strerror_s().)
// Params:
//	 filename = Name of the file to be opened for reading.
// Returns:
//	 NULL if the file name is null or the file could not be opened.
//	 Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char * filename);

// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 0 if the stream was not opened succesfully;
//	 otherwise, an integer value read from the file.
int StreamReadInt(Stream stream);

// Close an opened stream.
// (NOTE: Do not attempt to close the stream if the pointer is null.)
// Params:
//	 stream = The file stream to be closed.
void StreamClose(Stream * stream);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
