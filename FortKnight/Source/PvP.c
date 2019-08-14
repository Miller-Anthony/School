//------------------------------------------------------------------------------
//
// File Name:	PvP.c
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
#include "Objects.h"
#include "Sound.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Menu.h"
#include "Input.h"

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
static int button = 0;
static int time = 0;
static int time2 = 0;
static int time3 = 0;
static int frame = 168;
static int menuFlag = 0;

int ready1 = 0;
int ready2 = 0;

// Font Sheet Buffers
static char continueBuffer[16] = "";
static char newgameBuffer[16] = "";
static char quitBuffer[256] = "";

static FMOD_SOUND* mainMenuSound;
static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

// Font Sheet Sprites
SpritePtr continueSprite;
SpritePtr newgameSprite;
SpritePtr loadSprite;
SpritePtr optionsSprite;
SpritePtr creditsSprite;
SpritePtr quitSprite;

SpritePtr titleSprite;

SpritePtr buttonselectSpritePtr;
SpritePtr buttonselect2SpritePtr;
SpritePtr backgroundSprite;

SpritePtr menuSprite;
TransformPtr menuTransform;
ObjectPtr menuObject;

// Font Sheet Transforms
TransformPtr continueTransform;
TransformPtr newgameTransform;
TransformPtr quitTransform;


TransformPtr buttonselectTransform;
TransformPtr buttonselect2Transform;
TransformPtr backgroundTransform;

static AEGfxVertexList *pFontSheetVertexList; // Font Sheet Vertex List
static AEGfxTexture *pFontSheet;			  // Font Sheet Texture
static SpriteSourcePtr pFontSheetSprite;	  // Font Sheet Sprite

static AEGfxVertexList *buttonselectVertexList;
static AEGfxTexture *buttonselect;
static SpriteSourcePtr buttonselectSprite;
static SpriteSourcePtr buttonselect2Sprite;

static AEGfxVertexList *backgroundVertexList;
static AEGfxTexture *backgroundTexture;
static SpriteSourcePtr backgroundSpriteSource;

static AEGfxVertexList *batteryVertexList;
static AEGfxTexture *batteryTexture;
static SpriteSourcePtr batterySpriteSource;
static SpriteSourcePtr battery2SpriteSource;
static SpritePtr batterySprite;
static SpritePtr battery2Sprite;
TransformPtr ButtonTransform;
ObjectPtr batteryObject;
TransformPtr Button2Transform;
ObjectPtr battery2Object;

// Font Sheet Game Objects
static ObjectPtr continueGameObject;
static ObjectPtr newgameGameObject;
static ObjectPtr quitGameObject;

static ObjectPtr titleGameObject;

static ObjectPtr buttonselectGameObject;
static ObjectPtr buttonselect2GameObject;
static ObjectPtr backgroundGameObject;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void PVPLoad()
{
	pFontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pFontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	pFontSheetSprite = SpriteSourceCreate(16, 6, pFontSheet);

	buttonselectVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f / 2, "Mesh 1x1");
	buttonselect = AEGfxTextureLoad("Assets/Controller.png");
	buttonselectSprite = SpriteSourceCreate(1, 2, buttonselect);

	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);

	batteryVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "MeshBattery");
	batteryTexture = AEGfxTextureLoad("Assets/Battery.png");
	batterySpriteSource = SpriteSourceCreate(2, 3, batteryTexture);
}

// Initialize the memory associated with the Level1 game state.
void PVPInit()
{
	ready1 = 0;
	ready2 = 0;
	button = 0;
	SoundInit("./Assets/Sound/thePeasant.wav", FMOD_LOOP_NORMAL, &mainMenuSound);
	SoundPlay(&mainMenuSound, false);
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	continueGameObject = CreateObject("ContinueText", ObjTag);
	newgameGameObject = CreateObject("NewGameText", ObjTag);
	quitGameObject = CreateObject("QuitText", ObjTag);

	menuObject = CreateObject("MenuText", ObjTag);

	titleGameObject = CreateObject("TitleLogo", ObjTag);

	buttonselectGameObject = CreateObject("buttonSelect", ObjTag);
	buttonselect2GameObject = CreateObject("buttonSelect2", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	sprintf_s(continueBuffer, 16, "Player 1");
	sprintf_s(newgameBuffer, 16, "Player 2");
	sprintf_s(quitBuffer, 256, "Press A on both controllers to begin the Battle!");

	continueTransform = TransformCreate(-590, 180);
	newgameTransform = TransformCreate(410, 180);
	quitTransform = TransformCreate(-600, -350);

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

	buttonselectTransform = TransformCreate(500, 0);
	buttonselect2Transform = TransformCreate(-500, 0);

	AEVec2 buttonselectScale;
	TransformSetRotation(buttonselectTransform, 0);
	buttonselectScale.x = 512;
	buttonselectScale.y = 512;
	TransformSetScale(buttonselectTransform, &buttonselectScale);
	TransformSetScale(buttonselect2Transform, &buttonselectScale);

	buttonselectSpritePtr = SpriteCreate("MenuText Sprite");
	buttonselect2SpritePtr = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(buttonselectSpritePtr, buttonselectVertexList);
	SpriteSetMesh(buttonselect2SpritePtr, buttonselectVertexList);
	SpriteSetSpriteSource(buttonselectSpritePtr, buttonselectSprite);
	SpriteSetSpriteSource(buttonselect2SpritePtr, buttonselectSprite);

	ObjectSetTransform(buttonselectTransform, buttonselectGameObject);
	ObjectSetSprite(buttonselectSpritePtr, buttonselectGameObject);

	ObjectSetTransform(buttonselect2Transform, buttonselect2GameObject);
	ObjectSetSprite(buttonselect2SpritePtr, buttonselect2GameObject);

	PrintText(continueGameObject, continueBuffer, continueSprite, continueTransform);
	PrintText(newgameGameObject, newgameBuffer, newgameSprite, newgameTransform);
	PrintText(quitGameObject, quitBuffer, quitSprite, quitTransform);

	batterySprite = SpriteCreate("Battery");
	SpriteSetMesh(batterySprite, batteryVertexList);
	SpriteSetSpriteSource(batterySprite, batterySpriteSource);
	AEVec2 batteryScale = { 300, 300 };
	ButtonTransform = TransformCreate(-500, -200);
	TransformSetScale(ButtonTransform, &batteryScale);
	SpriteSetAlpha(batterySprite, 1.0f);
	batteryObject = CreateObject("Battery", ObjTag);
	ObjectSetTransform(ButtonTransform, batteryObject);
	ObjectSetSprite(batterySprite, batteryObject);

	battery2Sprite = SpriteCreate("Battery2");
	SpriteSetMesh(battery2Sprite, batteryVertexList);
	SpriteSetSpriteSource(battery2Sprite, batterySpriteSource);
	AEVec2 battery2Scale = { 300, 300 };
	Button2Transform = TransformCreate(500, -200);
	TransformSetScale(Button2Transform, &battery2Scale);
	SpriteSetAlpha(battery2Sprite, 1.0f);
	battery2Object = CreateObject("Battery2", ObjTag);
	ObjectSetTransform(Button2Transform, battery2Object);
	ObjectSetSprite(battery2Sprite, battery2Object);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void PVPUpdate(float dt)
{
	//SoundModuleUpdate();
	UNREFERENCED_PARAMETER(dt);
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);

	ControllerVibrate(0, 0.0f, 0.0f);

	if(ControllerisConnected(0))
		InputUpdate(0);

	if (GetButtonDown(0, 0))
	{
		SpriteSetFrame(ObjectGetSprite(buttonselect2GameObject), 1);
		ready1 = 1;
	}

	if (GetButtonDown(0, 1))
	{
		if (ready1)
		{
			SpriteSetFrame(ObjectGetSprite(buttonselect2GameObject), 0);
			ready1 = 0;
		}
		else
			GameStateManagerSetNextState(GsTown);
	}
	int batteryStat = BatteryInfo(0);

	if (batteryStat == 2 || batteryStat == 3)
		SpriteSetFrame(batterySprite, 0);
	else if (batteryStat == 4)
		SpriteSetFrame(batterySprite, 1);
	else if (batteryStat == 5)
		SpriteSetFrame(batterySprite, 2);
	else
		SpriteSetFrame(batterySprite, 3);

	if (ControllerisConnected(1))
		InputUpdate(1);

	if (GetButtonDown(1, 0))
	{
		SpriteSetFrame(ObjectGetSprite(buttonselectGameObject), 1);
		ready2 = 1;
	}
	if (GetButtonDown(1, 1))
	{
		if (ready2)
		{
			SpriteSetFrame(ObjectGetSprite(buttonselectGameObject), 0);
			ready2 = 0;
		}
		else
			GameStateManagerSetNextState(GsTown);
	}

	int battery2Stat = BatteryInfo(1);

	if (battery2Stat == 2 || battery2Stat == 3)
		SpriteSetFrame(battery2Sprite, 0);
	else if (battery2Stat == 4)
		SpriteSetFrame(battery2Sprite, 1);
	else if (battery2Stat == 5)
		SpriteSetFrame(battery2Sprite, 2);
	else
		SpriteSetFrame(battery2Sprite, 3);

	if (ready1 && ready2)
	{
		AEVec2 translation = { -250, -350 };
		TransformSetTranslation(ObjectGetTransform(quitGameObject), &translation);
		time3++;

		if(time3 <= 60)
			sprintf_s(quitBuffer, 256, "Starting Game in 3...");
		else if(time3 <= 120)
			sprintf_s(quitBuffer, 256, "Starting Game in 2...");
		else if (time3 <= 180)
			sprintf_s(quitBuffer, 256, "Starting Game in 1...");
		else
		{
			sprintf_s(quitBuffer, 256, "Game Started!");
			GameStateManagerSetNextState(GsDeathmatch);
		}
	}
	else
	{
		AEVec2 translation = { -600, -350 };
		TransformSetTranslation(ObjectGetTransform(quitGameObject), &translation);
		time3 = 0;
		sprintf_s(quitBuffer, 256, "Press A on both controllers to begin the Battle!");
	}

	time++;
	time2++;
	if (time % 5 == 0)
	{
		frame--;
		if (frame <= -1)
			frame = 168;
	}
	if (time2 % 12 == 0)
	{
		menuFlag = 0;
	}

	DrawObject(continueGameObject);
	DrawObject(newgameGameObject);
	DrawObject(quitGameObject);
	DrawObject(buttonselectGameObject);
	DrawObject(buttonselect2GameObject);
	DrawObject(menuObject);
	DrawObject(batteryObject);
	DrawObject(battery2Object);
	//PrintBatteryInfo();
}

// Shutdown any memory associated with the Level1 game state.
void PVPShutdown()
{
	FreeObject(&continueGameObject);
}

// Unload the resources associated with the Level1 game state.
void PVPUnload()
{
	SoundFree(&mainMenuSound);
	SpriteSourceFree(&pFontSheetSprite);
	AEGfxMeshFree(pFontSheetVertexList);
	AEGfxTextureUnload(pFontSheet);

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