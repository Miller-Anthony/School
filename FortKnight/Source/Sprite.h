//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Doug Schilling (dschilling)
// Project:		KnightMare
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
// Forward References:
//------------------------------------------------------------------------------

typedef struct AEGfxVertexList AEGfxVertexList;
typedef struct SpriteSource * SpriteSourcePtr;
typedef struct Sprite Sprite;
typedef struct Sprite * SpritePtr;
typedef struct Transform * TransformPtr;

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

// Dynamically allocate a new sprite object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: Make sure to initialize the 'alpha' member variable to 1.0f.)
// Params:
//	 name = The name of the sprite.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpritePtr SpriteCreate(const char * name);

//shallow copies contents of a sprite to another
void SpriteCopy(SpritePtr from, SpritePtr to);

//Zeroes out a sprite's members
void SpriteZero(SpritePtr sprite);

// Free the memory associated with a sprite object.
// (Also, set the sprite pointer to NULL.)
// Params:
//	 sprite = Pointer to the sprite pointer.
void SpriteFree(SpritePtr * sprite);

// Draw a sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the sprite object.
//   transform = Pointer to the sprite object's transform.
void SpriteDraw(const Sprite* sprite, TransformPtr transform);

//Draws a sprite with a specified spritesource and transform
//does not set sprite's spritesource to spritesource
void SpriteDrawWithSpriteSource(const Sprite* sprite, TransformPtr transform, SpriteSourcePtr spriteSource);

// Get a sprite's alpha value.
// Params:
//	 sprite = Pointer to the sprite object.
// Returns:
//	 If the pointer is valid,
//		then return the sprite's alpha value (a value between 0.0f and 1.0f),
//		else return 0.0f.
float SpriteGetAlpha(SpritePtr sprite);

//Gets a sprite's spritesource
SpriteSourcePtr SpriteGetSpriteSource(SpritePtr sprite);

//Gets a sprite's name
const char* SpriteGetName(SpritePtr sprite);

// Set a sprite's alpha value.
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
//	input value might be outside of this range.)
// (HINT: See AEClamp in AEMath.h.)
// Params:
//	 sprite = Pointer to the sprite object.
//   newAlpha = The sprite's new alpha value.
void SpriteSetAlpha(SpritePtr sprite, float newAlpha);

// Set the sprite's current frame.
// (NOTE: You must verify that the frameIndex parameter is within the
//	range [0 to frame count] before changing the sprite's frame index!)
// Params:
//	 sprite = Pointer to the sprite object.
//   frameIndex = New frame index for the sprite (0 .. frame count).
// ADDITIONAL REQUIREMENTS:
//   This function must make the following function call:
//     TraceMessage("SpriteSetFrame: %s frame index = %d", sprite->name, frameIndex);
void SpriteSetFrame(SpritePtr sprite, unsigned int frameIndex);

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the sprite object.
//   mesh = Pointer to a mesh created using the Alpha Engine.
void SpriteSetMesh(SpritePtr sprite, AEGfxVertexList * mesh);

// Set a new SpriteSource for the specified sprite.
// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
//	texture from a sprite and cause the sprite to be displayed as a colored mesh.)
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 spriteSource = A new sprite source for the sprite (this pointer may be NULL).
void SpriteSetSpriteSource(SpritePtr sprite, SpriteSourcePtr spriteSource);

void SpriteSetText(SpritePtr sprite, const char * text);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

