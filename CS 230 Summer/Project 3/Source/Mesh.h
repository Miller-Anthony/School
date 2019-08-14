//------------------------------------------------------------------------------
//
// File Name:	Mesh.h
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

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct AEGfxVertexList AEGfxVertexList;
typedef struct Matrix2D Matrix2D;
typedef struct SpriteSource SpriteSource;

//------------------------------------------------------------------------------
// Public Constants:
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
AEGfxVertexList * MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char * name);

// Render a mesh (textured or untextured) using the Alpha Engine.
// Params:
//	 mesh = Pointer to the mesh to be rendered.
//	 spriteSource = Pointer to sprite source used for rendering (this may be NULL).
//	 transform = The transformation matrix used to scale, rotate, and translate the sprite.
//	 frameIndex = The index into a sprite sheet; used for calculating UV offsets.
void MeshRender(AEGfxVertexList * mesh, SpriteSource * spriteSource, Matrix2D * transform, unsigned frameIndex);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

