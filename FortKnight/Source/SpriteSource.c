//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Brayan Lopez
// Project:		KnightMare
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
	SpriteSourcePtr spriteSPtr = (SpriteSourcePtr)calloc(1, sizeof(SpriteSource));
	if (spriteSPtr)
	{
		spriteSPtr->numCols = numCols;
		spriteSPtr->numRows = numRows;
		spriteSPtr->pTexture = pTexture;
	}

	return spriteSPtr;
}

//copies a sprite source's values from one to another
void SpriteSourceCopy(SpriteSourcePtr from, SpriteSourcePtr to)
{
    if(from && to)
        *to = *from;
}

//Zeroes a spritesource (does not free)
void SpriteSourceZero(SpriteSourcePtr spriteSource)
{
    if (spriteSource)
    {
        spriteSource->numCols = 0;
        spriteSource->numRows = 0;
        spriteSource->pTexture = 0;
    }
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
		return spriteSource->pTexture;

	return NULL;
}

//sets a spritesource's texture
void SpriteSourceSetTexture(SpriteSourcePtr spriteSource, AEGfxTexturePtr texture)
{
	if (spriteSource && texture)
	{
		spriteSource->pTexture = texture;
	}
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
		return spriteSource->numCols*spriteSource->numRows;

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
		float uSize, vSize;
		uSize = 1.0f / spriteSource->numCols;
		vSize = 1.0f / spriteSource->numRows;

		*u = uSize * (frameIndex % spriteSource->numCols);
		*v = vSize * (frameIndex / spriteSource->numCols);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

