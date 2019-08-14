//---------------------------------------------------------
// file:	PauseMenu.c
// author:	Akshat Madan
// brief:	Plays music for the game
//
// Copyright © 2019 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Sound.h"
#include "PauseMenu.h"
#include "Objects.h"
#include "Mesh.h"
#include "Input.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------
//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------
static char Buffer[32] = "";

static AEGfxVertexList *background;
static SpritePtr backgroundSprite;
static TransformPtr transformBG;

static AEGfxVertexList *boardVertexList;
static AEGfxTexture *boardTexture;
static SpriteSourcePtr boardSpriteSource;
static SpritePtr boardSprite;
static TransformPtr boardTransform;

static AEGfxVertexList *pauseVertexList;
static AEGfxTexture *pauseTexture;
static SpriteSourcePtr pauseSpriteSource;
static SpritePtr pauseSprite;
static TransformPtr pauseTransform;

static AEGfxVertexList *buttonselectVertexList;
static AEGfxTexture *buttonselect;
static SpriteSourcePtr buttonselectSpritePtr;
static TransformPtr buttonselectTransform;
static SpritePtr buttonselectSprite;
//---------------------------------------------------------
// Functions:
//---------------------------------------------------------
void pauseInit(void)
{
	backgroundSprite = SpriteCreate("Background Pause");
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
	background = AEGfxMeshEnd();

	SpriteSetMesh(backgroundSprite, background);
	SpriteSetAlpha(backgroundSprite, 0.65f);

	pauseVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pauseTexture = AEGfxTextureLoad("Assets/Text_White.png");
	pauseSpriteSource = SpriteSourceCreate(16, 6, pauseTexture);

	buttonselectVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	buttonselect = AEGfxTextureLoad("Assets/buttonSelectWide.png");
	buttonselectSpritePtr = SpriteSourceCreate(1, 1, buttonselect);

	boardVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	boardTexture = AEGfxTextureLoad("Assets/Board2.png");
	boardSpriteSource = SpriteSourceCreate(1, 1, boardTexture);
	boardSprite = SpriteCreate("Board");
}

void drawMenu(int button)
{
	transformBG = TransformCreate(0, 0);
	AEVec2 bgTranslation = { 0, 0 };
	AEGfxGetCamPosition(&bgTranslation.x, &bgTranslation.y);
	TransformSetTranslation(transformBG, &bgTranslation);
	AEVec2 scaleBg = { 1920, 1080 };
	TransformSetScale(transformBG, &scaleBg);
	SpriteDraw(backgroundSprite, transformBG);

	boardTransform = TransformCreate(0, 0);
	AEVec2 boardTranslation = { 0, 0 };
	AEGfxGetCamPosition(&boardTranslation.x, &boardTranslation.y);
	boardTranslation.y += 50;
	TransformSetTranslation(boardTransform, &boardTranslation);
	AEVec2 boardScale = { 1280, 720 };
	TransformSetScale(boardTransform, &boardScale);
	SpriteSetMesh(boardSprite, boardVertexList);
	SpriteSetSpriteSource(boardSprite, boardSpriteSource);
	SpriteDraw(boardSprite, boardTransform);

	sprintf_s(Buffer, 32, "Paused");
	pauseSprite = SpriteCreate("Pause Sprite");
	pauseTransform = TransformCreate(0, 0);
	AEVec2 translation = { 0,0 };
	AEGfxGetCamPosition(&translation.x, &translation.y);
	AEVec2 scale = { 25, 25 };
	TransformSetScale(pauseTransform, &scale);
	translation.x -= 75;
	translation.y += 200;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteSetMesh(pauseSprite, pauseVertexList);
	SpriteSetSpriteSource(pauseSprite, pauseSpriteSource);
	SpriteSetText(pauseSprite, Buffer);
	SpriteDraw(pauseSprite, pauseTransform);


	sprintf_s(Buffer, 32, "Resume");
	translation.y -= 100;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteDraw(pauseSprite, pauseTransform);

	sprintf_s(Buffer, 32, "Restart");
	translation.x -= 12.5;
	translation.y -= 50;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteDraw(pauseSprite, pauseTransform);

	sprintf_s(Buffer, 32, "Exit to Town");
	translation.x -= 50;
	translation.y -= 50;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteDraw(pauseSprite, pauseTransform);

	sprintf_s(Buffer, 32, "Exit to Desktop");
	translation.x -= 50;
	translation.y -= 50;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteDraw(pauseSprite, pauseTransform);

	AEVec2 selectTransform = { 0,0 };

	if (button == 0)
	{
		AEGfxGetCamPosition(&selectTransform.x, &selectTransform.y);
		selectTransform.x -= 40;
		selectTransform.y += 95;
	}
	else if (button == 1)
	{
		AEGfxGetCamPosition(&selectTransform.x, &selectTransform.y);
		selectTransform.x -= 40;
		selectTransform.y += 45;
	}
	else if (button == 2)
	{
		AEGfxGetCamPosition(&selectTransform.x, &selectTransform.y);
		selectTransform.x -= 40;
		selectTransform.y -= 5;
	}
	else if (button == 3)
	{
		AEGfxGetCamPosition(&selectTransform.x, &selectTransform.y);
		selectTransform.x -= 40;
		selectTransform.y -= 55;
	}

	buttonselectSprite = SpriteCreate("Pause Select");
	buttonselectTransform = TransformCreate(0, 0);
	AEVec2 selectScale = { 640, 256 };
	TransformSetScale(buttonselectTransform, &selectScale);
	TransformSetTranslation(buttonselectTransform, &selectTransform);
	SpriteSetMesh(buttonselectSprite, buttonselectVertexList);
	SpriteSetSpriteSource(buttonselectSprite, buttonselectSpritePtr);
	SpriteDraw(buttonselectSprite, buttonselectTransform);
}


