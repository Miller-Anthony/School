//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Mesh.h"

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
	AEGfxVertexList* pMesh;		// Pointer to a Mesh

	 // Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-xHalfSize, -yHalfSize, 0x00FFFFFF, 0.0f, vSize,
		xHalfSize, -yHalfSize, 0x00FFFFFF, uSize, vSize,
		-xHalfSize, yHalfSize, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		xHalfSize, -yHalfSize, 0x00FFFFFF, uSize, vSize,
		xHalfSize, yHalfSize, 0x00FFFFFF, uSize, 0.0f,
		-xHalfSize, yHalfSize, 0x00FFFFFF, 0.0f, 0.0f);

	pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh, "Failed to create %s!!", name);

	if (!pMesh)
	{
		return NULL;
	}
	return pMesh;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

