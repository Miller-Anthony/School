//------------------------------------------------------------------------------
//
// File Name:	GameStateBREnd.c
// Author(s):	ERICH ATWELL
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Input.h"
#include "GameStateManager.h"
#include "GameStateBREnd.h"
#include "SpriteSource.h"
#include "Objects.h"
#include "Sprite.h"
#include "Transform.h"
#include "Mesh.h"
#include "Player.h"

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

extern int BRplacing;

static float WinX;
static float WinY;
static int fade = 0;
static float alpha1;
static float alpha2;
static float alpha3;
static char textBuffer[64] = "";

SpritePtr blackSprite;
TransformPtr blackTransform;
static ObjectPtr blackGameObject;
static AEGfxVertexList *blackVertexList;
static AEGfxTexture *blackTexture;
static SpriteSourcePtr blackSpriteSource;

SpritePtr black1Sprite;
TransformPtr black1Transform;
static ObjectPtr black1GameObject;
static AEGfxVertexList *black1VertexList;
static AEGfxTexture *black1Texture;
static SpriteSourcePtr black1SpriteSource;

SpritePtr black2Sprite;
TransformPtr black2Transform;
static ObjectPtr black2GameObject;
static AEGfxVertexList *black2VertexList;
static AEGfxTexture *black2Texture;
static SpriteSourcePtr black2SpriteSource;

SpritePtr textSprite;
SpritePtr backgroundSprite;

static ObjectPtr textGameObject;
static ObjectPtr backgroundGameObject;

TransformPtr textTransform;
TransformPtr backgroundTransform;

static AEGfxVertexList *textVertexList;
static AEGfxTexture *textTexture;
static SpriteSourcePtr textSpriteSource;

static char rewardBuffer[64] = "";
SpritePtr rewardSprite;
TransformPtr rewardTransform;
static AEGfxVertexList *rewardVertexList;
static AEGfxTexture *rewardTexture;
static SpriteSourcePtr rewardSpriteSource;
static ObjectPtr rewardGameObject;

static AEGfxVertexList *backgroundVertexList;
static AEGfxTexture *backgroundTexture;
static SpriteSourcePtr backgroundSpriteSource;

 static AEGfxVertexList *highlighterVertexList;
 static AEGfxTexture *highlighterTexture;
 static SpriteSourcePtr highlighterSpriteSource;
 static ObjectPtr highlighterGameObject;
 static TransformPtr highlighterTransform;
 static SpritePtr highlighterSprite;
 static char continueBuffer[16] = "";
 SpritePtr continueSprite;
 TransformPtr continueTransform;
 static ObjectPtr continueObject;
 static AEGfxVertexList *continueVertexList;
 static AEGfxTexture *continueTexture;
 static SpriteSourcePtr continueSpriteSource;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);
static void ContinueToNextScreen(void);

// Load the resources associated with the Stub game state.
void GameStateBREndLoad()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Load the data for the font sheet
	textVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	textTexture = AEGfxTextureLoad("Assets/Text_White.png");
	textSpriteSource = SpriteSourceCreate(16, 6, textTexture);

	// Load the data for the background
	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");;
	backgroundTexture = AEGfxTextureLoad("Assets/Lose.png");
	backgroundSpriteSource = SpriteSourceCreate(1, 1, backgroundTexture);

	blackVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");;
	blackTexture = AEGfxTextureLoad("Assets/BlackScreen.png");
	blackSpriteSource = SpriteSourceCreate(1, 1, blackTexture);

	black1VertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");;
	black1Texture = AEGfxTextureLoad("Assets/BlackScreen.png");
	black1SpriteSource = SpriteSourceCreate(1, 1, black1Texture);

	black2VertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");;
	black2Texture = AEGfxTextureLoad("Assets/BlackScreen.png");
	black2SpriteSource = SpriteSourceCreate(1, 1, black2Texture);

	highlighterVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	highlighterTexture = AEGfxTextureLoad("Assets/buttonSelect.png");
	highlighterSpriteSource = SpriteSourceCreate(1, 1, highlighterTexture);
}

// Initialize the memory associated with the Stub game state.
void GameStateBREndInit()
{
	WinX = AEGfxGetWinMaxX() * 2;
	WinY = AEGfxGetWinMaxY() * 2;

	fade = 0;
	alpha1 = 1.0f;
	alpha2 = 1.0f;
	alpha3 = 1.0f;
	textGameObject = CreateObject("Text", ObjTag);
	
	if (BRplacing == 1)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dst", BRplacing);
	if (BRplacing == 2)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dnd", BRplacing);
	if (BRplacing == 3)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %drd", BRplacing);
	if (BRplacing >= 4 && BRplacing <= 20)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dth", BRplacing);
	if (BRplacing == 21)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dst", BRplacing);
	if (BRplacing == 22)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dnd", BRplacing);
	if (BRplacing == 23)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %drd", BRplacing);
	if (BRplacing >= 24 && BRplacing <= 30)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dth", BRplacing);
	if (BRplacing == 31)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dst", BRplacing);
	if (BRplacing == 32)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dnd", BRplacing);
	if (BRplacing == 33)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %drd", BRplacing);
	if (BRplacing >= 34)
		sprintf_s(textBuffer, 64, "Congratulations You placed: %dth", BRplacing);
	textTransform = TransformCreate(0, 0);
	PrintText(textGameObject, textBuffer, textSprite, textTransform);

	backgroundGameObject = CreateObject("Background", ObjTag);
	backgroundTransform = TransformCreate(0, 0);
	AEVec2 backgroundScale = { 0, 0 };
	backgroundScale.x = WinX;
	backgroundScale.y = WinY;
	TransformSetRotation(backgroundTransform, 0);
	TransformSetScale(backgroundTransform, &backgroundScale);
	backgroundSprite = SpriteCreate("Background sprite");
	SpriteSetMesh(backgroundSprite, backgroundVertexList);
	SpriteSetSpriteSource(backgroundSprite, backgroundSpriteSource);
	ObjectSetTransform(backgroundTransform, backgroundGameObject);
	ObjectSetSprite(backgroundSprite, backgroundGameObject);

	blackGameObject = CreateObject("Black", ObjTag);
	blackTransform = TransformCreate(0, 0);
	AEVec2 blackScale = { 100, 100 };
	TransformSetRotation(blackTransform, 0);
	TransformSetScale(blackTransform, &blackScale);
	blackSprite = SpriteCreate("Black Sprite");
	SpriteSetMesh(blackSprite, blackVertexList);
	SpriteSetSpriteSource(blackSprite, blackSpriteSource);
	ObjectSetTransform(blackTransform, blackGameObject);
	ObjectSetSprite(blackSprite, blackGameObject);

	black1GameObject = CreateObject("Black1", ObjTag);
	black1Transform = TransformCreate(0, 0);
	AEVec2 black1Scale = { 100, 100 };
	TransformSetRotation(black1Transform, 0);
	TransformSetScale(black1Transform, &black1Scale);
	black1Sprite = SpriteCreate("Black Sprite");
	SpriteSetMesh(black1Sprite, black1VertexList);
	SpriteSetSpriteSource(black1Sprite, black1SpriteSource);
	ObjectSetTransform(black1Transform, black1GameObject);
	ObjectSetSprite(black1Sprite, black1GameObject);

	black2GameObject = CreateObject("Black2", ObjTag);
	black2Transform = TransformCreate(0, 0);
	AEVec2 black2Scale = { 100, 100 };
	TransformSetRotation(black2Transform, 0);
	TransformSetScale(black2Transform, &black2Scale);
	black2Sprite = SpriteCreate("Black2 Sprite");
	SpriteSetMesh(black2Sprite, black2VertexList);
	SpriteSetSpriteSource(black2Sprite, black2SpriteSource);
	ObjectSetTransform(black2Transform, black2GameObject);
	ObjectSetSprite(black2Sprite, black2GameObject);

	continueObject = CreateObject("Continue", ObjTag);
	sprintf_s(continueBuffer, 16, "Continue");
	continueTransform = TransformCreate(0, 0);
	TransformSetRotation(continueTransform, 0);
	PrintText(continueObject, continueBuffer, continueSprite, continueTransform);

	ObjectSetTransform(rewardTransform, rewardGameObject);
	ObjectSetSprite(rewardSprite, rewardGameObject);
	rewardGameObject = CreateObject("Continue", ObjTag);
	if (BRplacing == 1)
	{
		sprintf_s(rewardBuffer, 64, "500 Gold added to your bag");
		PlayerAddGold(500);
	}
	if (BRplacing == 2)
	{
		sprintf_s(rewardBuffer, 64, "250 Gold added to your bag");
		PlayerAddGold(250);
	}
	if (BRplacing == 3)
	{
		sprintf_s(rewardBuffer, 64, "200 Gold added to your bag");
		PlayerAddGold(200);
	}
	if (BRplacing == 4)
	{
		sprintf_s(rewardBuffer, 64, "150 Gold added to your bag");
		PlayerAddGold(150);
	}
	if (BRplacing == 5)
	{
		sprintf_s(rewardBuffer, 64, "100 Gold added to your bag");
		PlayerAddGold(100);
	}
	if (BRplacing == 6)
	{
		sprintf_s(rewardBuffer, 64, "50 Gold added to your bag");
		PlayerAddGold(50);
	}
	if (BRplacing == 7)
	{
		sprintf_s(rewardBuffer, 64, "40 Gold added to your bag");
		PlayerAddGold(40);
	}
	if (BRplacing == 8)
	{
		sprintf_s(rewardBuffer, 64, "30 Gold added to your bag");
		PlayerAddGold(30);
	}
	if (BRplacing == 9)
	{
		sprintf_s(rewardBuffer, 64, "20 Gold added to your bag");
		PlayerAddGold(20);
	}
	if (BRplacing >= 10)
	{
		sprintf_s(rewardBuffer, 64, "10 Gold added to your bag");
		PlayerAddGold(10);
	}
	rewardTransform = TransformCreate(0, 0);
	TransformSetRotation(rewardTransform, 0);
	PrintText(rewardGameObject, rewardBuffer, rewardSprite, rewardTransform);

	highlighterGameObject = CreateObject("Highlighter", ObjTag);
	highlighterTransform = TransformCreate(0, 0);
	AEVec2 highlighterScale = { 250, 250 };
	TransformSetRotation(highlighterTransform, 0);
	TransformSetScale(highlighterTransform, &highlighterScale);
	highlighterSprite = SpriteCreate("Highlighter Sprite");
	SpriteSetMesh(highlighterSprite, highlighterVertexList);
	SpriteSetSpriteSource(highlighterSprite, highlighterSpriteSource);
	ObjectSetTransform(highlighterTransform, highlighterGameObject);
	ObjectSetSprite(highlighterSprite, highlighterGameObject);
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateBREndUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	DrawObject(backgroundGameObject);
	ContinueToNextScreen();

	if (fade == 3)
	{
		if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
			GameStateManagerSetNextState(GsPhysicalTown);
	}
	if (fade < 3 && alpha1 < 0.9f)
	{
		if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
			fade = 3;
	}
}

// Free any memory associated with the Stub game state.
void GameStateBREndShutdown()
{
	FreeObject(&textGameObject);
	FreeObject(&backgroundGameObject);
	FreeObject(&blackGameObject);
	FreeObject(&black1GameObject);
	FreeObject(&black2GameObject);
	FreeObject(&rewardGameObject);
	FreeObject(&highlighterGameObject);
}

// Unload the resources associated with the Stub game state.
void GameStateBREndUnload()
{
	SpriteSourceFree(&textSpriteSource);
	AEGfxTextureUnload(textTexture);
	AEGfxMeshFree(textVertexList);
	SpriteSourceFree(&rewardSpriteSource);
	AEGfxTextureUnload(rewardTexture);
	AEGfxMeshFree(rewardVertexList);
	SpriteSourceFree(&blackSpriteSource);
	AEGfxTextureUnload(blackTexture);
	AEGfxMeshFree(blackVertexList);
	SpriteSourceFree(&black1SpriteSource);
	AEGfxTextureUnload(black1Texture);
	AEGfxMeshFree(black1VertexList);
	SpriteSourceFree(&black2SpriteSource);
	AEGfxTextureUnload(black2Texture);
	AEGfxMeshFree(black2VertexList);
	SpriteSourceFree(&continueSpriteSource);
	AEGfxTextureUnload(continueTexture);
	AEGfxMeshFree(continueVertexList);
	SpriteSourceFree(&highlighterSpriteSource);
	AEGfxTextureUnload(highlighterTexture);
	AEGfxMeshFree(highlighterVertexList);
}

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform)
{

	AEVec2 scale;
	TransformSetRotation(pTransform, 0);
	scale.x = 25;
	scale.y = 25;
	TransformSetScale(pTransform, &scale);

	pSpriteSrc = SpriteCreate("Text Sprite");
	SpriteSetMesh(pSpriteSrc, textVertexList);
	SpriteSetSpriteSource(pSpriteSrc, textSpriteSource);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}

static void ContinueToNextScreen(void)
{
	AEVec2 BlackPos = { 0 };
	AEVec2 BlackScale = { 0, 0 };
	BlackPos.x = 0;
	BlackPos.y -= WinY / 2.3f;
	BlackScale.x = 550;
	BlackScale.y = 80;
	TransformSetTranslation(blackTransform, &BlackPos);
	TransformSetScale(blackTransform, &BlackScale);
	AEVec2 Black1Pos = { 0 };
	AEVec2 Black1Scale = { 0, 0 };
	Black1Pos.x = 0;
	Black1Pos.y = -300;
	Black1Scale.x = 1100;
	Black1Scale.y = 40;
	TransformSetTranslation(black1Transform, &Black1Pos);
	TransformSetScale(black1Transform, &Black1Scale);
	AEVec2 Black2Pos = { 0 };
	AEVec2 Black2Scale = { 0, 0 };
	Black2Pos.x = 0;
	Black2Pos.y = - 350;
	Black2Scale.x = 1000;
	Black2Scale.y = 40;
	TransformSetTranslation(black2Transform, &Black2Pos);
	TransformSetScale(black2Transform, &Black2Scale);

	if (fade == 3)
	{
		alpha1 = 0.0f;
		alpha2 = 0.0f;
		alpha3 = 0.0f;
	}
	if (fade == 2)
	{
		alpha3 -= 0.01f;
		if (alpha3 <= 0)
			fade = 3;
	}
	if (fade == 1)
	{
		alpha2 -= 0.01f;
		if (alpha2 <= 0)
			fade = 2;
	}
	if (fade == 0)
	{
		alpha1 -= 0.01f;
		if (alpha1 <= 0)
			fade = 1;
	}

	AEVec2 contPos = { 0 };
	AEVec2 contScale = { 0, 0 };
	contPos.x -= 115.0f;
	contPos.y -= WinY / 2.3f;
	contScale.x = 50;
	contScale.y = 50;
	TransformSetTranslation(continueTransform, &contPos);
	TransformSetScale(continueTransform, &contScale);
	DrawObject(continueObject);

	AEVec2 highlightPos = { 0 };
	AEVec2 highlightScale = { 0, 0 };
	highlightPos.y -= WinY / 2.27f;
	highlightScale.x = 550;
	highlightScale.y = 400;
	TransformSetTranslation(highlighterTransform, &highlightPos);
	TransformSetScale(highlighterTransform, &highlightScale);
	DrawObject(highlighterGameObject);

	AEVec2 textPos = { 0 };
	AEVec2 textScale = { 0, 0 };
	textPos.x -= 435.0f;
	textPos.y -= 300.0f;
	textScale.x = 30;
	textScale.y = 30;
	TransformSetTranslation(textTransform, &textPos);
	TransformSetScale(textTransform, &textScale);
	DrawObject(textGameObject);

	AEVec2 rewardPos = { 0 };
	AEVec2 rewardScale = { 0, 0 };
	if (BRplacing <= 5)
		rewardPos.x -= 340.0f;
	else if (BRplacing > 5)
		rewardPos.x -= 320.0f;
	rewardPos.y -= 351.0f;
	rewardScale.x = 30;
	rewardScale.y = 30;
	TransformSetTranslation(rewardTransform, &rewardPos);
	TransformSetScale(rewardTransform, &rewardScale);
	DrawObject(rewardGameObject);

	SpriteSetAlpha(blackSprite, alpha3);
	SpriteSetAlpha(black1Sprite, alpha1);
	SpriteSetAlpha(black2Sprite, alpha2);
	DrawObject(blackGameObject);
	DrawObject(black1GameObject);
	DrawObject(black2GameObject);
}

// P3N15 W45 H3R3 if you can read this consider your self unique, did you know only 5% of the population can read text like this.