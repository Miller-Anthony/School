//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel1.c
// Author(s):	Anthony Miller, Brayan Lopez, Akshat Madan, Erich
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
#include "GameStateLevel1.h"
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
extern Bosses boss;
bool isPaused = false;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static int button;
static int flag;
static int menuFlag;

static FMOD_SOUND* backgroundMusic;
static AEVec2 humanScale = { 1.0f,1.0f };//{ 102.3f,60.0f };
static AEGfxVertexList* mesh1x1;

static SpritePtr pHealthTextSprite;
static SpritePtr eHealthTextSprite;

#pragma region PLAYER_STUFF

extern PlayerPtr player;
ObjectPtr pObj;
HumanPtr pHum;
static TransformPtr pTrans;  //player transform

static AEGfxVertexList* pIndicatorMesh; //the triangle thing floating above the player
static AEVec2 pIndicatorOffset = { 0.0f, 150.0f }; //offset from player
static AEVec2 pIndicatorScale = { 50.0f, 50.0f };
static TransformPtr pIndicatorTrans;

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
static AEVec2 startTextPos = { -650.0f,350.0f };
static AEVec2 startTimerPos = { 0.0f,-50.0f };
static char startTextString[] = "Battle Starting in:";
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
    switch (boss)
    {
    case SerScatterfoot:
        enemy = CreateEnemy("Enemy", EnemyTag, 100, 100, 5, 30, 100, 10, AIFIghtCustom, 11, 6, 5, 5, 10, true, true);
        eHum = HumanGetHuman(NULL, enemy);
        HumanSetWeapon(HumanGetHuman(NULL, enemy), WoodSword);
        HumanSetArmors(eHum, LeatherHelm, LeatherChest, LeatherBoots);
        break;
    case BaronDeEvidance:
        enemy = CreateEnemy("Enemy", EnemyTag, 100, 100, 5, 30, 100, 10, AIFIghtCustom, 12, 8, 3, 5, 10, true, true);
        eHum = HumanGetHuman(NULL, enemy);
        HumanSetWeapon(HumanGetHuman(NULL, enemy), IronSword);
        HumanSetArmors(eHum, IronHelm, IronChest, IronBoots);
        break;
    case SVEN:
        enemy = CreateEnemy("Enemy", EnemyTag, 100, 100, 10, 35, 105, 33, AIFIghtCustom, 16, 12, 3, 5, 10, true, true);
        eHum = HumanGetHuman(NULL, enemy);
        HumanSetWeapon(HumanGetHuman(NULL, enemy), SteelSword);
        HumanSetArmors(eHum, SteelHelm, SteelChest, SteelBoots);
        break;
    }
	
    eObj = ObjectGetObject(eHum, NULL, NULL, NULL);
    //HumanAddTarget(HumanGetHuman(NULL, enemy), pHum);
    HumanAddTarget(eHum, pHum);

	AEVec2 translate = { 150.0f, 150.0f };

	//ObjectPtr obj = ObjectGetObject(NULL, NULL, NULL, enemy);
	//TransformPtr trans = ObjectGetTransform(obj);
	TransformPtr trans = ObjectGetTransform(eObj);

	AEVec2 scale = {20, 30};
	ColliderSetScale(ObjectGetCollider(eObj), &scale);

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
// Load the resources associated with the Level1 game state.
void GameStateLevel1Load()
{
    //meshes
    mesh1x1 = MeshCreateQuad(.5f, .5f, 1.0f, 1.0f, "Mesh1x1");
    mesh16x6 = MeshCreateQuad(.5f, .5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
    
    //triangle player indicator mesh
    AEGfxMeshStart();       //green
    AEGfxTriAdd(-.5f,  .0f, 0xff00ff00, 0.0f, 1.0f, //top left
                 .5f,  .0f, 0xff00ff00, 1.0f, 1.0f, //top right
                 .0f, -.5f, 0xff00ff00, 0.0f, 0.0f);//bottom
    pIndicatorMesh = AEGfxMeshEnd();
    AE_ASSERT_MESG(pIndicatorMesh, "Failed to create mesh: %s", "Player Indicator Mesh");

    //more triangle indicator stuff
    pIndicatorTrans = TransformCreate(0.0f, 0.0f);
    TransformSetScale(pIndicatorTrans, &pIndicatorScale);

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


    InitDamagePopupDrawer();
}

// Initialize the memory associated with the Level1 game state.
void GameStateLevel1Init()
{
	button = 0;
	pauseInit();
	stopSong();
	playSong(3);

  sceneStarting = true;
  isPaused = true;
  sceneStartTimer = 3.0f;
  blackAlpha = 1.0f;
  SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);

  CameraSetPosBounds(-arenaScale.x / 4 + arenaPos.x, arenaScale.x / 4 + arenaPos.x, -arenaScale.y / 4 + arenaPos.y, arenaScale.y / 4 + arenaPos.y);
  CameraSetPosition(0.0f, 0.0f, false, true, false);

  pTrans = ObjectGetTransform(pObj);
  TransformPtr eTrans = ObjectGetTransform(eObj);
  AEVec2 pPos = { 0.0f };
  pPos.x = -arenaScale.x/4;
  AEVec2 ePos = { 0.0f};
  ePos.x = arenaScale.x/4;
  TransformSetTranslation(pTrans, &pPos);
  TransformSetTranslation(eTrans, &ePos);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop
void GameStateLevel1Update(float dt)
{
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
  
    UpdateHuman(eHum);
    UpdateHuman(pHum);
    CollisionUpdate(eObj);
    CollisionUpdate(pObj);
    DrawItemsInQueue(); //Uncomment this one when not debugging (This Draw call is the for reals one)
    DamagePopupsDraw();
    CameraUpdate();
    UpdateItems();
	//ParticleEmitterUpdateEmitter(dt);
	//ParticleManagerUpdateParticles(dt);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	HumanDrawHealth(pHum);
	HumanDrawStamina(pHum);
	HumanDrawHealth(eHum);
	HumanDrawStamina(eHum);
  //player indicator triangle rendering
  AEVec2 playerIndicatorPos;
  AEVec2Add(&playerIndicatorPos,TransformGetTranslation(pTrans),&pIndicatorOffset);
  TransformSetTranslation(pIndicatorTrans, &playerIndicatorPos);
  MeshRender(pIndicatorMesh, NULL, TransformGetMatrix(pIndicatorTrans), 0);

    DrawObject(blackObj);

    int playerHealth = (int)HumanGetHealth(pHum);
    int enemyHealth = (int)HumanGetHealth(eHum);
    if (playerHealth <= 0)
    {
        nextState = GsLose;
        sceneEnding = true;
    }
    else if (enemyHealth <= 0)
    {
        nextState = GsWin;
        sceneEnding = true;
    }

    if (sceneEnding)
    {
        blackAlpha += .007f;
        SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);
        
        if (blackAlpha >= 1.0f)
            GameStateManagerSetNextState(nextState);
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

	//if (GetBackButton())
	//	AESysPrintf("Scoreboard\n");
 // 
	//if (AEInputCheckTriggered('1'))
	//{
	//	GameStateManagerSetNextState(GsRestart);
	//}
	//else if (AEInputCheckTriggered('2'))
	//{
	//	GameStateManagerSetNextState(GsLevel2);
	//}
	//else if (AEInputCheckTriggered('3'))
	//{
	//	GameStateManagerSetNextState(GsArmorShop);
	//}
	//else if (AEInputCheckTriggered('5'))
	//{
	//	GameStateManagerSetNextState(GsTitle);
	//}
	//else if (AEInputCheckTriggered('6'))
	//{
	//	GameStateManagerSetNextState(GsMenu);
	//}
 // else if (AEInputCheckTriggered('7'))
 // {
 //     GameStateManagerSetNextState(GsBattleRoyale);
 // }
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
				GameStateManagerSetNextState(GsPhysicalTown);
			else if (button == 3)
				GameStateManagerSetNextState(GsQuit);
		}
	}
}

// Shutdown any memory associated with the Level1 game state.
void GameStateLevel1Shutdown()
{
    HumanSetHealth(pHum, 100);
	HumanSetPreviousHealth(pHum, 100);
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

// Unload the resources associated with the Level1 game state.
void GameStateLevel1Unload()
{
    //SoundFree(&backgroundMusic);
    AEGfxMeshFree(mesh1x1);
    AEGfxMeshFree(mesh16x6);
    AEGfxMeshFree(pIndicatorMesh);
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
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

