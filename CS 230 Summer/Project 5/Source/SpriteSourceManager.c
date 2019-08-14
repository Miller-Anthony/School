//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceManager.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "SpriteSource.h"
#include "SpriteSourceManager.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

const unsigned spriteSourceListSize = 100;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct SpriteSourceManager
{
	// The number of sprite sources currently in the list.
	unsigned int spriteSourceCount;

	// A list of all currently loaded sprite sources.
	// This list can be a fixed-length array (minimum size of 10 entries)
	// or a dynamically-sized array, such as a linked list.
	SpriteSourcePtr	spriteSourceList[100];

} SpriteSourceManager;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

SpriteSourceManager sourceManager;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void SpriteSourceManagerAdd(SpriteSourcePtr spriteSource);
SpriteSourcePtr SpriteSourceManagerFind(const char * spriteSourceName);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Sprite Source Manager.
// (NOTE: Make sure to initialize all memory to zero.)
void SpriteSourceManagerInit()
{
	sourceManager.spriteSourceCount = 0;
	for (unsigned i = 0; i < spriteSourceListSize; i++)
	{
		sourceManager.spriteSourceList[i] = NULL;
	}
}

// Create a SpriteSource and add it to the SpriteSource manager.
// 1: Call SpriteSourceManagerFind() to determine if the sprite source already exists
// 2: If the named sprite source does not already exist,
//	  a: Use sprintf_s() to construct a path name using SpriteSourceName
//	     (HINT: The correct path name should be constructed using "Data/&s.txt".)
//	  b: Call StreamOpen(), passing the pathname
//    c: If the stream was opened successfully,
//		 1: Call SpriteSourceRead() to construct a SpriteSource using data read from the file
//		 2: Call SpriteSourceManagerAdd(), passing the created SpriteSource
// 3: Return the SpriteSource (already existing or just created)
// Params:
//	 SpriteSourceName = The name of the SpriteSource to be created.
// Returns:
//	 If the SpriteSource already exists or was created successfully,
//	   then return a pointer to the SpriteSource,
//	   else return NULL.
SpriteSourcePtr SpriteSourceManagerBuild(const char * spriteSourceName)
{
	SpriteSourcePtr holder = SpriteSourceManagerFind(spriteSourceName);

	if (!holder)
	{
		char pathName[FILENAME_MAX] = "";
		sprintf_s(pathName, _countof(pathName), "Data/%s.txt", spriteSourceName);

		Stream stream = StreamOpen(pathName);

		if (stream)
		{
			holder = SpriteSourceRead(stream);
			SpriteSourceManagerAdd(holder);
		}
	}
	return holder;
}

// Free all SpriteSourcees in the SpriteSource Manager.
// (NOTE: Make sure to call SpriteSourceFree() to free each SpriteSource.)
// (HINT: The list should contain nothing but NULL pointers once this function is done.)
void SpriteSourceManagerFreeAll()
{
	for (unsigned i = 0; i < spriteSourceListSize; i++)
	{
		if (sourceManager.spriteSourceList[i])
		{
			SpriteSourceFree(&(sourceManager.spriteSourceList[i]));
			sourceManager.spriteSourceList[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void SpriteSourceManagerAdd(SpriteSourcePtr spriteSource)
{
	if (spriteSource)
	{
		sourceManager.spriteSourceList[sourceManager.spriteSourceCount] = spriteSource;
		sourceManager.spriteSourceCount++;
	}
}

SpriteSourcePtr SpriteSourceManagerFind(const char * spriteSourceName)
{
	for (unsigned i = 0; i < spriteSourceListSize; i++)
	{
		if (SpriteSourceIsNamed(sourceManager.spriteSourceList[i], spriteSourceName))
		{
			return sourceManager.spriteSourceList[i];
		}
	}
	return NULL;
}