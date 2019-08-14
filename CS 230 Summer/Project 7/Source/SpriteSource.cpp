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
SpriteSource::SpriteSource(int Cols, int Rows, AEGfxTexturePtr texture)
{
	numCols = Cols;
	numRows = Rows;
	pTexture = texture;
}

// Free the memory associated with a sprite source object.
// (Also, set the sprite source pointer to NULL.)
// Params:
//	 spriteSource = Pointer to the sprite source pointer.
SpriteSource::~SpriteSource(void)
{
	if (pTexture)
	{
		AEGfxTextureUnload(pTexture);
		pTexture = NULL;
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

			SpriteSourcePtr holder = new SpriteSource(numCols, numRows, pTexture);

			holder->SetName(name);

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
bool SpriteSource::IsNamed(const char * check)
{
	if (this)
	{
		if (!strcmp(name, check))
		{
			return true;
		}
	}
	return false;
}

void SpriteSource::SetName(const char * newName)
{
	strcpy_s(name, 32, newName);
}

// Returns a pointer to the texture, for the purposes of rendering a sprite.
// Params:
//	 spriteSource = Pointer to the sprite source object.
// Returns:
//	 If the sprite source pointer is valid,
//		then return a pointer to its texture,
//		else return NULL.
AEGfxTexturePtr SpriteSource::GetTexture(void)
{
	return pTexture;
}

// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
// (Hint: Frame count = numCols * numRows.)
// Params:
//	 spriteSource = Pointer to the sprite source object.
// Returns:
//	 If the sprite source pointer is valid,
//		then return the calculated frame count,
//		else return 0.
unsigned int SpriteSource::GetFrameCount(void)
{
	return numCols * numRows;
}

// Returns the UV coordinates of the specified frame in a sprite sheet.
// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
// Params:
//	 spriteSource = Pointer to the sprite source object.
//	 frameIndex = A frame index within a sprite sheet.
//   u = Pointer to a f32 to contain the U coordinate. 
//   v = Pointer to a f32 to contain the V coordinate. 
void SpriteSource::GetUV(unsigned int frameIndex, float * u, float * v)
{
	*u = (1.0f / numCols) * (frameIndex % numCols);
	*v = (1.0f / numRows) * (frameIndex / numCols);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------