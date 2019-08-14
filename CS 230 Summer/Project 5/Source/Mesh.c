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
#include "SpriteSource.h"
#include "Mesh.h"
#include "Stream.h"
#include "Matrix2D.h"
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

// Create a mesh using data read from a file.
// (NOTE: First read an integer indicating the number of vertices to be read.)
// (NOTE: For each vertex, read two floats (position), a hexidecimal integer (color), and two floats (UV).)
// (HINT: Call AEGfxVertexAdd() to add a single vertex to the mesh.)
// Params:
//	 stream = Pointer to the data stream used for reading.
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created mesh,
//	   else return NULL.
AEGfxVertexList * MeshRead(Stream stream)
{
	if (stream)
	{
		const char * holder = StreamReadToken(stream);
		if (strncmp(holder, "Mesh", _countof("Mesh")) == 0)
		{
			AEGfxMeshStart();
			int max = StreamReadInt(stream);

			for (int i = 0; i < max; i++)
			{
				float x = StreamReadFloat(stream);
				float y = StreamReadFloat(stream);

				unsigned color = StreamReadHex(stream);

				float u = StreamReadFloat(stream);
				float v = StreamReadFloat(stream);

				AEGfxVertexAdd(x, y, color, u, v);
			}
			return AEGfxMeshEnd();
		}
		else if (strncmp(holder, "Quad", _countof("Quad")) == 0)
		{
			float x = StreamReadFloat(stream);
			float y = StreamReadFloat(stream);

			int u = StreamReadInt(stream);
			int v = StreamReadInt(stream);

			const char *name = StreamReadToken(stream);

			return MeshCreateQuad(x, y, 1.0f / u, 1.0f / v, name);
		}
	}
	return NULL;
}

// Render a mesh (textured or untextured) using the Alpha Engine.
// Params:
//	 mesh = Pointer to the mesh to be rendered.
//	 spriteSource = Pointer to sprite source used for rendering (this may be NULL).
//	 transform = The transformation matrix used to scale, rotate, and translate the sprite.
//	 frameIndex = The index into a sprite sheet; used for calculating UV offsets.
void MeshRender(AEGfxVertexList * mesh, SpriteSource * spriteSource, Matrix2D * transform, unsigned frameIndex)
{
	if (spriteSource)
	{
		float u;
		float v;

		SpriteSourceGetUV(spriteSource, frameIndex, &u, &v);
		AEGfxTextureSet(SpriteSourceGetTexture(spriteSource), u, v);
	}
	AEGfxSetTransform(transform->m);
	AEGfxMeshDraw(mesh,AE_GFX_MDM_TRIANGLES);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

