//------------------------------------------------------------------------------
//
// File Name:	Credits.c
// Author(s):	Akshat Madan
// Project:		Knightmare
// Course:		GAM150
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "Sound.h"
#include "Credits.h"
#include "Mesh.h"
#include "Input.h"
#include "OST.h"

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
static char Buffer[16] = "";
static int time = 0;
static int frame = 168;
static f32 y = -2100;

SpritePtr buttonSprite;
SpritePtr buttonselectSpritePtr;
SpritePtr backgroundSprite;

TransformPtr buttonTransform;
TransformPtr buttonselectTransform;
TransformPtr backgroundTransform;

static AEGfxVertexList *pFontSheetVertexList; // Font Sheet Vertex List
static AEGfxTexture *pFontSheet; // Font Sheet Texture
static SpriteSourcePtr pFontSheetSprite; // Font Sheet Sprite

static AEGfxVertexList *buttonselectVertexList;
static AEGfxTexture *buttonselect;
static SpriteSourcePtr buttonselectSprite;

static AEGfxVertexList *backgroundVertexList;
static AEGfxTexture *backgroundTexture;
static SpriteSourcePtr backgroundSpriteSource;

static AEGfxVertexList *creditsVertexList;
static AEGfxTexture *creditsTexture;
static SpriteSourcePtr creditsSpriteSource;
static SpritePtr creditsSprite;
TransformPtr creditsTransform;
ObjectPtr creditsObject;

static ObjectPtr buttonGameObject;
static ObjectPtr buttonselectGameObject;
static ObjectPtr backgroundGameObject;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void CreditsLoad()
{
	creditsVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "MeshCredits");
	creditsTexture = AEGfxTextureLoad("Assets/Credits.png");
	creditsSpriteSource = SpriteSourceCreate(1, 1, creditsTexture);

	pFontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pFontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	pFontSheetSprite = SpriteSourceCreate(16, 6, pFontSheet);

	buttonselectVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	buttonselect = AEGfxTextureLoad("Assets/buttonSelect.png");
	buttonselectSprite = SpriteSourceCreate(1, 1, buttonselect);

	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);
}

// Initialize the memory associated with the Level1 game state.
void CreditsInit()
{
	stopSong();
	playSong(7);

	creditsObject = CreateObject("Credits", ObjTag);
	creditsTransform = TransformCreate(0, 0);

	AEVec2 scale = { 960, 3240 };

	creditsSprite = SpriteCreate("Credits");
	SpriteSetMesh(creditsSprite, creditsVertexList);
	SpriteSetSpriteSource(creditsSprite, creditsSpriteSource);
	TransformSetScale(creditsTransform, &scale);
	SpriteSetAlpha(creditsSprite, 1.0f);

	ObjectSetTransform(creditsTransform, creditsObject);
	ObjectSetSprite(creditsSprite, creditsObject);

	buttonGameObject = CreateObject("Button", ObjTag);
	buttonselectGameObject = CreateObject("buttonSelect", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	sprintf_s(Buffer, 16, "Back");
	buttonTransform = TransformCreate(725, -380);

	backgroundTransform = TransformCreate(0, 0);
	AEVec2 backgroundScale;
	backgroundScale.x = -1920;
	backgroundScale.y = 1080;
	TransformSetRotation(backgroundTransform, 0);
	TransformSetScale(backgroundTransform, &backgroundScale);

	backgroundSprite = SpriteCreate("Background sprite");
	SpriteSetMesh(backgroundSprite, backgroundVertexList);
	SpriteSetSpriteSource(backgroundSprite, backgroundSpriteSource);

	ObjectSetTransform(backgroundTransform, backgroundGameObject);
	ObjectSetSprite(backgroundSprite, backgroundGameObject);

	buttonselectTransform = TransformCreate(760, -385);

	AEVec2 buttonselectScale;
	TransformSetRotation(buttonselectTransform, 0);
	buttonselectScale.x = 235;
	buttonselectScale.y = 200;
	TransformSetScale(buttonselectTransform, &buttonselectScale);

	buttonselectSpritePtr = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(buttonselectSpritePtr, buttonselectVertexList);
	SpriteSetSpriteSource(buttonselectSpritePtr, buttonselectSprite);

	ObjectSetTransform(buttonselectTransform, buttonselectGameObject);
	ObjectSetSprite(buttonselectSpritePtr, buttonselectGameObject);

	PrintText(buttonGameObject, Buffer, buttonSprite, buttonTransform);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void CreditsUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);

	time++;
	if (time % 5 == 0)
	{
		frame--;
		if (frame <= -1)
			frame = 168;
	}

	AEVec2 translation = {0, -2100};
	translation.y = y;
	//y++;

	TransformSetTranslation(ObjectGetTransform(creditsObject), &translation);
	DrawObject(backgroundGameObject);
	DrawObject(creditsObject);
	DrawObject(buttonGameObject);
	DrawObject(buttonselectGameObject);

	if(/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
		GameStateManagerSetNextState(GsMenu);

	if (/*AEInputCheckCurr(VK_UP) || */GetJoystickY(SIDE_L) >= 0.25f)
		y -= 5.0f;
	else if (/*AEInputCheckCurr(VK_DOWN) || */GetJoystickY(SIDE_L) <= -0.25f)
		y += 5.0f;
	else
		y++;
}

// Shutdown any memory associated with the Level1 game state.
void CreditsShutdown()
{
	FreeObject(&creditsObject);
	FreeObject(&buttonGameObject);
	FreeObject(&buttonselectGameObject);
	FreeObject(&backgroundGameObject);
}

// Unload the resources associated with the Level1 game state.
void CreditsUnload()
{
	AEGfxMeshFree(pFontSheetVertexList);
	AEGfxMeshFree(buttonselectVertexList);
	AEGfxMeshFree(backgroundVertexList);
	AEGfxMeshFree(creditsVertexList);

	AEGfxTextureUnload(pFontSheet);
	AEGfxTextureUnload(buttonselect);
	AEGfxTextureUnload(backgroundTexture);
	AEGfxTextureUnload(creditsTexture);

	SpriteSourceFree(&pFontSheetSprite);
	SpriteSourceFree(&buttonselectSprite);
	SpriteSourceFree(&backgroundSpriteSource);
	SpriteSourceFree(&creditsSpriteSource);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform)
{

	AEVec2 scale;
	TransformSetRotation(pTransform, 0);
	scale.x = 25;
	scale.y = 25;
	TransformSetScale(pTransform, &scale);

	pSpriteSrc = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(pSpriteSrc, pFontSheetVertexList);
	SpriteSetSpriteSource(pSpriteSrc, pFontSheetSprite);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}