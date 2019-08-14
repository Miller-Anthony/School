//------------------------------------------------------------------------------
//
// File Name:	GameStateTutorial.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		CS230S19-A
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include <stdio.h> //sprintf_s
#include "GameStateManager.h"
#include "GameStateTutorial.h"
#include "Input.h"
#include "Objects.h"
#include "Sound.h"
#include "Mesh.h"
#include "AI.h"
#include "collision.h"
#include "Text.H"
#include "ItemData.h"
#include "InventoryWorn.h"
#include "Camera.h"
#include "OST.h"
#include "PauseMenu.h"
#include "ParticleManager.h"
#include "ParticleEmitter.h"
#include "Transform.h"
//#include "Player.h" //PlayerAddGold

#define DEBUGGING 0
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
extern float vibrateTime;
extern bool isPaused;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int button;
static int flag;
static int menuFlag;
static int frame = 0;
static int frame2 = 0;

static AEVec2 humanScale = { 1.0f,1.0f };//{ 102.3f,60.0f };
static AEGfxVertexList* mesh1x1;

static SpritePtr pHealthTextSprite;
static SpritePtr eHealthTextSprite;

#pragma region PLAYER_STUFF

extern PlayerPtr player;
ObjectPtr pObj;
HumanPtr pHum;

#if DEBUGGING
static ObjectPtr pHealthTextObj;
static char pHealthBaseText[] = { "Player Health: %d" };
static char pHealthBuffer[32] = { 0 };
#endif
#pragma endregion

#pragma region ENEMY_STUFF

EnemyPtr enemy;
ObjectPtr eObj;
HumanPtr eHum;



#if DEBUGGING
static ObjectPtr eHealthTextObj;
static char eHealthBaseText[] = { "Enemy Health: %d" };
static char eHealthBuffer[32] = { 0 };
#endif

#pragma endregion

#pragma region ARENA_STUFF

static ObjectPtr arena;
static SpriteSourcePtr arenaSS;
static const char* arenaFile = "./Assets/Arena9.png";
static AEGfxTexture* arenaPNG;
static AEVec2 arenaScale = { 1920*2, 1080*2 };
static AEVec2 arenaPos = { 0.0f,155.0f };

#pragma endregion


#pragma region SCENE_START_STUFF

static bool sceneStarting = true;
static float sceneStartTimer = 3.0f;
static ObjectPtr startText;
static AEVec2 startTextScale = {75.0f,75.0f};
static AEVec2 startTextPos = { -750.0f,350.0f };
static AEVec2 startTimerPos = { 0.0f,-50.0f };
static char startTextString[] = "Tutorial Starting in:";
static char* startTextTimerString[] = {"3","2","1"};

static AEGfxVertexList* mesh16x6;
static AEGfxTexture* textPNG;
static SpriteSourcePtr textSS;

#pragma endregion

#pragma region SCENE_END_STUFF

static ObjectPtr blackObj;
static SpriteSourcePtr blackSS;
static AEGfxTexture* blackTexture;
static AEVec2 blackScale = { 5000, 5000 };
static float blackAlpha = 0.0f;
static GameStates nextState;
static bool sceneEnding = false;

#pragma endregion

#pragma region TUTORIAL_STUFF

static char Buffer[64] = "";

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

static AEGfxVertexList *buttonVertexList;
static AEGfxTexture *buttonTexture;
static SpriteSourcePtr buttonSpriteSource;
static SpritePtr buttonSprite;
static TransformPtr buttonTransform;
static ObjectPtr buttonObject;

#pragma endregion
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//static PlayerPtr CreateCharacter();
static EnemyPtr CreateEnemyChar();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


static EnemyPtr CreateEnemyChar()
{
    
    enemy = CreateEnemy("Enemy", EnemyTag, 100, 100, 5, 30, 100, 10, AIFIghtCustom, 0, 0, 1, 1, 10, true, true);
    eHum = HumanGetHuman(NULL, enemy);
    HumanSetWeapon(HumanGetHuman(NULL, enemy), WoodSword);
    HumanSetArmors(eHum, LeatherHelm, LeatherChest, LeatherBoots);
	
    eObj = ObjectGetObject(eHum, NULL, NULL, NULL);
    HumanAddTarget(HumanGetHuman(NULL, enemy), pHum);

	AEVec2 translate = { 150.0f, 150.0f };

	ObjectPtr obj = ObjectGetObject(NULL, NULL, NULL, enemy);
	TransformPtr trans = ObjectGetTransform(obj);

	AEVec2 scale = {20, 30};
	ColliderSetScale(ObjectGetCollider(obj), &scale);

	TransformSetTranslation(trans, &translate);
	TransformSetScale(trans, &humanScale);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(NULL, enemy)), DefaultShield);
	return enemy;
}

#if DEBUGGING
static ObjectPtr CreateHealthText(const float x, const float y, const float w, const float h)
{
    ObjectPtr textObj = CreateObject("Health Text", ObjTag);
    TransformPtr textTrans = ObjectGetTransform(textObj);

    AEVec2 pos;
    AEVec2 scale;
    pos.x = x;
    pos.y = y;
    scale.x = w;
    scale.y = h;

    TransformSetScale(textTrans, &scale);
    TransformSetTranslation(textTrans, &pos);

    return textObj;
}
#endif
// Load the resources associated with the Tutorial game state.
void GameStateTutorialLoad()
{
    //meshes
    mesh1x1 = MeshCreateQuad(.5f, .5f, 1.0f, 1.0f, "Mesh1x1");
    mesh16x6 = MeshCreateQuad(.5f, .5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");

    //arena
    arena = CreateObject("Arena", ObjTag);
    arenaPNG = AEGfxTextureLoad(arenaFile);
    arenaSS = SpriteSourceCreate(1, 1, arenaPNG);
    SpriteSourceSetTexture(arenaSS, arenaPNG);
    SpriteSetMesh(ObjectGetSprite(arena), mesh1x1);
    SpriteSetSpriteSource(ObjectGetSprite(arena), arenaSS);
    TransformSetTranslation(ObjectGetTransform(arena), &arenaPos);
    TransformSetScale(ObjectGetTransform(arena), &arenaScale);

    //assign player vars
    pHum = HumanGetHuman(player, NULL);
    pObj = ObjectGetObject(pHum, NULL, NULL, NULL);

    CreateEnemyChar(); //create enemy

    if (pHum)
    {
        HumanAddTarget(pHum, eHum);
        HumanSetSpeed(pHum, 30);
        HumanSetDodgeSpeed(pHum, 120);
        HumanSetFaceDir(pHum, down);
    }

    //black screen
    blackTexture = AEGfxTextureLoad("./Assets/BlackScreen.png");
    blackSS = SpriteSourceCreate(1, 1, blackTexture);
    blackObj = CreateObject("Black Screen", ObjTag);
    SpriteSourceSetTexture(blackSS, blackTexture);
    SpriteSetMesh(ObjectGetSprite(blackObj), mesh1x1);
    SpriteSetSpriteSource(ObjectGetSprite(blackObj), blackSS);
    TransformSetScale(ObjectGetTransform(blackObj), &blackScale);

    sceneEnding = false;

    //text
    textPNG = AEGfxTextureLoad("./Assets/Text_White.png");
    textSS = SpriteSourceCreate(16, 6, textPNG);
    SpriteSourceSetTexture(textSS, textPNG);
    startText = CreateObject("Start Text", ObjTag);
    SpriteSetSpriteSource(ObjectGetSprite(startText), textSS);
    SpriteSetMesh(ObjectGetSprite(startText), mesh16x6);

#if DEBUGGING
    pHealthTextObj = CreateHealthText(-900.0f, 500.0f, 30.0f, 30.0f);
    eHealthTextObj = CreateHealthText(300.0f, 500.0f, 30.0f, 30.0f);
    pHealthTextSprite = ObjectGetSprite(pHealthTextObj);
    eHealthTextSprite = ObjectGetSprite(eHealthTextObj);
    SpriteSetSpriteSource(pHealthTextSprite, textSS);
    SpriteSetSpriteSource(eHealthTextSprite, textSS);
    SpriteSetMesh(pHealthTextSprite, mesh16x6);
    SpriteSetMesh(eHealthTextSprite, mesh16x6);
#endif

	pauseVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pauseTexture = AEGfxTextureLoad("Assets/Text_White.png");
	pauseSpriteSource = SpriteSourceCreate(16, 6, pauseTexture);

	boardVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	boardTexture = AEGfxTextureLoad("Assets/Board2.png");
	boardSpriteSource = SpriteSourceCreate(1, 1, boardTexture);
	boardSprite = SpriteCreate("Board");

    InitDamagePopupDrawer();

	//ParticleEmitterCreateTemplate(cTemplateDirt, 1.0f);
	//ParticleEmitterCreateTemplate(cTemplateSpark, 1.0f);
}

// Initialize the memory associated with the Tutorial game state.
void GameStateTutorialInit()
{
	button = 0;
	pauseInit();
	stopSong();
	playSong(3);

	flag = 0;
	menuFlag = 0;
	frame = 0;
	frame2 = 0;

  sceneStarting = true;
  isPaused = true;
  sceneStartTimer = 3.0f;
  blackAlpha = 1.0f;
  SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);

  CameraSetPosBounds(-arenaScale.x / 4 + arenaPos.x, arenaScale.x / 4 + arenaPos.x, -arenaScale.y / 4 + arenaPos.y, arenaScale.y / 4 + arenaPos.y);
  CameraSetPosition(0.0f, 0.0f, false, true, false);

  TransformPtr pTrans = ObjectGetTransform(pObj);
  TransformPtr eTrans = ObjectGetTransform(eObj);
  AEVec2 pPos = { 0.0f };
  pPos.x = -arenaScale.x/4;
  AEVec2 ePos = { 0.0f};
  ePos.x = arenaScale.x/4;
  TransformSetTranslation(pTrans, &pPos);
  TransformSetTranslation(eTrans, &ePos);
}

// Update the Tutorial game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop
void GameStateTutorialUpdate(float dt)
{
	frame++;

    if (sceneStarting)
    {
        sceneStartTimer -= dt;
        DrawObject(blackObj);
        TransformSetScale(ObjectGetTransform(startText), &startTextScale);
        TransformSetTranslation(ObjectGetTransform(startText), &startTextPos);
        SpriteSetText(ObjectGetSprite(startText), startTextString);
        DrawObject(startText);  //Draw "Battle Starts in: "
        TransformSetTranslation(ObjectGetTransform(startText), &startTimerPos);
        if (sceneStartTimer > 2)
            SpriteSetText(ObjectGetSprite(startText), startTextTimerString[0]);
        else if(sceneStartTimer > 1)
            SpriteSetText(ObjectGetSprite(startText), startTextTimerString[1]);
        else if(sceneStartTimer > 0)
            SpriteSetText(ObjectGetSprite(startText), startTextTimerString[2]);
        else
        {
            sceneStarting = false;
            isPaused = false;
            blackAlpha = .0f;
            SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);
        }
        if(sceneStartTimer>0)
            DrawObject(startText);  //Draw "3", "2", "1"
        return;
    }

    DrawObject(arena);
    if (vibrateTime <= 0)
    {
        vibrateTime = -1.0f;
        ControllerVibrate(0, 0.0f, 0.0f);
    }
    if(vibrateTime>=0)
        vibrateTime -= dt;
  
	if(frame > 900)
		UpdateHuman(eHum);

    UpdateHuman(pHum);
    CollisionUpdate(eObj);
    CollisionUpdate(pObj);
    DrawItemsInQueue(); //Uncomment this one when not debugging (This Draw call is the for reals one)
    DamagePopupsDraw();
	//ParticleEmitterUpdateEmitter(dt);
	//ParticleManagerUpdateParticles(dt);
    CameraUpdate();
    UpdateItems();
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

    DrawObject(blackObj);


	boardTransform = TransformCreate(0, 0);
	AEVec2 boardTranslation = { 0, 0 };
	AEGfxGetCamPosition(&boardTranslation.x, &boardTranslation.y);
	boardTranslation.y -= 350;
	TransformSetTranslation(boardTransform, &boardTranslation);
	AEVec2 boardScale = { 640, 360 };
	TransformSetScale(boardTransform, &boardScale);
	SpriteSetMesh(boardSprite, boardVertexList);
	SpriteSetSpriteSource(boardSprite, boardSpriteSource);

	if(frame > 960 && frame < 1500)
		sprintf_s(Buffer, 64, "This is an enemy");
	else if (frame < 960)
		sprintf_s(Buffer, 64, "This is the player");
	else
		sprintf_s(Buffer, 64, "");

	pauseSprite = SpriteCreate("Pause Sprite");
	pauseTransform = TransformCreate(0, 0);
	AEVec2 translation = { 0, 0 };
	AEGfxGetCamPosition(&translation.x, &translation.y);
	AEVec2 scale = { 25, 25 };
	TransformSetScale(pauseTransform, &scale);
	translation.x -= 212.5;
	translation.y -= 275;
	TransformSetTranslation(pauseTransform, &translation);
	SpriteSetMesh(pauseSprite, pauseVertexList);
	SpriteSetSpriteSource(pauseSprite, pauseSpriteSource);
	SpriteSetText(pauseSprite, Buffer);

	if (frame < 1500)
	{
		SpriteDraw(boardSprite, boardTransform);
		SpriteDraw(pauseSprite, pauseTransform);
	}

	if (frame > 240 && frame < 600)
	{
		frame2++;
		buttonObject = CreateObject("Button Sprite", ObjTag);

		buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "Mesh 2x3");
		buttonTexture = AEGfxTextureLoad("Assets/Left.png");
		buttonSpriteSource = SpriteSourceCreate(2, 3, buttonTexture);
		buttonSprite = SpriteCreate("Button");
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpriteSource);

		buttonTransform = TransformCreate(0, 0);
		AEVec2 translation1 = { 0, 0 };
		AEGfxGetCamPosition(&translation1.x, &translation1.y);
		AEVec2 scale1 = { 250, 250 };
		TransformSetScale(buttonTransform, &scale1);
		//translation.x -= 212.5;
		translation1.y -= 350;
		TransformSetTranslation(buttonTransform, &translation1);

		ObjectSetTransform(buttonTransform, buttonObject);
		ObjectSetSprite(buttonSprite, buttonObject);

		if (frame2 < 60)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 0);
		else if (frame2 < 120)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 1);
		else if (frame2 < 180)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 2);
		else if (frame2 < 240)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 4);
		else if (frame2 < 300)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 3);
		else if (frame2 > 360)
			frame2 = 0;

		DrawObject(buttonObject);

		sprintf_s(Buffer, 64, "To move the player");
		//translation.x += 25;
		translation.y -= 150;
		TransformSetTranslation(pauseTransform, &translation);
		SpriteDraw(pauseSprite, pauseTransform);
	}
	else if (frame > 600 && frame < 960)
	{
		frame2++;
		//buttonObject = CreateObject("Button Sprite", ObjTag);

		//buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "Mesh 2x3");
		buttonTexture = AEGfxTextureLoad("Assets/Right.png");
		buttonSpriteSource = SpriteSourceCreate(2, 3, buttonTexture);
		//buttonSprite = SpriteCreate("Button");
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpriteSource);

		buttonTransform = TransformCreate(0, 0);
		AEVec2 translation1 = { 0, 0 };
		AEGfxGetCamPosition(&translation1.x, &translation1.y);
		AEVec2 scale1 = { 250, 250 };
		TransformSetScale(buttonTransform, &scale1);
		//translation.x -= 212.5;
		translation1.y -= 350;
		TransformSetTranslation(buttonTransform, &translation1);

		ObjectSetTransform(buttonTransform, buttonObject);
		ObjectSetSprite(buttonSprite, buttonObject);

		if (frame2 < 60)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 0);
		else if (frame2 < 120)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 1);
		else if (frame2 < 180)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 2);
		else if (frame2 < 240)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 4);
		else if (frame2 < 300)
			SpriteSetFrame(ObjectGetSprite(buttonObject), 3);
		else if (frame2 > 360)
			frame2 = 0;

		DrawObject(buttonObject);

		sprintf_s(Buffer, 64, "To dash: Uses POWER");
		translation.x -= 20;
		translation.y -= 150;
		TransformSetTranslation(pauseTransform, &translation);
		SpriteDraw(pauseSprite, pauseTransform);
	}
	else if (frame > 960 && frame < 1140)
	{
		frame2++;
		//buttonObject = CreateObject("Button Sprite", ObjTag);

		//buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "Mesh 2x3");
		buttonTexture = AEGfxTextureLoad("Assets/Button.png");
		buttonSpriteSource = SpriteSourceCreate(2, 3, buttonTexture);
		//buttonSprite = SpriteCreate("Button");
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpriteSource);

		buttonTransform = TransformCreate(0, 0);
		AEVec2 translation1 = { 0, 0 };
		AEGfxGetCamPosition(&translation1.x, &translation1.y);
		AEVec2 scale1 = { 250, 250 };
		TransformSetScale(buttonTransform, &scale1);
		//translation.x -= 212.5;
		translation1.y -= 362.5;
		TransformSetTranslation(buttonTransform, &translation1);

		ObjectSetTransform(buttonTransform, buttonObject);
		ObjectSetSprite(buttonSprite, buttonObject);

			SpriteSetFrame(ObjectGetSprite(buttonObject), 1);
		
		if (frame2 > 360)
			frame2 = 0;

		DrawObject(buttonObject);

		sprintf_s(Buffer, 64, "To ATTACK!");
		translation.x += 100;
		translation.y -= 150;
		TransformSetTranslation(pauseTransform, &translation);
		SpriteDraw(pauseSprite, pauseTransform);
	}
	else if (frame > 1140 && frame < 1320)
	{
		frame2++;
		//buttonObject = CreateObject("Button Sprite", ObjTag);

		//buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "Mesh 2x3");
		buttonTexture = AEGfxTextureLoad("Assets/Button.png");
		buttonSpriteSource = SpriteSourceCreate(2, 3, buttonTexture);
		//buttonSprite = SpriteCreate("Button");
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpriteSource);

		buttonTransform = TransformCreate(0, 0);
		AEVec2 translation1 = { 0, 0 };
		AEGfxGetCamPosition(&translation1.x, &translation1.y);
		AEVec2 scale1 = { 250, 250 };
		TransformSetScale(buttonTransform, &scale1);
		//translation.x -= 212.5;
		translation1.y -= 362.5;
		TransformSetTranslation(buttonTransform, &translation1);

		ObjectSetTransform(buttonTransform, buttonObject);
		ObjectSetSprite(buttonSprite, buttonObject);

		SpriteSetFrame(ObjectGetSprite(buttonObject), 3);

		if (frame2 > 360)
			frame2 = 0;

		DrawObject(buttonObject);

		sprintf_s(Buffer, 64, "To BLOCK!");
		translation.x += 100;
		translation.y -= 150;
		TransformSetTranslation(pauseTransform, &translation);
		SpriteDraw(pauseSprite, pauseTransform);
	}
	else if (frame > 1320 && frame < 1500)
	{
		frame2++;
		//buttonObject = CreateObject("Button Sprite", ObjTag);

		//buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 3, "Mesh 2x3");
		buttonTexture = AEGfxTextureLoad("Assets/Button.png");
		buttonSpriteSource = SpriteSourceCreate(2, 3, buttonTexture);
		//buttonSprite = SpriteCreate("Button");
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpriteSource);

		buttonTransform = TransformCreate(0, 0);
		AEVec2 translation1 = { 0, 0 };
		AEGfxGetCamPosition(&translation1.x, &translation1.y);
		AEVec2 scale1 = { 250, 250 };
		TransformSetScale(buttonTransform, &scale1);
		//translation.x -= 212.5;
		translation1.y -= 362.5;
		TransformSetTranslation(buttonTransform, &translation1);

		ObjectSetTransform(buttonTransform, buttonObject);
		ObjectSetSprite(buttonSprite, buttonObject);

		SpriteSetFrame(ObjectGetSprite(buttonObject), 4);

		if (frame2 > 360)
			frame2 = 0;

		DrawObject(buttonObject);

		sprintf_s(Buffer, 64, "To pause");
		translation.x += 100;
		translation.y -= 150;
		TransformSetTranslation(pauseTransform, &translation);
		SpriteDraw(pauseSprite, pauseTransform);
	}
	else if(frame > 1500)
	{
		sceneEnding = true;
	}


    int playerHealth = (int)HumanGetHealth(pHum);
    int enemyHealth = (int)HumanGetHealth(eHum);
    if (playerHealth <= 0)
    {
        sceneEnding = true;
    }
    else if (enemyHealth <= 0)
    {
        sceneEnding = true;
    }

    if (sceneEnding)
    {
        blackAlpha += .007f;
        SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);
        
        if (blackAlpha >= 1.0f)
            GameStateManagerSetNextState(GsTown);
    }

#pragma region UI

#if DEBUGGING
  AEVec2 camPos = { 0 };
  AEGfxGetCamPosition(&camPos.x, &camPos.y);
  TransformPtr pHealthTransform = ObjectGetTransform(pHealthTextObj);
  TransformPtr eHealthTransform = ObjectGetTransform(eHealthTextObj);
  AEVec2 pHealthPos = { -900.0f, 500.0f };
  AEVec2 eHealthPos = { 300.0f, 500.0f };
  
  AEVec2Add(&pHealthPos, &pHealthPos, &camPos);
  AEVec2Add(&eHealthPos, &eHealthPos, &camPos);
  TransformSetTranslation(pHealthTransform, &pHealthPos);
  TransformSetTranslation(eHealthTransform, &eHealthPos);

  sprintf_s(pHealthBuffer, sizeof(pHealthBuffer)/sizeof(*pHealthBuffer), pHealthBaseText, playerHealth);
  sprintf_s(eHealthBuffer, sizeof(eHealthBuffer)/sizeof(*eHealthBuffer), eHealthBaseText, enemyHealth);

  SpriteSetText(pHealthTextSprite, pHealthBuffer);
  SpriteSetText(eHealthTextSprite, eHealthBuffer);
  DrawObject(pHealthTextObj);
  DrawObject(eHealthTextObj);
#endif
#pragma endregion

#pragma region INPUT

  if (/*AEInputCheckTriggered('P') || */GetStartButton())
  {
		if (!isPaused)
			isPaused = true;
		else
			isPaused = false;
  }

#pragma endregion
	
	flag++;

	if (flag % 12 == 0)
		menuFlag = 0;

	if ((/*AEInputCheckTriggered(VK_DOWN) || */GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f) && menuFlag == 0)
	{
		button++;
		if (button > 3)
			button = 0;
		menuFlag = 1;
		flag = 0;
	}
	else if ((/*AEInputCheckTriggered(VK_UP) || */GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f) && menuFlag == 0)
	{
		button--;
		if (button < 0)
			button = 3;
		menuFlag = 1;
		flag = 0;
	}

	if (isPaused)
	{
		drawMenu(button);

		if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
		{
			isPaused = false;

			if (button == 0)
				isPaused = false;
			else if (button == 1)
				GameStateManagerSetNextState(GsRestart);
			else if(button == 2)
				GameStateManagerSetNextState(GsMenu);
			else if (button == 3)
				GameStateManagerSetNextState(GsQuit);
		}
	}
}

// Shutdown any memory associated with the Tutorial game state.
void GameStateTutorialShutdown()
{
    HumanSetHealth(pHum, 100);
    HumanSetHealth(eHum, 100);
    HumanSetBool(pHum, 0, 1, 0, 0, 0, 0);
    HumanSetFaceDir(pHum, down);
    UpdateHuman(pHum);
    CameraReset();
    ResetItemDrawer(); //prevent Item Drawer from drawing the previous frame
    ResetDamagePopupDrawer();
	//ParticleManagerClear();
	//ParticleEmitterClear();
}

// Unload the resources associated with the Tutorial game state.
void GameStateTutorialUnload()
{
    //SoundFree(&backgroundMusic);
    AEGfxMeshFree(mesh1x1);
    AEGfxMeshFree(mesh16x6);
    AEGfxTextureUnload(textPNG);
    AEGfxTextureUnload(arenaPNG);
    SpriteSourceFree(&textSS);
    SpriteSourceFree(&arenaSS);
#if DEBUGGING
    FreeObject(&pHealthTextObj);
    FreeObject(&eHealthTextObj);
#endif
    FreeObject(&arena);
    FreeEnemy(&enemy);
    HumanResetTargets(pHum);
    ResetDamagePopupDrawer();
    DamagePopupsFree();
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxMeshFree(boardVertexList);
	AEGfxMeshFree(pauseVertexList);
	AEGfxMeshFree(buttonVertexList);

	AEGfxTextureUnload(boardTexture);
	AEGfxTextureUnload(pauseTexture);
	AEGfxTextureUnload(buttonTexture);

	SpriteSourceFree(&boardSpriteSource);
	SpriteSourceFree(&pauseSpriteSource);
	SpriteSourceFree(&buttonSpriteSource);

	SpriteFree(&boardSprite);
	SpriteFree(&pauseSprite);
	SpriteFree(&buttonSprite);

	//FreeObject(&buttonObject);
	TransformFree(&boardTransform);
	TransformFree(&pauseTransform);

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

