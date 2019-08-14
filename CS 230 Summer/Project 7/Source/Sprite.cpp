//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Sprite.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "SpriteSourceManager.h"
#include "Mesh.h"
#include "MeshManager.h"
#include "Trace.h"

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

// Dynamically allocate a new sprite object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: Make sure to initialize the 'alpha' member variable to 1.0f.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Sprite::Sprite(void) : Component(SpriteType)
{
	alpha = 1.0f;
}

// Dynamically allocate a clone of an existing sprite.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ComponentPtr Sprite::Clone() const
{
	SpritePtr holder = new Sprite;
	if (holder)
	{
		*holder = *this;
	}
	return holder;
}

// Free the memory associated with a sprite object.
// (Also, set the sprite pointer to NULL.)
// Params:
//	 sprite = Pointer to the sprite pointer.
Sprite::~Sprite(void)
{
	delete spriteSource;
	spriteSource = NULL;
}

// Read the properties of a Sprite component from a file.
// [NOTE: Read the frameIndex value using StreamReadInt.]
// [NOTE: Read the alpha value using StreamReadFloat.]
// Params:
//	 sprite = Pointer to the Sprite component.
//	 stream = Pointer to the data stream used for reading.
void Sprite::Read(Stream stream)
{
	if (stream)
	{
		frameIndex = StreamReadInt(stream);
		alpha = StreamReadFloat(stream);
		
		const char *name = StreamReadToken(stream);
		AEGfxVertexList *holdMesh = MeshManagerBuild(name);
		SetMesh(holdMesh);

		name = StreamReadToken(stream);
		SpriteSourcePtr holdSpriteSource = SpriteSourceManagerBuild(name);
		SetSpriteSource(holdSpriteSource);
	}
}

// Draw a sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the sprite object.
//   transform = Pointer to the sprite object's transform.
void Sprite::Draw(void)
{
	if (spriteSource)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	}

	// Drawing the mesh (list of triangles)
	AEGfxSetTransparency(alpha);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);

	if (!text)
	{
		MeshRender(mesh, spriteSource, this->GetParent()->GetTransform()->GetMatrix(), frameIndex);
	}
	else
	{
		//Local variables
		const Vector2D *holdScale = this->GetParent()->GetTransform()->GetScale();
		Matrix2D *matrix = this->GetParent()->GetTransform()->GetMatrix();
		Matrix2D offSet;
		const char * holdText = text;

		Matrix2DTranslate(&offSet, holdScale->x, 0);
			
		while (*holdText)
		{
			unsigned int frame;

			if (*holdText - ' ' >= 0)
			{
				//hold what frame of the font sheet to look at
				frame = *holdText - ' ';
			}
			else
			{
				frame = 0;
			}
			//draw the character to the screen
			MeshRender(mesh, spriteSource, matrix, frame);

			//increment to the next character in the text field
			holdText++;

			//increment the offset of the next character
			Matrix2DConcat(matrix, &offSet, matrix);
		}
	}
}

// Get a sprite's alpha value.
// Params:
//	 sprite = Pointer to the sprite object.
// Returns:
//	 If the pointer is valid,
//		then return the sprite's alpha value (a value between 0.0f and 1.0f),
//		else return 0.0f.
float Sprite::GetAlpha(void)
{
	return alpha;
}

// Set a sprite's alpha value.
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
//	input value might be outside of this range.)
// (HINT: See AEClamp in AEMath.h.)
// Params:
//	 sprite = Pointer to the sprite object.
//   newAlpha = The sprite's new alpha value.
void Sprite::SetAlpha(float newAlpha)
{
	alpha = AEClamp(newAlpha, 0.0f, 1.0f);
}

// Set the sprite's current frame.
// (NOTE: You must verify that the frameIndex parameter is within the
//	range [0 to frame count] before changing the sprite's frame index!)
// Params:
//	 sprite = Pointer to the sprite object.
//   frameIndex = New frame index for the sprite (0 .. frame count).
// ADDITIONAL REQUIREMENTS:
// - This function must make the following function call:
//     TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
void Sprite::SetFrame(unsigned int newFrameIndex)
{
	frameIndex = newFrameIndex;
	TraceMessage("SpriteSetFrame: frame index = %d", newFrameIndex);
}

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the sprite object.
//   mesh = Pointer to a mesh created using the Alpha Engine.
void Sprite::SetMesh(AEGfxVertexList * newMesh)
{
	if (newMesh)
	{
		mesh = newMesh;
	}
}

// Set a new SpriteSource for the specified sprite.
// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
//	texture from a sprite and cause the sprite to be displayed as a colored mesh.)
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 spriteSource = A new sprite source for the sprite (this pointer may be NULL).
void Sprite::SetSpriteSource(SpriteSourcePtr newSpriteSource)
{
	spriteSource = newSpriteSource;
}

// Assign a text string to a sprite object.  This will allow a sequence of
//	 characters to be displayed as text.
// (NOTE: The text parameter may be NULL.  This will remove an existing text
//	 string from a sprite and cause the sprite to be displayed normally.)
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 text = Pointer to a zero-terminated array of characters.
void Sprite::SetText(const char * newText)
{
	text = newText;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

