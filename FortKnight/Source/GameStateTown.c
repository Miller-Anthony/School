//------------------------------------------------------------------------------
//
// File Name:	GameStateTown.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "GameStateTown.h"
#include "Trace.h"
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

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
// General enumeration
static int highlighter = 0;
static int time = 0;
static int time2 = 0;
static int menuFlag = 0;
static int frame = 168;
static int state = 0;

//sounds
static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

// Font Sheets
static char fightBuffer[16] = "";
static char upgradeBuffer[16] = "";
static char optionsBuffer[16] = "";
static char saveBuffer[16] = "";
static char quitBuffer[16] = "";

// Font Sprites
SpritePtr fightSprite;
SpritePtr upgradeSprite;
SpritePtr optionsSprite;
SpritePtr saveSprite;
SpritePtr quitSprite;
SpritePtr highlighterSprite;
SpritePtr backgroundSprite;

// Font Transform
TransformPtr fightTransform;
TransformPtr upgradeTransform;
TransformPtr optionsTransform;
TransformPtr saveTransform;
TransformPtr quitTransform;
TransformPtr highlighterTransform;
TransformPtr backgroundTransform;

// Menu Game Objects
static ObjectPtr fightGameObject;
static ObjectPtr upgradeGameObject;
static ObjectPtr optionsGameObject;
static ObjectPtr saveGameObject;
static ObjectPtr quitGameObject;
static ObjectPtr highlighterGameObject;
static ObjectPtr backgroundGameObject;  // Background Object

static AEGfxVertexList *fontSheetVertexList;     // Font Sheet Vertex List
static AEGfxTexture *fontSheet;                 // Font Sheet Texture
static SpriteSourcePtr fontSheetSpriteSource;  // Font Sheet SpriteSource

static AEGfxVertexList *highlighterVertexList;     // highlighter Vertex List
static AEGfxTexture *highlighterTexture;	         // highlighter Texture
static SpriteSourcePtr highlighterSpriteSource;  // highlighter SpriteSource

static AEGfxVertexList *backgroundVertexList;     // Background Vertex List
static AEGfxTexture *backgroundTexture;			 // Background Texture
static SpriteSourcePtr backgroundSpriteSource;  // Background SpriteSource

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//need to talk to tema about moving this to somewhere for public access 
//because I am copy pasting it from Menu.c
static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Town game state.
void GameStateTownLoad()
{
	// Load the data for the font sheet
	fontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	fontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	fontSheetSpriteSource = SpriteSourceCreate(16, 6, fontSheet);

	// Load the data for the selection indecator
	highlighterVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	highlighterTexture = AEGfxTextureLoad("Assets/buttonSelectWide.png");
	highlighterSpriteSource = SpriteSourceCreate(1, 1, highlighterTexture);

	// Load the data for the background
	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);
}

// Initialize the memory associated with the Town game state.
void GameStateTownInit()
{
	// Always start at the buy option
	highlighter = 0;

	stopSong();
	playSong(2);

	// Initialize the sounds
	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);

	// Set the background to black
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Create the game objects for the options to select
	fightGameObject = CreateObject("FightText", ObjTag);
	upgradeGameObject = CreateObject("UpgradeText", ObjTag);
	optionsGameObject = CreateObject("OptionsText", ObjTag);
	saveGameObject = CreateObject("SaveText", ObjTag);
	quitGameObject = CreateObject("QuitText", ObjTag);
	highlighterGameObject = CreateObject("highlighter", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	// Format the text for the menu items to be desplayed
	sprintf_s(fightBuffer, 16, "Bounty Hunt");
	sprintf_s(upgradeBuffer, 16, "Moshpit");
	sprintf_s(optionsBuffer, 16, "Deathmatch");
	sprintf_s(saveBuffer, 16, "Back to Town");
	sprintf_s(quitBuffer, 16, "Save");

	// Create transforms for positioning the menu items
	fightTransform = TransformCreate(0, 0);
	upgradeTransform = TransformCreate(0, -50);
	optionsTransform = TransformCreate(0, -100);
	saveTransform = TransformCreate(0, -150);
	quitTransform = TransformCreate(0, -200);
	highlighterTransform = TransformCreate(85, -2.5);

	// Set the data for the backgrounds transform
	backgroundTransform = TransformCreate(0, 0);
	AEVec2 backgroundScale = { -1920, 1080 };
	TransformSetRotation(backgroundTransform, 0);
	TransformSetScale(backgroundTransform, &backgroundScale);

	// Set the backgrounds sprite
	backgroundSprite = SpriteCreate("Background sprite");
	SpriteSetMesh(backgroundSprite, backgroundVertexList);
	SpriteSetSpriteSource(backgroundSprite, backgroundSpriteSource);

	// Conect the transform and sprite to the background
	ObjectSetTransform(backgroundTransform, backgroundGameObject);
	ObjectSetSprite(backgroundSprite, backgroundGameObject);

	// Set the data for the highlighter object
	AEVec2 buttonselectScale = { 640, 256 };
	TransformSetRotation(highlighterTransform, 0);
	TransformSetScale(highlighterTransform, &buttonselectScale);

	// Set the highlighter sprite
	highlighterSprite = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(highlighterSprite, highlighterVertexList);
	SpriteSetSpriteSource(highlighterSprite, highlighterSpriteSource);

	// Connect the sprite and transform to the highlighter
	ObjectSetTransform(highlighterTransform, highlighterGameObject);
	ObjectSetSprite(highlighterSprite, highlighterGameObject);

	// Attach the needed info to the GameObjects
	PrintText(fightGameObject, fightBuffer, fightSprite, fightTransform);
	PrintText(upgradeGameObject, upgradeBuffer, upgradeSprite, upgradeTransform);
	PrintText(optionsGameObject, optionsBuffer, optionsSprite, optionsTransform);
	PrintText(saveGameObject, saveBuffer, saveSprite, saveTransform);
	PrintText(quitGameObject, quitBuffer, quitSprite, quitTransform);
}

// Update the Town game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateTownUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);
	ControllerVibrate(0, 0.0f, 0.0f);
	//update and draw the background
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);

	//update time and advance frames for the background animation
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

	DrawObject(fightGameObject);
	DrawObject(upgradeGameObject);
	DrawObject(saveGameObject);
	DrawObject(optionsGameObject);
	DrawObject(quitGameObject);
	DrawObject(highlighterGameObject);
	
	if (/*AEInputCheckTriggered(VK_DOWN) || */GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f)
	{
		if (menuFlag == 0)
		{
			SoundPlay(&optionSound, false);
			time2 = 0;
			menuFlag = 1;
			highlighter++;
		}
	}
	else if (/*AEInputCheckTriggered(VK_UP) || */GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f)
	{
		if (menuFlag == 0)
		{
			time2 = 0;
			menuFlag = 1;
			highlighter--;
			SoundPlay(&optionSound, false);
		}
	}


	if (highlighter < 0)
		highlighter = 4;
	if (highlighter > 4)
		highlighter = 0;

	if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
	{
		playSwingSound();
		if (highlighter == 0)
			GameStateManagerSetNextState(GsLevel2);
		if (highlighter == 1)
			GameStateManagerSetNextState(GsBattleRoyale);
		if (highlighter == 2)
			GameStateManagerSetNextState(GsPvP);
		if (highlighter == 3)
			GameStateManagerSetNextState(GsPhysicalTown);
		if (highlighter == 4)
			GameStateManagerSetNextState(GsSaveSelect);
	}

	AEVec2 choice0 = { 85, -2.5 };
	AEVec2 choice1 = { 85, -52.5 };
	AEVec2 choice2 = { 85, -102.5 };
	AEVec2 choice3 = { 85, -152.5 };
	AEVec2 choice4 = { 85, -202.5 };

	if (highlighter == 0)
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &choice0);
	if (highlighter == 1)
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &choice1);
	if (highlighter == 2)
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &choice2);
	if (highlighter == 3)
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &choice3);
	if (highlighter == 4)
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &choice4);

}

// Free any memory associated with the Town game state.
void GameStateTownShutdown()
{
	// Free all objects.
	FreeObject(&fightGameObject);
	FreeObject(&upgradeGameObject);
	FreeObject(&optionsGameObject);
	FreeObject(&saveGameObject);
	FreeObject(&quitGameObject);
	FreeObject(&highlighterGameObject);
	FreeObject(&backgroundGameObject);
}

// Unload the resources associated with the Town game state.
void GameStateTownUnload()
{
	// Free all sprite sources.
	SpriteSourceFree(&fontSheetSpriteSource);
	// Unload all textures.
	AEGfxTextureUnload(fontSheet);
	// Free all meshes.
	AEGfxMeshFree(fontSheetVertexList);
	
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
	SpriteSetMesh(pSpriteSrc, fontSheetVertexList);
	SpriteSetSpriteSource(pSpriteSrc, fontSheetSpriteSource);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}