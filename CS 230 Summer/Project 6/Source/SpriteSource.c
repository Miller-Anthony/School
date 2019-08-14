//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
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
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct SpriteSource
{
	// The name of the sprite source.
	// A buffer is used to allow each sprite source to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	char name[32];

	// The dimensions of the sprite sheet.
	int	numRows;
	int	numCols;

	// Pointer to a texture created using the Alpha Engine.
	AEGfxTexturePtr	pTexture;

} SpriteSource;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new sprite source object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 numCols = The number of columns in the sprite sheet.
//	 numRows = The number of rows in the sprite sheet.
//	 pTexture = A pointer to a texture that has been loaded by the Alpha Engine.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpriteSourcePtr SpriteSourceCreate(int numCols, int numRows, AEGfxTexturePtr pTexture)
{
	SpriteSourcePtr holder = calloc(1, sizeof(SpriteSource));

	if (!holder)
	{
		return NULL;
	}

	holder->numCols = numCols;
	holder->numRows = numRows;
	holder->pTexture = pTexture;

	return holder;
}

// Free the memory associated with a sprite source object.
// (Also, set the sprite source pointer to NULL.)
// Params:
//	 spriteSource = Pointer to the sprite source pointer.
void SpriteSourceFree(SpriteSourcePtr * spriteSource)
{
	if (spriteSource)
	{
		if ((*spriteSource)->pTexture)
		{
			AEGfxTextureUnload((*spriteSource)->pTexture);
			(*spriteSource)->pTexture = NULL;
		}
		free(*spriteSource);
		*spriteSource = NULL;
	}
}

// Create a SpriteSource using data read from a file.
// Params:
//	 stream = Pointer to the data stream used for reading.
// Returns:
//	 If the sprite source was created successfully,
//	   then return a pointer to the created sprite source,
//	   else return NULL.
SpriteSourcePtr SpriteSourceRead(Stream stream)
{
	if (stream)
	{
		const char *check = StreamReadToken(stream);

		if (strcmp(check, "SpriteSource") == 0)
		{
			const char *holdName = StreamReadToken(stream);

			char name[32];

			strcpy_s(name, 32, holdName);

			int	numCols = StreamReadInt(stream);
			int	numRows = StreamReadInt(stream);
			const char *path = StreamReadToken(stream);

			AEGfxTexturePtr pTexture = AEGfxTextureLoad(path);

			SpriteSourcePtr holder = SpriteSourceCreate(numCols, numRows, pTexture);

			strcpy_s(holder->name, 32, name);

			return holder;
		}
	}
	return NULL;
}

// Determines if a sprite source has the specified name.
// Params:
//	 spriteSource = Pointer to the sprite source object.
//	 name = Pointer to the name to be compared.
// Returns:
//	 If the sprite source and name pointers are valid,
//		then perform a string comparison and return the result (match = true),
//		else return false.
bool SpriteSourceIsNamed(SpriteSourcePtr spriteSource, const char * name)
{
	if (spriteSource && name)
	{
		if (!strcmp(spriteSource->name, name))
		{
			return true;
		}
	}
	return false;
}

// Returns a pointer to the texture, for the purposes of rendering a sprite.
// Params:
//	 spriteSource = Pointer to the sprite source object.
// Returns:
//	 If the sprite source pointer is valid,
//		then return a pointer to its texture,
//		else return NULL.
AEGfxTexturePtr SpriteSourceGetTexture(SpriteSourcePtr spriteSource)
{
	if (spriteSource)
	{
		return spriteSource->pTexture;
	}
	return NULL;
}

// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
// (Hint: Frame count = numCols * numRows.)
// Params:
//	 spriteSource = Pointer to the sprite source object.
// Returns:
//	 If the sprite source pointer is valid,
//		then return the calculated frame count,
//		else return 0.
unsigned int SpriteSourceGetFrameCount(SpriteSourcePtr spriteSource)
{
	if (spriteSource)
	{
		return spriteSource->numCols * spriteSource->numRows;
	}
	return 0;
}

// Returns the UV coordinates of the specified frame in a sprite sheet.
// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
// Params:
//	 spriteSource = Pointer to the sprite source object.
//	 frameIndex = A frame index within a sprite sheet.
//   u = Pointer to a f32 to contain the U coordinate. 
//   v = Pointer to a f32 to contain the V coordinate. 
void SpriteSourceGetUV(SpriteSourcePtr spriteSource, unsigned int frameIndex, float * u, float * v)
{
	if (spriteSource)
	{
		*u = (1.0f / spriteSource->numCols) * (frameIndex % spriteSource->numCols);
		*v = (1.0f / spriteSource->numRows) * (frameIndex / spriteSource->numCols);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

