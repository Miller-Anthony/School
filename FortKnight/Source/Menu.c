//------------------------------------------------------------------------------
//
// File Name:	Menu.c
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
#include "SaveSelect.h"
#include "Player.h"
#include "Menu.h"
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
extern Player *player;

static int button = 0;
static int time = 0;
static int time2 = 0;
static int frame = 168;
static int menuFlag = 0;
static int subtitleFlag = 0;
static int subtitleFrame = 0;
static int done = 0;
static int subtitleDone = 0;

// Font Sheet Buffers
static char continueBuffer[16] = "";
static char newgameBuffer[16] = "";
static char loadBuffer[16] = "";
static char optionsBuffer[16] = "";
static char creditsBuffer[16] = "";
static char quitBuffer[16] = "";
static char Buffer[256] = "";

static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;
static FMOD_SOUND* pencilSound;

// Font Sheet Sprites
SpritePtr continueSprite;
SpritePtr newgameSprite;
SpritePtr loadSprite;
SpritePtr optionsSprite;
SpritePtr creditsSprite;
SpritePtr quitSprite;

SpritePtr titleSprite;
SpritePtr subtitleSprite;

SpritePtr buttonselectSpritePtr;
SpritePtr backgroundSprite;

SpritePtr menuSprite;
TransformPtr menuTransform;
ObjectPtr menuObject;

// Font Sheet Transforms
TransformPtr continueTransform;
TransformPtr newgameTransform;
TransformPtr loadTransform;
TransformPtr optionsTransform;
TransformPtr creditsTransform;
TransformPtr quitTransform;

TransformPtr titleTransform;

TransformPtr buttonselectTransform;
TransformPtr backgroundTransform;

static AEGfxVertexList *pTitleVertexList;
static AEGfxTexture *pTitleTexture;
static SpriteSourcePtr pTitleSpriteSource;

static AEGfxVertexList *psubTitleVertexList;
static AEGfxTexture *psubTitleTexture;
static SpriteSourcePtr psubTitleSpriteSource;
static TransformPtr subtitleTransform;

static AEGfxVertexList *pFontSheetVertexList; // Font Sheet Vertex List
static AEGfxTexture *pFontSheet; // Font Sheet Texture
static SpriteSourcePtr pFontSheetSprite; // Font Sheet Sprite

static AEGfxVertexList *buttonselectVertexList;
static AEGfxTexture *buttonselect;
static SpriteSourcePtr buttonselectSprite;

static AEGfxVertexList *backgroundVertexList;
static AEGfxTexture *backgroundTexture;
static SpriteSourcePtr backgroundSpriteSource;

static AEGfxVertexList *batteryVertexList;
static AEGfxTexture *batteryTexture;
static SpriteSourcePtr batterySpriteSource;
static SpritePtr batterySprite;
TransformPtr ButtonTransform;
ObjectPtr batteryObject;

// Font Sheet Game Objects
static ObjectPtr continueGameObject;
static ObjectPtr newgameGameObject;
static ObjectPtr loadGameObject;
static ObjectPtr optionsGameObject;
static ObjectPtr creditsGameObject;
static ObjectPtr quitGameObject;

static ObjectPtr titleGameObject;

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
void MenuLoad()
{
	pFontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pFontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	pFontSheetSprite = SpriteSourceCreate(16, 6, pFontSheet);

	buttonselectVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	buttonselect = AEGfxTextureLoad("Assets/buttonSelect.png");
	buttonselectSprite = SpriteSourceCreate(1, 1, buttonselect);

	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);

	pTitleVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "MeshTitle");
	pTitleTexture = AEGfxTextureLoad("Assets/Title.png");
	pTitleSpriteSource = SpriteSourceCreate(1, 1, pTitleTexture);

	psubTitleVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 2, "MeshSubtitle");
	psubTitleTexture = AEGfxTextureLoad("Assets/subtitle.png");
	psubTitleSpriteSource = SpriteSourceCreate(2, 2, psubTitleTexture);

	batteryVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "MeshBattery");
	batteryTexture = AEGfxTextureLoad("Assets/Battery.png");
	batterySpriteSource = SpriteSourceCreate(2, 3, batteryTexture);
}

// Initialize the memory associated with the Level1 game state.
void MenuInit()
{
	button = 0;

	stopSong();
	playSong(1);

	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);
	SoundInit("./Assets/Sound/pencilScratch.mp3", FMOD_LOOP_OFF, &pencilSound);
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	continueGameObject = CreateObject("ContinueText", ObjTag);
	newgameGameObject = CreateObject("NewGameText", ObjTag);
	loadGameObject = CreateObject("LoadText", ObjTag);
	optionsGameObject = CreateObject("OptionsText", ObjTag);
	creditsGameObject = CreateObject("CreditsText", ObjTag);
	quitGameObject = CreateObject("QuitText", ObjTag);

	menuObject = CreateObject("MenuText", ObjTag);

	titleGameObject = CreateObject("TitleLogo", ObjTag);

	buttonselectGameObject = CreateObject("buttonSelect", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	sprintf_s(continueBuffer, 16, "Continue");
	sprintf_s(newgameBuffer, 16, "New Game");
	sprintf_s(loadBuffer, 16, "Save");
	sprintf_s(optionsBuffer, 16, "Options");
	sprintf_s(creditsBuffer, 16, "Credits");
	sprintf_s(quitBuffer, 16, "Quit");

	continueTransform = TransformCreate(-800, 0);
	newgameTransform = TransformCreate(-800, -50);
	loadTransform = TransformCreate(-800, -100);
	optionsTransform = TransformCreate(-800, -150);
	creditsTransform = TransformCreate(-800, -200);
	quitTransform = TransformCreate(-800, -250);
	menuTransform = TransformCreate(-800, -450);

	titleTransform = TransformCreate(-500, 200);
	AEVec2 titleScale = {688, 341};
	TransformSetRotation(titleTransform, 0);
	TransformSetScale(titleTransform, &titleScale);
	titleSprite = SpriteCreate("Title Sprite");
	SpriteSetMesh(titleSprite, pTitleVertexList);
	SpriteSetSpriteSource(titleSprite, pTitleSpriteSource);
	ObjectSetTransform(titleTransform, titleGameObject);
	ObjectSetSprite(titleSprite, titleGameObject);

	subtitleTransform = TransformCreate(-475, 125);
	AEVec2 subtitleScale = { 1020, 576 };
	TransformSetRotation(subtitleTransform, 0);
	TransformSetScale(subtitleTransform, &subtitleScale);
	subtitleSprite = SpriteCreate("Subtitle Sprite");
	SpriteSetMesh(subtitleSprite, psubTitleVertexList);
	SpriteSetSpriteSource(subtitleSprite, psubTitleSpriteSource);
	SpriteSetFrame(subtitleSprite, 0);

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

	buttonselectTransform = TransformCreate(75, -2.5);

	AEVec2 buttonselectScale;
	TransformSetRotation(buttonselectTransform, 0);
	buttonselectScale.x = 312.5;
	buttonselectScale.y = 250;
	TransformSetScale(buttonselectTransform, &buttonselectScale);

	buttonselectSpritePtr = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(buttonselectSpritePtr, buttonselectVertexList);
	SpriteSetSpriteSource(buttonselectSpritePtr, buttonselectSprite);

	ObjectSetTransform(buttonselectTransform, buttonselectGameObject);
	ObjectSetSprite(buttonselectSpritePtr, buttonselectGameObject);

	PrintText(continueGameObject, continueBuffer, continueSprite, continueTransform);
	PrintText(newgameGameObject, newgameBuffer, newgameSprite, newgameTransform);
	PrintText(loadGameObject, loadBuffer, loadSprite, loadTransform);
	PrintText(optionsGameObject, optionsBuffer, optionsSprite, optionsTransform);
	PrintText(creditsGameObject, creditsBuffer, creditsSprite, creditsTransform);
	PrintText(quitGameObject, quitBuffer, quitSprite, quitTransform);

	batterySprite = SpriteCreate("Battery");
	SpriteSetMesh(batterySprite, batteryVertexList);
	SpriteSetSpriteSource(batterySprite, batterySpriteSource);
	AEVec2 batteryScale = { 300, 300 };
	ButtonTransform = TransformCreate(850, -450);
	TransformSetScale(ButtonTransform, &batteryScale);
	SpriteSetAlpha(batterySprite, 1.0f);
	batteryObject = CreateObject("Battery", ObjTag);
	ObjectSetTransform(ButtonTransform, batteryObject);
	ObjectSetSprite(batterySprite, batteryObject);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void MenuUpdate(float dt)
{
	//SoundModuleUpdate();
	UNREFERENCED_PARAMETER(dt);
	SpriteSetFrame(subtitleSprite, subtitleFrame);
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);
	DrawObject(titleGameObject);
	SpriteDraw(subtitleSprite, subtitleTransform);

	subtitleFlag++;
	if (subtitleFlag % 30 == 0)
	{
		if (subtitleDone == 0)
		{
			SoundPlay(&pencilSound, false);
			subtitleDone = 1;
		}
		subtitleFrame++;
		if (subtitleFrame > 3)
		{
			subtitleFrame = 3;
			done = 1;
		}
	}

	ControllerVibrate(0, 0.0f, 0.0f);

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

	if (done)
	{
		DrawObject(continueGameObject);
		DrawObject(newgameGameObject);
		DrawObject(loadGameObject);
		DrawObject(optionsGameObject);
		DrawObject(creditsGameObject);
		DrawObject(quitGameObject);
		DrawObject(buttonselectGameObject);
		DrawObject(menuObject);
		DrawObject(batteryObject);
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

	if (done)
	{
		if (/*AEInputCheckTriggered(VK_DOWN) || */GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f)
		{
			if (menuFlag == 0)
			{
				SoundPlay(&optionSound, false);
				time2 = 0;
				menuFlag = 1;
				button++;
			}
		}
		else if (/*AEInputCheckTriggered(VK_UP) || */GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f)
		{
			if (menuFlag == 0)
			{
				SoundPlay(&optionSound, false);
				time2 = 0;
				menuFlag = 1;
				button--;
			}
		}
	}

	if (button < 0)
		button = 5;
	if (button > 5)
		button = 0;

	if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && done)
	{
		playSwingSound();

		if (button == 0)
		{
			SaveSelectContinue();
			GameStateManagerSetNextState(GsPhysicalTown);
		}
		if (button == 1)
		{
			HumanPtr human = HumanGetHuman(player, NULL);
			HumanSetWeapon(human, 2);
			HumanSetArmors(human, 5, 6, 7);
			GameStateManagerSetNextState(GsTutorial);
		}
		if (button == 2)
		{
			GameStateManagerSetNextState(GsSaveSelect);
		}
		if (button == 3)
			GameStateManagerSetNextState(GsSettings);
		if (button == 4)
		{
			GameStateManagerSetNextState(GsCredits);
		}
		if (button == 5)
			GameStateManagerSetNextState(GsQuit);
	}

	AEVec2 choice0 = { -740, -2.5 };
	AEVec2 choice1 = { -740, -52.5 };
	AEVec2 choice2 = { -740, -102.5 };
	AEVec2 choice3 = { -740, -152.5 };
	AEVec2 choice4 = { -740, -202.5 };
	AEVec2 choice5 = { -740, -252.5 };

	if (button == 0)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice0);
		sprintf_s(Buffer, 256, "Continue from latest save");
	}
	if (button == 1)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice1);
		sprintf_s(Buffer, 256, "Start a new game");

	}
	if (button == 2)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice2);
		sprintf_s(Buffer, 256, "Load from a previously made save file");

	}
	if (button == 3)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice3);
		sprintf_s(Buffer, 256, "Change settings");

	}
	if (button == 4)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice4);
		sprintf_s(Buffer, 256, "View Credits");

	}
	if (button == 5)
	{
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice5);
		sprintf_s(Buffer, 256, "Quit to Desktop");

	}

	PrintText(menuObject, Buffer, menuSprite, menuTransform);
	//PrintBatteryInfo();
}

// Shutdown any memory associated with the Level1 game state.
void MenuShutdown()
{
	FreeObject(&continueGameObject);
	FreeObject(&newgameGameObject);
	FreeObject(&loadGameObject);
	FreeObject(&optionsGameObject);
	FreeObject(&creditsGameObject);
	FreeObject(&quitGameObject);
	FreeObject(&titleGameObject);
	FreeObject(&buttonselectGameObject);
	FreeObject(&backgroundGameObject);
	FreeObject(&batteryObject);
	FreeObject(&menuObject);
}

// Unload the resources associated with the Level1 game state.
void MenuUnload()
{
	SpriteSourceFree(&pFontSheetSprite);
	SpriteSourceFree(&pTitleSpriteSource);
	SpriteSourceFree(&psubTitleSpriteSource);
	SpriteSourceFree(&buttonselectSprite);
	SpriteSourceFree(&backgroundSpriteSource);
	SpriteSourceFree(&batterySpriteSource);

	AEGfxMeshFree(pFontSheetVertexList);
	AEGfxMeshFree(pTitleVertexList);
	AEGfxMeshFree(psubTitleVertexList);
	AEGfxMeshFree(buttonselectVertexList);
	AEGfxMeshFree(backgroundVertexList);
	AEGfxMeshFree(batteryVertexList);

	AEGfxTextureUnload(pFontSheet);
	AEGfxTextureUnload(pTitleTexture);
	AEGfxTextureUnload(psubTitleTexture);
	AEGfxTextureUnload(buttonselect);
	AEGfxTextureUnload(backgroundTexture);
	AEGfxTextureUnload(batteryTexture);
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