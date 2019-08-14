//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel2.c
// Author(s):	Erich Atwell, Brayan Lopez, Akshat Madan
// Project:		Knightmare
// Course:		CS230S19-A
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "GameStateLevel2.h"
#include "GameStateLevel1.h"    //Bosses enum
#include "Trace.h"
#include "Player.h"
#include "Input.h"
#include "Mesh.h"
#include "Objects.h"
#include "Sound.h"
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

Bosses boss; //tells level 1 which boss to spawn

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------



static int button = 0;
static int flag = 0;

enum Prog pTemp = Start;
static enum Unlock uTemp = unlock1;

static int count = 0;
static int highlight = 0;
static float WinX;
static float WinY;
static float backX;
static float backY;
static float backX2;
static float backY2;

static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

static char backBuffer[16] = "";

AEVec2 backPos = { 0, 0 };
AEVec2 nopePos = { 5000, -2.5 };

SpritePtr backSprite;
SpritePtr highlighterSprite;
SpritePtr backgroundSprite;

TransformPtr backTransform;
TransformPtr highlighterTransform;
TransformPtr backgroundTransform;

static ObjectPtr backGameObject;
static ObjectPtr highlighterGameObject;
static ObjectPtr backgroundGameObject;

static AEGfxVertexList *fontSheetVertexList;     
static AEGfxTexture *fontSheet;                 
static SpriteSourcePtr fontSheetSpriteSource;  

static AEGfxVertexList *highlighterVertexList;   
static AEGfxTexture *highlighterTexture;	       
static SpriteSourcePtr highlighterSpriteSource; 

static AEGfxVertexList *backgroundVertexList;    
static AEGfxTexture *backgroundTexture;			 
static SpriteSourcePtr backgroundSpriteSource;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level2 game state.
void GameStateLevel2Load()
{
	// Load the data for the font sheet
	fontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	fontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	fontSheetSpriteSource = SpriteSourceCreate(16, 6, fontSheet);

	// Load the data for the selection indecator
	highlighterVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	highlighterTexture = AEGfxTextureLoad("Assets/buttonSelect.png");
	highlighterSpriteSource = SpriteSourceCreate(1, 1, highlighterTexture);

	// Load the data for the background
	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 3, 1.0f / 3, "Mesh 3x3");;
	backgroundTexture = AEGfxTextureLoad("Assets/Select.png");
	backgroundSpriteSource = SpriteSourceCreate(3, 3, backgroundTexture);
}

	// Initialize the memory associated with the Level2 game state.
void GameStateLevel2Init()
{
	highlight = pTemp + 1;
	WinX = AEGfxGetWinMaxX() * 2;
	WinY = AEGfxGetWinMaxY() * 2;
	backX = -WinX / 2.5f;
	backX2 = -WinX / 2.35f;
	backY = -WinY / 2.7f;
	backY2 = -WinY / 2.72f;
	backPos.x = backX;
	backPos.y = backY;

	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);

	AEGfxSetBackgroundColor(1.0f, 1.0f, 1.0f);

	backGameObject = CreateObject("BackText", ObjTag);
	highlighterGameObject = CreateObject("Highlighter", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	sprintf_s(backBuffer, 16, "Back");

	backTransform = TransformCreate(backX2, backY2);
	highlighterTransform = TransformCreate(backX, backY);

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

	AEVec2 buttonselectScale = { 250, 250 };
	TransformSetRotation(highlighterTransform, 0);
	TransformSetScale(highlighterTransform, &buttonselectScale);

	highlighterSprite = SpriteCreate("Highlighter Sprite");
	SpriteSetMesh(highlighterSprite, highlighterVertexList);
	SpriteSetSpriteSource(highlighterSprite, highlighterSpriteSource);

	ObjectSetTransform(highlighterTransform, highlighterGameObject);
	ObjectSetSprite(highlighterSprite, highlighterGameObject);

	PrintText(backGameObject, backBuffer, backSprite, backTransform);
}

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel2Update(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	flag++;

	if (flag % 12 == 0)
	{
		button = 0;
	}

	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), count);
	DrawObject(backgroundGameObject);
	DrawObject(highlighterGameObject);
	DrawObject(backGameObject);

	if ((/*AEInputCheckTriggered(VK_LEFT) || */GetDpadButton(3) || GetJoystickX(SIDE_L) <= -0.25f) && button == 0)
	{
		highlight--;
		button = 1;
		SoundPlay(&optionSound, false);
		flag = 0;
	}
	else if ((/*AEInputCheckTriggered(VK_RIGHT) || */GetDpadButton(1) || GetJoystickX(SIDE_L) >= 0.25f) && button == 0)
	{
		highlight++;
		button = 1;
		SoundPlay(&optionSound, false);
		flag = 0;
	}

	if (highlight > pTemp + uTemp)
		highlight = pTemp;
	if (highlight < pTemp)
		highlight = pTemp + uTemp;

	if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
	{
		playSwingSound();
		if (pTemp == Start)
		{
			if (highlight == 0)
				GameStateManagerSetNextState(GsTown);
      if (highlight == 1)
      {
          boss = SerScatterfoot;
          GameStateManagerSetNextState(GsLevel1);
      }
		}
		if (pTemp == Secnd)
		{
			if (highlight == 2)
				GameStateManagerSetNextState(GsTown);
      if (highlight == 3)
      {
          boss = SerScatterfoot;
          GameStateManagerSetNextState(GsLevel1);
      }
      if (highlight == 4)
      {
          boss = BaronDeEvidance;
          GameStateManagerSetNextState(GsLevel1);
      }
		}
		if (pTemp == Third)
		{
			if (highlight == 5)
				GameStateManagerSetNextState(GsTown);
      if (highlight == 6)
      {
          boss = SerScatterfoot;
          GameStateManagerSetNextState(GsLevel1);
      }
      if (highlight == 7)
      {
          boss = BaronDeEvidance;
          GameStateManagerSetNextState(GsLevel1);
      }
      if (highlight == 8)
      {
          boss = SVEN;
          GameStateManagerSetNextState(GsLevel1);
      }
		}
	}

	if (highlight == 0)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &backPos);
		count = 0;
	}
	if (highlight == 1)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 1;
	}
	if (highlight == 2)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &backPos);
		count = 2;
	}
	if (highlight == 3)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 3;
	}
	if (highlight == 4)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 4;
	}
	if (highlight == 5)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &backPos);
		count = 5;
	}
	if (highlight == 6)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 6;
	}
	if (highlight == 7)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 7;
	}
	if (highlight == 8)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &nopePos);
		count = 8;
	}
}

// Shutdown any memory associated with the Level2 game state.
void GameStateLevel2Shutdown()
{
	FreeObject(&backGameObject);
	FreeObject(&highlighterGameObject);
	FreeObject(&backgroundGameObject);
}

// Unload the resources associated with the Level2 game state.
void GameStateLevel2Unload()
{
	SpriteSourceFree(&fontSheetSpriteSource);
	AEGfxTextureUnload(fontSheet);
	AEGfxMeshFree(fontSheetVertexList);
}

void SetSelect()
{
	if (pTemp == Third)
		return;
	else
	{
		if (pTemp == Start)
		{
			pTemp = Secnd;
			uTemp = unlock2;
			return;
		}
		if (pTemp == Secnd)
		{
			pTemp = Third;
			uTemp = unlock3;
			return;
		}
	}
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

	pSpriteSrc = SpriteCreate("Highlighter Sprite");
	SpriteSetMesh(pSpriteSrc, fontSheetVertexList);
	SpriteSetSpriteSource(pSpriteSrc, fontSheetSpriteSource);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}