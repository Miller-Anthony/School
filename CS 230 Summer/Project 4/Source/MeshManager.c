//------------------------------------------------------------------------------
//
// File Name:	MeshManager.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "MeshManager.h"
#include "Stream.h"
#include "Mesh.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

const int meshListSize = 100;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct MeshManager
{
	// The number of game objects currently in the list.
	unsigned int meshCount;

	// The maximum number of game objects ever in the list, at any given moment.
	//unsigned int meshMax;

	// A list of all currently loaded meshes.
	// This list can be a fixed-length array (minimum size of 10 entries)
	// or a dynamically-sized array, such as a linked list.
	AEGfxVertexList *	meshList[100];

} MeshManager;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

MeshManager meshManager;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void MeshManagerAdd(AEGfxVertexList *mesh);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Mesh Manager.
// (NOTE: Make sure to initialize all memory to zero.)
void MeshManagerInit()
{
	meshManager.meshCount = 0;

	for (int i = 0; i < meshListSize; i++)
	{
		meshManager.meshList[0] = NULL;
	}
}

// Create a mesh and add it to the mesh manager.
// 1: Use sprintf_s() to construct a path name using meshName
//	   (HINT: The correct path name should be constructed using "Data/&s.txt".)
// 2: Call StreamOpen(), passing the pathname
// 3: If the stream was opened successfully,
//	  a: Call MeshRead() to construct a mesh using data read from the file
//	  b: Call MeshManagerAdd(), passing the created mesh
//	  c: Return the created mesh
// Params:
//	 meshName = The name of the mesh to be created.
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created mesh,
//	   else return NULL.
AEGfxVertexList * MeshManagerBuild(const char * meshName)
{
	char pathName[FILENAME_MAX] = "";
	sprintf_s(pathName, _countof(pathName), "Data/%s.txt", meshName);
	Stream stream = StreamOpen(pathName);

	if (stream)
	{
		AEGfxVertexList *mesh = MeshRead(stream);
		 
		MeshManagerAdd(mesh);
		return mesh;
	}
	return NULL;
}

// Free all meshes in the Mesh Manager.
// (NOTE: Make sure to call AEGfxMeshFree() to free each mesh.)
// (HINT: The list should contain nothing but NULL pointers once this function is done.)
void MeshManagerFreeAll()
{
	for (int i = 0; i < meshListSize; i++)
	{
		if (meshManager.meshList[i])
		{
			AEGfxMeshFree(meshManager.meshList[i]);
			meshManager.meshList[i] = NULL;
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void MeshManagerAdd(AEGfxVertexList *mesh)
{
	if (mesh)
	{
		meshManager.meshList[meshManager.meshCount] = mesh;
		meshManager.meshCount++;
	}
}