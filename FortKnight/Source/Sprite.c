//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Brayan Lopez
// Project:		KnightMare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "AEVec2.h"
#include "Trace.h"
#include "Mesh.h"
#include "AEEngine.h"
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Sprite
{
    // The name of the sprite.
    const char * name;

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
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
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
SpritePtr SpriteCreate(const char * name)
{
	SpritePtr sprite = (SpritePtr)calloc(1, sizeof(Sprite));
	if (sprite)
	{
		sprite->alpha = 1.0f;
		sprite->name = name;
	}
	return sprite;

}

//shallow copies contents of a sprite to another
void SpriteCopy(SpritePtr from, SpritePtr to)
{
    if (from && to)
        *to = *from;
}


//Zeroes out a sprite's members
void SpriteZero(SpritePtr sprite)
{
    sprite->alpha = 0;
    sprite->frameIndex = 0;
    sprite->mesh = NULL;
    sprite->name = "";
    sprite->spriteSource = NULL;
    sprite->text = "";
}


// Free the memory associated with a sprite object.
// (Also, set the sprite pointer to NULL.)
// Params:
//	 sprite = Pointer to the sprite pointer.
void SpriteFree(SpritePtr * sprite)
{
	if (sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}

// Get a sprite's alpha value.
// Params:
//	 sprite = Pointer to the sprite object.
// Returns:
//	 If the pointer is valid,
//		then return the sprite's alpha value (a value between 0.0f and 1.0f),
//		else return 0.0f.
float SpriteGetAlpha(SpritePtr sprite)
{
	if (sprite)
		return sprite->alpha;
	else
		return 0.0f;
}

//Gets the Sprite's SpriteSource
SpriteSourcePtr SpriteGetSpriteSource(SpritePtr sprite)
{
    if (sprite)
        return sprite->spriteSource;
    return NULL;
}

//Gets a sprite's name
const char* SpriteGetName(SpritePtr sprite)
{
    if (sprite)
        return sprite->name;

    return NULL;
}

// Set a sprite's alpha value.
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
//	input value might be outside of this range.)
// (HINT: See AEClamp in AEMath.h.)
// Params:
//	 sprite = Pointer to the sprite object.
//   newAlpha = The sprite's new alpha value.
void SpriteSetAlpha(SpritePtr sprite, float newAlpha)
{
	if (sprite)
	{
		sprite->alpha = newAlpha;
		AEClamp(sprite->alpha, 0.0f, 1.0f); //I think this Clamp works like Unity's Clamp()
	}
}

// Set the sprite's current frame.
// (NOTE: You must verify that the frameIndex parameter is within the
//	range [0 to frame count] before changing the sprite's frame index!)
// Params:
//	 sprite = Pointer to the sprite object.
//   frameIndex = New frame index for the sprite (0 .. frame count).
// ADDITIONAL REQUIREMENTS:
//   This function must make the following function call:
//     TraceMessage("SpriteSetFrame: %s frame index = %d", sprite->name, frameIndex);
void SpriteSetFrame(SpritePtr sprite, unsigned int frameIndex)
{
	unsigned int frameCount = SpriteSourceGetFrameCount(sprite->spriteSource);
	//TraceMessage("SpriteSetFrame: %s frame index = %d", sprite->name, frameIndex);

	if (frameIndex <= frameCount) //<= because range is inclusive of frameCount
		sprite->frameIndex = frameIndex;
}

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the sprite object.
//   mesh = Pointer to a mesh created using the Alpha Engine.
void SpriteSetMesh(SpritePtr sprite, AEGfxVertexList * mesh)
{
	if(sprite)
		sprite->mesh = mesh;
}

// Set a new SpriteSource for the specified sprite.
// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
//	texture from a sprite and cause the sprite to be displayed as a colored mesh.)
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 spriteSource = A new sprite source for the sprite (this pointer may be NULL).
void SpriteSetSpriteSource(SpritePtr sprite, SpriteSourcePtr spriteSource)
{
	if(sprite)
		sprite->spriteSource = spriteSource;	 //give sprite the new one
}

// Assign a text string to a sprite object.  This will allow a sequence of
//	 characters to be displayed as text.
// (NOTE: The text parameter may be NULL.  This will remove an existing text
//	 string from a sprite and cause the sprite to be displayed normally.)
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 text = Pointer to a zero-terminated array of characters.
void SpriteSetText(SpritePtr sprite, const char * text)
{
    if (sprite)
    {
        sprite->text = text;
    }
}

// Draw a sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the sprite object.
//   transform = Pointer to the sprite object's transform.
void SpriteDraw(const Sprite* sprite, TransformPtr transform)
{
    if(sprite && transform)
    SpriteDrawWithSpriteSource(sprite, transform, sprite->spriteSource);
}

//Draws a sprite with a specified spritesource and transform
//does not set sprite's spritesource to spritesource
void SpriteDrawWithSpriteSource(const Sprite* sprite, TransformPtr transform, SpriteSourcePtr spriteSource)
{
    if (!sprite || !transform) //precautionary step
        return;
    if (!sprite->mesh) //cant draw without a mesh
        return;

    if (spriteSource)
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    else
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);

    AEGfxSetTransparency(sprite->alpha);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
    if (!sprite->text)
    {
        MeshRender(sprite->mesh, spriteSource, TransformGetMatrix(transform), sprite->frameIndex);
    }
    else
    {
        AEMtx33 mat = *TransformGetMatrix(transform); //copy of matrix
        AEMtx33 offset = { 0 };
        float scaleX = TransformGetScale(transform)->x;
        AEMtx33Trans(&offset, scaleX, 0.0f);
        const char* text = sprite->text;
        while (*text)
        {
            MeshRender(sprite->mesh, spriteSource, &mat, *text - ' ');
            text++;
            AEMtx33Concat(&mat, &offset, &mat);
        }
    }
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

