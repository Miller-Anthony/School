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
#include "SpriteSource.h"

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
		free(*spriteSource);
		*spriteSource = NULL;
	}
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

