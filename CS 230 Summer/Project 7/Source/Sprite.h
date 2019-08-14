//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct AEGfxVertexList AEGfxVertexList;
typedef class SpriteSource * SpriteSourcePtr;
typedef class Sprite Sprite;
typedef class Sprite * SpritePtr;
typedef class Transform * TransformPtr;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef class Sprite : public Component
{
public:

	// Dynamically allocate a new sprite object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: Make sure to initialize the 'alpha' member variable to 1.0f.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
	Sprite(void);

	// Free the memory associated with a sprite object.
// (Also, set the sprite pointer to NULL.)
// Params:
//	 sprite = Pointer to the sprite pointer.
	~Sprite(void);

	// Dynamically allocate a clone of an existing sprite.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
	ComponentPtr Clone(void) const;

	// Read the properties of a Sprite component from a file.
	// [NOTE: Read the frameIndex value using StreamReadInt.]
	// [NOTE: Read the alpha value using StreamReadFloat.]
	// [NOTE: Read a token and call MeshManagerBuild(), passing the token.
	//	  Attach the returned mesh to the sprite using SpriteSetMesh(). ]
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//	 stream = Pointer to the data stream used for reading.
	void Read(Stream stream);

	// Draw a sprite (Sprite can be textured or untextured).
	// Params:
	//	 sprite = Pointer to the sprite object.
	//   transform = Pointer to the sprite object's transform.
	void Draw(void);

	// Get a sprite's alpha value.
	// Params:
	//	 sprite = Pointer to the sprite object.
	// Returns:
	//	 If the pointer is valid,
	//		then return the sprite's alpha value (a value between 0.0f and 1.0f),
	//		else return 0.0f.
	float GetAlpha(void);

	// Set a sprite's alpha value.
	// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
	//	input value might be outside of this range.)
	// (HINT: See AEClamp in AEMath.h.)
	// Params:
	//	 sprite = Pointer to the sprite object.
	//   newAlpha = The sprite's new alpha value.
	void SetAlpha(float newAlpha);

	// Set the sprite's current frame.
	// (NOTE: You must verify that the frameIndex parameter is within the
	//	range [0 to frame count] before changing the sprite's frame index!)
	// Params:
	//	 sprite = Pointer to the sprite object.
	//   frameIndex = New frame index for the sprite (0 .. frame count).
	// ADDITIONAL REQUIREMENTS:
	// - This function must make the following function call:
	//     TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
	void SetFrame(unsigned int frameIndex);

	// Set the sprite's mesh.
	// (NOTE: This mesh may be textured or untextured.)
	// (NOTE: This mesh may contain any number of triangles.)
	// Params:
	//	 sprite = Pointer to the sprite object.
	//   mesh = Pointer to a mesh created using the Alpha Engine.
	void SetMesh(AEGfxVertexList * mesh);

	// Set a new SpriteSource for the specified sprite.
	// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
	//	texture from a sprite and cause the sprite to be displayed as a colored mesh.)
	// Params:
	//	 sprite = Pointer to the sprite to be modified.
	//	 spriteSource = A new sprite source for the sprite (this pointer may be NULL).
	void SetSpriteSource(SpriteSourcePtr spriteSource);

	// Assign a text string to a sprite object.  This will allow a sequence of
	//	 characters to be displayed as text.
	// (NOTE: The text parameter may be NULL.  This will remove an existing text
	//	 string from a sprite and cause the sprite to be displayed normally.)
	// Params:
	//	 sprite = Pointer to the sprite to be modified.
	//	 text = Pointer to a zero-terminated array of characters.
	void SetText(const char * text);

private:
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	SpriteSourcePtr spriteSource;

	// The mesh used to draw the sprite.
	AEGfxVertexList * mesh;

	// Zero-terminated string used to display sprite text.
	const char * text;

} Sprite;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/*----------------------------------------------------------------------------*/
