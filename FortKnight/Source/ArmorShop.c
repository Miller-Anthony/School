//------------------------------------------------------------------------------
//
// File Name:	ArmorShop.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "ArmorShop.h"
#include "ItemData.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Mesh.h"
#include "Player.h"
#include "Objects.h"
#include "InventoryWorn.h"
#include "Sound.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
extern bool isPaused;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// General enumeration
static int highlighter = 0;
static int time = 0;
static int time2 = 0;
static int menuFlag = 0;
static int frame = 168;

//sounds
static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

// Font Sheets
static char backBuffer[16] = "";
static char curHeadBuffer[16] = "";
static char curBodyBuffer[16] = "";
static char curLegsBuffer[16] = "";
static char curWeaponBuffer[16] = "";
static char nextHeadBuffer[16] = "";
static char nextBodyBuffer[16] = "";
static char nextLegsBuffer[16] = "";
static char nextWeaponBuffer[16] = "";
static char costHeadBuffer[16] = "";
static char costBodyBuffer[16] = "";
static char costLegsBuffer[16] = "";
static char costWeaponBuffer[16] = "";
static char goldBuffer[16] = "";

// Font Sprites
SpritePtr backSprite;
SpritePtr arrowSprite;
SpritePtr curHeadSprite;
SpritePtr curBodySprite;
SpritePtr curLegsSprite;
SpritePtr curWeaponSprite;
SpritePtr nextHeadSprite;
SpritePtr nextBodySprite;
SpritePtr nextLegsSprite;
SpritePtr nextWeaponSprite;
SpritePtr costHeadSprite;
SpritePtr costBodySprite;
SpritePtr costLegsSprite;
SpritePtr costWeaponSprite;
SpritePtr goldSprite;
SpritePtr highlighterSprite;
SpritePtr backgroundSprite;

// Font Transform
TransformPtr backTransform;
TransformPtr arrowTransform;
TransformPtr curHeadTransform;
TransformPtr curBodyTransform;
TransformPtr curLegsTransform;
TransformPtr curWeaponTransform;
TransformPtr nextHeadTransform;
TransformPtr nextBodyTransform;
TransformPtr nextLegsTransform;
TransformPtr nextWeaponTransform;
TransformPtr costHeadTransform;
TransformPtr costBodyTransform;
TransformPtr costLegsTransform;
TransformPtr costWeaponTransform;
TransformPtr goldTransform;
TransformPtr highlighterTransform;
TransformPtr backgroundTransform;

// Menu Game Objects
static ObjectPtr backGameObject;
static ObjectPtr arrowGameObject;
static ObjectPtr curHeadGameObject;
static ObjectPtr curBodyGameObject;
static ObjectPtr curLegsGameObject;
static ObjectPtr curWeaponGameObject;
static ObjectPtr nextHeadGameObject;
static ObjectPtr nextBodyGameObject;
static ObjectPtr nextLegsGameObject;
static ObjectPtr nextWeaponGameObject;
static ObjectPtr costHeadGameObject;
static ObjectPtr costBodyGameObject;
static ObjectPtr costLegsGameObject;
static ObjectPtr costWeaponGameObject;
static ObjectPtr goldGameObject;
static ObjectPtr highlighterGameObject;
static ObjectPtr backgroundGameObject;  // Background Object

static AEGfxVertexList *fontSheetVertexList;     // Font Sheet Vertex List
static AEGfxTexture *fontSheet;                 // Font Sheet Texture
static SpriteSourcePtr fontSheetSpriteSource;  // Font Sheet SpriteSource

static AEGfxVertexList *highlighterVertexList;     // highlighter Vertex List
static AEGfxTexture *highlighterTexture;	      // highlighter Texture
static SpriteSourcePtr highlighterSpriteSource;  // highlighter SpriteSource

static AEGfxVertexList *backgroundVertexList;     // Background Vertex List
static AEGfxTexture *backgroundTexture;			 // Background Texture
static SpriteSourcePtr backgroundSpriteSource;  // Background SpriteSource

static AEGfxVertexList *arrowVertexList;     // Arrow Vertex List
static AEGfxTexture *arrowTexture;		    // Texture for the arrow sprite
static SpriteSourcePtr arrowSpriteSource;  // Arrow SpriteSource

extern bool isPaused; //need to set this to false for this state so the player will show

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//need to talk to tema about moving this to somewhere for public access 
//because I am copy pasting it from Menu.c
static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);

	//menu for buying new items
static void BuyMenu();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ArmorShopLoad()
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

	// Load data for the arrow texture
	arrowVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	arrowTexture = AEGfxTextureLoad("Assets/Right Arrow ver2.png");
	arrowSpriteSource = SpriteSourceCreate(1, 1, arrowTexture);

  //load data for damage popups to display
  InitDamagePopupDrawer();
}

// Initialize the ...
void ArmorShopInit()
{
    //pause so player cant move even with speed boosts from equipped armors
    isPaused = false;

    HumanSetBool(PlayerGetHuman(), 0, 0, 0, 0, 0, 0);
    HumanSetNextState(PlayerGetHuman(), HSidle);

	// Always start at the buy option
	highlighter = 0;

	// Initialize the sounds
	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);


	// Set the background to black
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Create the game objects for the options to select
	backGameObject = CreateObject("BackText", ObjTag);
	arrowGameObject = CreateObject("Arrow", ObjTag);
	curHeadGameObject = CreateObject("CurHeadText", ObjTag);
	curBodyGameObject = CreateObject("CurBodyText", ObjTag);
	curLegsGameObject = CreateObject("CurLegsText", ObjTag);
	curWeaponGameObject = CreateObject("CurWeaponText", ObjTag);
	nextHeadGameObject = CreateObject("NextHeadText", ObjTag);
	nextBodyGameObject = CreateObject("NextBodyText", ObjTag);
	nextLegsGameObject = CreateObject("NextLegsText", ObjTag);
	nextWeaponGameObject = CreateObject("NextWeaponText", ObjTag);
	costHeadGameObject = CreateObject("CostHeadText", ObjTag);
	costBodyGameObject = CreateObject("CostBodyText", ObjTag);
	costLegsGameObject = CreateObject("CostLegsText", ObjTag);
	costWeaponGameObject = CreateObject("CostWeaponText", ObjTag);
	goldGameObject = CreateObject("GoldText", ObjTag);
	highlighterGameObject = CreateObject("highlighter", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	// Format the text for the menu items to be desplayed
	sprintf_s(backBuffer, 16, "Back");
	sprintf_s(curHeadBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head)), NULL, NULL)));
	sprintf_s(curBodyBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body)), NULL, NULL)));
	sprintf_s(curLegsBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs)), NULL, NULL)));
	sprintf_s(curWeaponBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon)), NULL, NULL)));
	
	if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head) < SteelHelm)
	{
		sprintf_s(nextHeadBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head) + 3), NULL, NULL)));
		sprintf_s(costHeadBuffer, 16, "Cost: %d", ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head))) * 100);
	}
	else
	{
		sprintf_s(nextHeadBuffer, 16, "None");
	}

	if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) < SteelChest)
	{
		sprintf_s(nextBodyBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) + 3), NULL, NULL)));
		sprintf_s(costBodyBuffer, 16, "Cost: %d", ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body))) * 100);
	}
	else
	{
		sprintf_s(nextBodyBuffer, 16, "None");
	}

	if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) < SteelBoots)
	{
		sprintf_s(nextLegsBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) + 3), NULL, NULL)));
		sprintf_s(costLegsBuffer, 16, "Cost: %d", ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs))) * 100);
	}
	else
	{
		sprintf_s(nextLegsBuffer, 16, "None");
	}

	if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon) < SteelSword)
	{
		sprintf_s(nextWeaponBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon) + 1), NULL, NULL)));
		sprintf_s(costWeaponBuffer, 16, "Cost: %d", ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon))) * 150);
	}
	else
	{
		sprintf_s(nextWeaponBuffer, 16, "None");
	}
	
	sprintf_s(goldBuffer, 16, "Gold: %d", PlayerGetGold());

	// Create transforms for positioning the menu items
	backTransform = TransformCreate(-500, -300);
	arrowTransform = TransformCreate(-210, 100);
	curHeadTransform = TransformCreate(-550, 0);
	curBodyTransform = TransformCreate(-550, -100);
	curLegsTransform = TransformCreate(-550, -200);
	curWeaponTransform = TransformCreate(-550, 100);
	nextHeadTransform = TransformCreate(-50, 0);
	nextBodyTransform = TransformCreate(-50, -100);
	nextLegsTransform = TransformCreate(-50, -200);
	nextWeaponTransform = TransformCreate(-50, 100);
	costHeadTransform = TransformCreate(0, -50);
	costBodyTransform = TransformCreate(0, -150);
	costLegsTransform = TransformCreate(0, -250);
	costWeaponTransform = TransformCreate(0, 50);
	goldTransform = TransformCreate(200, 200);
	highlighterTransform = TransformCreate(-410, -2.5);

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
	AEVec2 highlighterScale = { 500, 250 };
	TransformSetRotation(highlighterTransform, 0);
	TransformSetScale(highlighterTransform, &highlighterScale);

	// Set the highlighter sprite
	highlighterSprite = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(highlighterSprite, highlighterVertexList);
	SpriteSetSpriteSource(highlighterSprite, highlighterSpriteSource);
	
	// Connect the sprite and transform to the highlighter
	ObjectSetTransform(highlighterTransform, highlighterGameObject);
	ObjectSetSprite(highlighterSprite, highlighterGameObject);

	// Set the data for the arrow sprite
	AEVec2 arrowScale = { 100, 100 };
	TransformSetRotation(arrowTransform, 0);
	TransformSetScale(arrowTransform, &arrowScale);

	//set the arrow sprite
	arrowSprite = SpriteCreate("Arrow Sprite");
	SpriteSetMesh(arrowSprite, arrowVertexList);
	SpriteSetSpriteSource(arrowSprite, arrowSpriteSource);

	//connect the arrow sprite
	ObjectSetTransform(arrowTransform, arrowGameObject);
	ObjectSetSprite(arrowSprite, arrowGameObject);

	// Attach the needed info to the GameObjects
	PrintText(backGameObject, backBuffer, backSprite, backTransform);
	PrintText(curHeadGameObject, curHeadBuffer, curHeadSprite, curHeadTransform);
	PrintText(curBodyGameObject, curBodyBuffer, curBodySprite, curBodyTransform);
	PrintText(curLegsGameObject, curLegsBuffer, curLegsSprite, curLegsTransform);
	PrintText(curWeaponGameObject, curWeaponBuffer, curWeaponSprite, curWeaponTransform);
	PrintText(nextHeadGameObject, nextHeadBuffer, nextHeadSprite, nextHeadTransform);
	PrintText(nextBodyGameObject, nextBodyBuffer, nextBodySprite, nextBodyTransform);
	PrintText(nextLegsGameObject, nextLegsBuffer, nextLegsSprite, nextLegsTransform);
	PrintText(nextWeaponGameObject, nextWeaponBuffer, nextWeaponSprite, nextWeaponTransform);
	PrintText(costHeadGameObject, costHeadBuffer, costHeadSprite, costHeadTransform);
	PrintText(costBodyGameObject, costBodyBuffer, costBodySprite, costBodyTransform);
	PrintText(costLegsGameObject, costLegsBuffer, costLegsSprite, costLegsTransform);
	PrintText(costWeaponGameObject, costWeaponBuffer, costWeaponSprite, costWeaponTransform);
	PrintText(goldGameObject, goldBuffer, goldSprite, goldTransform);

	AEVec2 playerPosition = { 500, -122.5 };
	TransformSetTranslation(ObjectGetTransform(ObjectGetObject(PlayerGetHuman(), NULL, NULL, NULL)), &playerPosition);
	
	HumanSetShowHealth(PlayerGetHuman(), false);
	HumanSetShowStamina(PlayerGetHuman(), false);
	HumanSetSpeed(PlayerGetHuman(), 0);
  HumanSetDodgeSpeed(PlayerGetHuman(), 0);
  HumanSetFaceDir(PlayerGetHuman(), down);
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void ArmorShopUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	
	//update and draw the background
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);

	//set the text for how much gold you have
	sprintf_s(goldBuffer, 16, "Gold: %d", WornInventoryGetCount(HumanGetInventoryWorn(PlayerGetHuman()), slotGold));
	PrintText(goldGameObject, goldBuffer, goldSprite, goldTransform);
	DrawObject(goldGameObject);

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
		menuFlag = true;
	}

	//function for actually doing the menu stuff
	BuyMenu();

	// Change what item of the menu is highlighted
	if ((GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f) && menuFlag)
	{
		time2 = 0;
		menuFlag = false;
		highlighter++;
		SoundPlay(&optionSound, false);
	}
	else if ((GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f) && menuFlag)
	{
		time2 = 0;
		menuFlag = false;
		highlighter--;
		SoundPlay(&optionSound, false);
	}

  //draw damage popups
  DamagePopupsDraw();
}

// Shutdown the ...
void ArmorShopShutdown()
{
	FreeObject(&backGameObject);
	FreeObject(&arrowGameObject);
	FreeObject(&curHeadGameObject);
	FreeObject(&curBodyGameObject);
	FreeObject(&curLegsGameObject);
	FreeObject(&curWeaponGameObject);
	FreeObject(&nextHeadGameObject);
	FreeObject(&nextBodyGameObject);
	FreeObject(&nextLegsGameObject);
	FreeObject(&nextWeaponGameObject);
	FreeObject(&highlighterGameObject);
	FreeObject(&backgroundGameObject);

	HumanSetShowHealth(PlayerGetHuman(), true);
	HumanSetShowStamina(PlayerGetHuman(), true);
	HumanSetSpeed(PlayerGetHuman(), 30);

  ResetDamagePopupDrawer(); //reset damage popup data
}

void ArmorShopUnload()
{
	SpriteSourceFree(&fontSheetSpriteSource);
	AEGfxMeshFree(fontSheetVertexList);
	AEGfxTextureUnload(fontSheet);

	SpriteSourceFree(&highlighterSpriteSource);
	AEGfxMeshFree(highlighterVertexList);
	AEGfxTextureUnload(highlighterTexture);

	SpriteSourceFree(&backgroundSpriteSource);
	AEGfxMeshFree(backgroundVertexList);
	AEGfxTextureUnload(backgroundTexture);

	SpriteSourceFree(&arrowSpriteSource);
	AEGfxMeshFree(arrowVertexList);
	AEGfxTextureUnload(arrowTexture);

  DamagePopupsFree();//free damage popup stuff
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

//menu for buying new items
static void BuyMenu()
{
	// Locations for the highlighter over menu items
	AEVec2 backPos = { -360, -302.5 };
	AEVec2 curHeadPos = { 90, -2.5 };
	AEVec2 curBodyPos = { 90, -102.5 };
	AEVec2 curLegsPos = { 90, -202.5 };
	AEVec2 curWeaponPos = { 90, 97.5 };
	AEVec2 arrowPos = { -200, 100 };

	//draw the menu items
	DrawObject(backGameObject);
	DrawObject(curHeadGameObject);
	DrawObject(curBodyGameObject);
	DrawObject(curLegsGameObject);
	DrawObject(curWeaponGameObject);
	DrawObject(nextHeadGameObject);
	DrawObject(nextBodyGameObject);
	DrawObject(nextLegsGameObject);
	DrawObject(nextWeaponGameObject);
	DrawObject(costHeadGameObject);
	DrawObject(costBodyGameObject);
	DrawObject(costLegsGameObject);
	DrawObject(costWeaponGameObject);
	DrawObject(highlighterGameObject);

	TransformSetTranslation(arrowTransform, &arrowPos);
	DrawObject(arrowGameObject);
	arrowPos.y = 0;
	TransformSetTranslation(arrowTransform, &arrowPos);
	DrawObject(arrowGameObject);
	arrowPos.y = -100;
	TransformSetTranslation(arrowTransform, &arrowPos);
	DrawObject(arrowGameObject);
	arrowPos.y = -200;
	TransformSetTranslation(arrowTransform, &arrowPos);
	DrawObject(arrowGameObject);

	UpdateHuman(PlayerGetHuman());
	DrawItemsInQueue();

	// Wrap the menu to jump from bottom to top or top to bottom
	if (highlighter < 0)
		highlighter = 4;
	if (highlighter > 4)
		highlighter = 0;

	//when the highlighted button is selected
	if (GetButtonDown(0, 0))
	{
		int quality = 0;
		SoundPlay(&swordSound, false);
		switch (highlighter)
		{
		case 0:
			quality = ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon)));
			// upgrade the weapon slot
			if (quality < ItemGetQuality(ItemGetByID(SteelSword)) && WornInventoryGetCount(HumanGetInventoryWorn(PlayerGetHuman()), slotGold) >= quality * 150)
			{
          DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, 0, 100.0f, -50.0f, ObjectGetTransform(ObjectGetObject(PlayerGetHuman(),NULL,NULL,NULL)), DPUpgrade, false, 40.0f);
				WornInventoryAddGold(HumanGetInventoryWorn(PlayerGetHuman()), quality * -150);
				EquipItem(HumanGetInventoryWorn(PlayerGetHuman()), WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon) + 1);
				
				sprintf_s(curWeaponBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon)), NULL, NULL)));
				if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon) == SteelSword)
				{
					sprintf_s(nextWeaponBuffer, 16, "None");
					sprintf_s(costWeaponBuffer, 16, " ");
				}
				else
				{
					sprintf_s(nextWeaponBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Weapon) + 1), NULL, NULL)));
					sprintf_s(costWeaponBuffer, 16, "Cost: %d", (quality + 1) * 150);
				}
			}
			break;
		case 1:
			quality = ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head)));
			// upgrade the head slot
			if (quality < ItemGetQuality(ItemGetByID(SteelHelm)) && WornInventoryGetCount(HumanGetInventoryWorn(PlayerGetHuman()), slotGold) >= quality * 100)
			{
        DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, 0, 100.0f, -50.0f, ObjectGetTransform(ObjectGetObject(PlayerGetHuman(), NULL, NULL, NULL)), DPUpgrade, false, 40.0f);
        WornInventoryAddGold(HumanGetInventoryWorn(PlayerGetHuman()), quality * -100);
				EquipItem(HumanGetInventoryWorn(PlayerGetHuman()), WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head) + 3);
				
				sprintf_s(curHeadBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head)), NULL, NULL)));
				if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head) == SteelHelm)
				{
					sprintf_s(nextHeadBuffer, 16, "None");
					sprintf_s(costHeadBuffer, 16, " ");
				}
				else
				{
					sprintf_s(nextHeadBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Head) + 3), NULL, NULL)));
					sprintf_s(costHeadBuffer, 16, "Cost: %d", (quality + 1) * 100);
				}
			}
			break;
		case 2:
			quality = ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body)));
			// upgrade the body slot
			if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) < SteelChest &&
				WornInventoryGetCount(HumanGetInventoryWorn(PlayerGetHuman()), slotGold) >= quality * 100)
			{
        DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, 0, 100.0f, -50.0f, ObjectGetTransform(ObjectGetObject(PlayerGetHuman(), NULL, NULL, NULL)), DPUpgrade, false, 40.0f);
        WornInventoryAddGold(HumanGetInventoryWorn(PlayerGetHuman()), quality * -100);
				EquipItem(HumanGetInventoryWorn(PlayerGetHuman()), WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) + 3);
				
				sprintf_s(curBodyBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body)), NULL, NULL)));
				if(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) == SteelChest)
				{
					sprintf_s(nextBodyBuffer, 16, "None");
					sprintf_s(costBodyBuffer, 16, " ");
				}
				else
				{
					sprintf_s(nextBodyBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Body) + 3), NULL, NULL)));
					sprintf_s(costBodyBuffer, 16, "Cost: %d", (quality + 1) * 100);
				}
			}
			break;
		case 3:
			quality = ItemGetQuality(ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs)));
			// upgrade the legs slot
			if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) < SteelBoots &&
				WornInventoryGetCount(HumanGetInventoryWorn(PlayerGetHuman()), slotGold) >= quality * 100)
			{
        DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, 0, 100.0f, -50.0f, ObjectGetTransform(ObjectGetObject(PlayerGetHuman(), NULL, NULL, NULL)), DPUpgrade, false, 40.0f);
        WornInventoryAddGold(HumanGetInventoryWorn(PlayerGetHuman()), quality * -100);
				EquipItem(HumanGetInventoryWorn(PlayerGetHuman()), WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) + 3);
				
				sprintf_s(curLegsBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs)), NULL, NULL)));
				if (WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) == SteelBoots)
				{
					sprintf_s(nextLegsBuffer, 16, "None");
					sprintf_s(costLegsBuffer, 16, " ");
				}
				else
				{
					sprintf_s(nextLegsBuffer, 16, ObjectGetName(ObjectGetObject(NULL, ItemGetByID(WornInventoryGetId(HumanGetInventoryWorn(PlayerGetHuman()), Legs) + 3), NULL, NULL)));
					sprintf_s(costLegsBuffer, 16, "Cost: %d", (quality + 1) * 100);
				}
			}
			break;
		case 4:
			GameStateManagerSetNextState(GsPhysicalTown);
			break;
		}
	}

	// Update the highlighter to be over the correct menu item
	switch (highlighter)
	{
	case 0:
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &curWeaponPos);
		break;
	case 1:
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &curHeadPos);
		break;
	case 2:
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &curBodyPos);
		break;
	case 3:
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &curLegsPos);
		break;
	case 4:
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &backPos);
		break;
	}
}