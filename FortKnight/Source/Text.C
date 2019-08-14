//------------------------------------------------------------------------------
//
// File Name:	Text.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Mesh.h"
#include "Text.h"
#include "Sprite.h"
#include "Transform.h"
#include "SpriteSource.h"

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

SpritePtr emptyRect;
TransformPtr emptyTransform;
SpritePtr healthBar;
TransformPtr healthTransform;
SpriteSourcePtr healthPixel;
SpritePtr RedBar;
TransformPtr RedTransform;
SpriteSourcePtr RedPixel;
SpritePtr blueBar;
TransformPtr blueTransform;
SpriteSourcePtr bluePixel;
AEGfxVertexList* pMeshLine;			// Pointer to Mesh (Model)
AEGfxVertexList* pMeshTri;			// Pointer to Mesh (Model)
AEGfxVertexList* pMeshRed;			// mesh for below the health bar
AEGfxVertexList* pMeshBlue;			// mesh for the stamina bar

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void CreateEmptyRect();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void DrawEmptyRect(float x, float y, float w, float h)
{
	f32 xPos = 0;
	f32 yPos = 0;

	AEGfxGetCamPosition(&xPos, &yPos);

    if (!pMeshLine)
    {
        CreateEmptyRect();
    }

	if (!emptyTransform)
	{
		AEVec2 scale;
		emptyTransform = TransformCreate(xPos + x, yPos + y);

		scale.x = w;
		scale.y = h;
		TransformSetScale(emptyTransform, &scale);
	}
	else
	{
		AEVec2 trans;
		AEVec2 scale;

		trans.x = xPos + x;
		trans.y = yPos + y;

		scale.x = w;
		scale.y = h;

		TransformSetTranslation(emptyTransform, &trans);
		TransformSetScale(emptyTransform, &scale);
	}

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxSetTransform(TransformGetMatrix(emptyTransform)->m); //put it in world space
    AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);
}

void DrawFilledRect(float x, float y, float w, float h)
{
	f32 xPos = 0;
	f32 yPos = 0;

	AEGfxGetCamPosition(&xPos, &yPos);

	if (!healthPixel)
	{
		healthPixel = SpriteSourceCreate(1, 1, AEGfxTextureLoad("Assets/Health.png"));
	}

	if (!pMeshTri)
	{
		pMeshTri = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "health mesh");
	}

	if (!healthBar)
	{
		healthBar = SpriteCreate("health");
		SpriteSetMesh(healthBar, pMeshTri);
		SpriteSetSpriteSource(healthBar, healthPixel);
	}

	if (!healthTransform)
	{
		AEVec2 scale;
		healthTransform = TransformCreate(xPos + x, yPos + y);
	
		scale.x = w;
		scale.y = h;
		TransformSetScale(healthTransform, &scale);
	}
	else
	{
		AEVec2 trans;
		AEVec2 scale;
		
		trans.x = xPos + x;
		trans.y = yPos + y;

		scale.x = w;
		scale.y = h;

		TransformSetTranslation(healthTransform, &trans);
		TransformSetScale(healthTransform, &scale);
	}

	SpriteDraw(healthBar, healthTransform);
}

void DrawRedRect(float x, float y, float w, float h)
{
	f32 xPos = 0;
	f32 yPos = 0;

	AEGfxGetCamPosition(&xPos, &yPos);

	if (!RedPixel)
	{
		RedPixel = SpriteSourceCreate(1, 1, AEGfxTextureLoad("Assets/Red.png"));
	}

	if (!pMeshRed)
	{
		pMeshRed = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "red mesh");
	}

	if (!RedBar)
	{
		RedBar = SpriteCreate("decreasing health");
		SpriteSetSpriteSource(RedBar, RedPixel);
		SpriteSetMesh(RedBar, pMeshRed);
	}

	if (!RedTransform)
	{
		AEVec2 scale;
		RedTransform = TransformCreate(xPos + x, yPos + y);

		scale.x = w;
		scale.y = h;
		TransformSetScale(RedTransform, &scale);
	}
	else
	{
		AEVec2 trans;
		AEVec2 scale;

		trans.x = xPos + x;
		trans.y = yPos + y;

		scale.x = w;
		scale.y = h;

		TransformSetTranslation(RedTransform, &trans);
		TransformSetScale(RedTransform, &scale);
	}


	SpriteDraw(RedBar, RedTransform);
}

void DrawBlueRect(float x, float y, float w, float h)
{
	f32 xPos = 0;
	f32 yPos = 0;

	AEGfxGetCamPosition(&xPos, &yPos);

	if (!bluePixel)
	{
		bluePixel = SpriteSourceCreate(1, 1, AEGfxTextureLoad("Assets/Blue.png"));
	}

	if (!pMeshBlue)
	{
		pMeshBlue = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "blue mesh");
	}

	if (!blueBar)
	{
		blueBar = SpriteCreate("stamina");
		SpriteSetSpriteSource(blueBar, bluePixel);
		SpriteSetMesh(blueBar, pMeshBlue);
	}

	if (!blueTransform)
	{
		AEVec2 scale;
		blueTransform = TransformCreate(xPos + x, yPos + y);

		scale.x = w;
		scale.y = h;
		TransformSetScale(blueTransform, &scale);
	}
	else
	{
		AEVec2 trans;
		AEVec2 scale;

		trans.x = xPos + x;
		trans.y = yPos + y;

		scale.x = w;
		scale.y = h;

		TransformSetTranslation(blueTransform, &trans);
		TransformSetScale(blueTransform, &scale);
	}


	SpriteDraw(blueBar, blueTransform);
}

void FreeRects(void)
{
	if (pMeshLine)
	{
		AEGfxMeshFree(pMeshLine);
		pMeshLine = NULL;
	}
	if (pMeshTri)
	{
		AEGfxMeshFree(pMeshTri);
		pMeshTri = NULL;
	}		
	if (pMeshRed)
	{
		AEGfxMeshFree(pMeshRed);
		pMeshRed = NULL;
	}
	if (pMeshBlue)
	{
		AEGfxMeshFree(pMeshBlue);
		pMeshBlue = NULL;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void CreateEmptyRect()
{
	if (!pMeshLine)
	{
		AEGfxMeshStart();
		// This shape has 4 vertices
		AEGfxVertexAdd(0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
		pMeshLine = AEGfxMeshEnd();
		AE_WARNING_MESG(pMeshLine, "Failed to create mesh 2!!");
	}
}