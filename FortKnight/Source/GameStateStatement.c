//------------------------------------------------------------------------------
//
// File Name:	GameStateStatement.c
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
#include "GameStateStatement.h"
#include "Trace.h"
#include "Input.h"
#include "Mesh.h"
#include "Objects.h"

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
static int time = 0;
static int frame = 168;

// Font Sheets
static char firstBuffer[64] = "";
static char secondBuffer[64] = "";


// Font Sprites
SpritePtr firstSprite;
SpritePtr secondSprite;

SpritePtr backgroundSprite;

// Font Transform
TransformPtr firstTransform;
TransformPtr secondTransform;

TransformPtr backgroundTransform;

// Menu Game Objects
static ObjectPtr firstGameObject;
static ObjectPtr secondGameObject;

static ObjectPtr backgroundGameObject;  // Background Object

static AEGfxVertexList *fontSheetVertexList;     // Font Sheet Vertex List
static AEGfxTexture *fontSheet;                 // Font Sheet Texture
static SpriteSourcePtr fontSheetSpriteSource;  // Font Sheet SpriteSource

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

// Load the resources associated with the Statement game state.
void GameStateStatementLoad()
{
	// Load the data for the font sheet
	fontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	fontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	fontSheetSpriteSource = SpriteSourceCreate(16, 6, fontSheet);

	// Load the data for the background
	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);
}

// Initialize the memory associated with the Statement game state.
void GameStateStatementInit()
{
	// Set the background to black
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Create the game objects for the options to select
	firstGameObject = CreateObject("FirstText", ObjTag);
	secondGameObject = CreateObject("SecondText", ObjTag);
	
	backgroundGameObject = CreateObject("Background", ObjTag);

	// Format the text for the menu items to be desplayed
	sprintf_s(firstBuffer, 64, "2D isometric medieval arena fighter");
	sprintf_s(secondBuffer, 64, "with item management and customization");

	// Create transforms for positioning the menu items
	firstTransform = TransformCreate(-370, 0);
	secondTransform = TransformCreate(-370, -50);

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

	// Attach the needed info to the GameObjects
	PrintText(firstGameObject, firstBuffer, firstSprite, firstTransform);
	PrintText(secondGameObject, secondBuffer, secondSprite, secondTransform);
}

// Update the Statement game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateStatementUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	//update and draw the background
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);

	//update time and advance frames for the background animation
	time++;
	if (time % 5 == 0)
	{
		frame--;
		if (frame <= -1)
			frame = 168;
	}

	DrawObject(firstGameObject);
	DrawObject(secondGameObject);

	if (AEInputCheckTriggered(VK_RETURN) || GetButtonDown(0, 0))
	{
		GameStateManagerSetNextState(GsMenu);
	}

	PrintBatteryInfo();

	// highlighter other scenes
	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsLevel1);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsArmorShop);
	}
	else if (AEInputCheckTriggered('3'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	else if (AEInputCheckTriggered('5'))
	{
		GameStateManagerSetNextState(GsMenu);
	}

}

// Free any memory associated with the Statement game state.
void GameStateStatementShutdown()
{
	// Free all objects.
	FreeObject(&firstGameObject);
	FreeObject(&secondGameObject);
	FreeObject(&backgroundGameObject);
}

// Unload the resources associated with the Statement game state.
void GameStateStatementUnload()
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