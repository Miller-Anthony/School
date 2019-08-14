//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Brayan Lopez
// Project:		KnightMare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"
#include "AEEngine.h"

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

// Create a quadrilateral mesh using the Alpha Engine.
// Params:
//	 xHalfSize = The X half-size of the mesh.
//	 yHalfSize = The Y half-size of the mesh.
//   uSize = The U size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//   vSize = The V size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//	 name = A name for the mesh.  Currently used only for error messaging.
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created mesh,
//	   else return NULL.
AEGfxVertexList * MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char * name)
{
	AEGfxVertexList* mesh = NULL;
	AEGfxMeshStart();

	AEGfxTriAdd(-xHalfSize, -yHalfSize, 0, 0.0f , vSize, //bottom left
				 xHalfSize, -yHalfSize, 0, uSize, vSize, //bottom right
				-xHalfSize,  yHalfSize, 0, 0.0f , 0);	 //top left

	AEGfxTriAdd(xHalfSize,  yHalfSize, 0, uSize, 0,      //top right
		       -xHalfSize,  yHalfSize, 0, 0.0f , 0,      //top left
		        xHalfSize, -yHalfSize, 0, uSize, vSize); //bottom right

	mesh = AEGfxMeshEnd();

	AE_ASSERT_MESG(mesh, "Failed to create mesh: %s", name); 

	return mesh;

}

// Render a mesh (textured or untextured) using the Alpha Engine.
// Params:
//	 mesh = Pointer to the mesh to be rendered.
//	 spriteSource = Pointer to sprite source used for rendering (this may be NULL).
//	 transform = The transformation matrix used to scale, rotate, and translate the sprite.
//	 frameIndex = The index into a sprite sheet; used for calculating UV offsets.
void MeshRender(AEGfxVertexList * mesh, SpriteSourcePtr spriteSource, AEMtx33 * transform, unsigned frameIndex)
{
    if (spriteSource)
    {
        AEVec2 UVs;
        SpriteSourceGetUV(spriteSource, frameIndex, &UVs.x, &UVs.y);
        AEGfxTextureSet(SpriteSourceGetTexture(spriteSource), UVs.x, UVs.y);
    }
    AEGfxSetTransform(transform->m); //put it in world space
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

