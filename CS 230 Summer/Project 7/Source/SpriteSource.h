//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 2
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

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct AEGfxTexture AEGfxTexture;
typedef struct AEGfxTexture *AEGfxTexturePtr;

// Pointer to a SpriteSource structure.
typedef class SpriteSource SpriteSource;
typedef class SpriteSource * SpriteSourcePtr;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef class SpriteSource
{
public:

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
	SpriteSource(int Cols, int Rows, AEGfxTexturePtr texture);

	// Free the memory associated with a sprite source object.
	// (NOTE: The texture should now be freed by this function.)
	// (Also, set the sprite source pointer to NULL.)
	// Params:
	//	 spriteSource = Pointer to the sprite source pointer.
	~SpriteSource(void);

	// Determines if a sprite source has the specified name.
	// Params:
	//	 spriteSource = Pointer to the sprite source object.
	//	 name = Pointer to the name to be compared.
	// Returns:
	//	 If the sprite source and name pointers are valid,
	//		then perform a string comparison and return the result (match = true),
	//		else return false.
	bool IsNamed(const char * check);

	void SetName(const char * newName);

	// Returns a pointer to the texture, for the purposes of rendering a sprite.
	// Params:
	//	 spriteSource = Pointer to the sprite source object.
	// Returns:
	//	 If the sprite source pointer is valid,
	//		then return a pointer to its texture,
	//		else return NULL.
	AEGfxTexturePtr GetTexture(void);

	// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
	// (Hint: Frame count = numCols * numRows.)
	// Params:
	//	 spriteSource = Pointer to the sprite source object.
	// Returns:
	//	 If the sprite source pointer is valid,
	//		then return the calculated frame count,
	//		else return 0.
	unsigned int GetFrameCount(void);

	// Returns the UV coordinates of the specified frame in a sprite sheet.
	// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
	// Params:
	//	 spriteSource = Pointer to the sprite source object.
	//	 frameIndex = A frame index within a sprite sheet.
	//   u = Pointer to a float to contain the U coordinate. 
	//   v = Pointer to a float to contain the V coordinate. 
	void GetUV(unsigned int frameIndex, float * u, float * v);

private:

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
// Public Functions:
//------------------------------------------------------------------------------

// Create a SpriteSource using data read from a file.
	// Params:
	//	 stream = Pointer to the data stream used for reading.
	// Returns:
	//	 If the sprite source was created successfully,
	//	   then return a pointer to the created sprite source,
	//	   else return NULL.
SpriteSourcePtr SpriteSourceRead(Stream stream);

/*----------------------------------------------------------------------------*/