//------------------------------------------------------------------------------
//
// File Name:	GameStatePVP.c
// Author(s):	Brayan Lopez, Akshat Madan
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
#include "GameStatePVP.h"
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
float vibrateTimeP2;
extern bool isPaused;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static int button;
static int flag;
static int menuFlag;

static SpritePtr p1HealthTextSprite;
static SpritePtr p2HealthTextSprite;

#pragma region ARENA_STUFF

static AEGfxVertexList* mesh1x1;
static ObjectPtr arena;
static SpriteSourcePtr arenaSS;
static const char* arenaFile = "./Assets/Arena9.png";
static AEGfxTexture* arenaPNG;
static const AEVec2 arenaScale = { 1920 * 2, 1080 * 2 };
static AEVec2 arenaPos = { 0.0f,155.0f };

#pragma endregion


#pragma region PLAYER1_STUFF

static PlayerPtr player1;
static HumanPtr p1Hum;
static ObjectPtr p1Obj;
static const AEVec2 p1StartPos = {-400,0.0f};
static AEVec2* p1Pos = NULL;

#if DEBUGGING
static ObjectPtr pHealthTextObj;
static char pHealthBaseText[] = { "Player Health: %d" };
static char pHealthBuffer[32] = { 0 };
#endif
#pragma endregion

#pragma region PLAYER2_STUFF

static PlayerPtr  player2;
static HumanPtr  p2Hum;
static ObjectPtr p2Obj;
static const AEVec2 p2StartPos = { 400,0.0f };
static AEVec2* p2Pos = NULL;

#if DEBUGGING
static ObjectPtr eHealthTextObj;
static char eHealthBaseText[] = { "Enemy Health: %d" };
static char eHealthBuffer[32] = { 0 };
#endif

#pragma endregion

static AEGfxVertexList* pIndicatorMesh; //the triangle thing floating above the player
static AEVec2 pIndicatorOffset = { 0.0f, 150.0f }; //offset from player
static AEVec2 pIndicatorScale = { 50.0f, 50.0f };
static TransformPtr pIndicatorTrans;


//#pragma region SCENE_START_STUFF
//
//static bool sceneStarting = true;
//static float sceneStartTimer = 3.0f;
//static ObjectPtr startText;
//static AEVec2 startTextScale = { 75.0f,75.0f };
//static AEVec2 startTextPos = { -650.0f,350.0f };
//static AEVec2 startTimerPos = { 0.0f,-50.0f };
//static char startTextString[] = "Battle Starting in:";
//static char* startTextTimerString[] = { "3","2","1" };
//
//static AEGfxVertexList* mesh16x6;
//static AEGfxTexture* textPNG;
//static SpriteSourcePtr textSS;
//
//#pragma endregion

#pragma region SCENE_END_STUFF

static ObjectPtr blackObj;
static SpriteSourcePtr blackSS;
static AEGfxTexture* blackTexture;
static AEVec2 blackScale = { 5000, 5000 };
static float blackAlpha = 0.0f;
static GameStates nextState;
static bool sceneEnding = false;
static bool displayedEndText = false;
TransformPtr winTextTrans;
#pragma endregion
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//static PlayerPtr CreateCharacter();
static void CreateBothPlayers();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------



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
// Load the resources associated with the PVP game state.
void GameStatePVPLoad()
{
    //meshes
    mesh1x1 = MeshCreateQuad(.5f, .5f, 1.0f, 1.0f, "Mesh1x1");
    //mesh16x6 = MeshCreateQuad(.5f, .5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");

    //triangle player indicator mesh
    AEGfxMeshStart();       //green
    AEGfxTriAdd(-.5f, .0f, 0xff000000, 0.0f, 1.0f, //top left
      .5f, .0f, 0xff000000, 1.0f, 1.0f, //top right
      .0f, -.5f, 0xff000000, 0.0f, 0.0f);//bottom
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

    //black screen
    blackTexture = AEGfxTextureLoad("./Assets/BlackScreen.png");
    blackSS = SpriteSourceCreate(1, 1, blackTexture);
    blackObj = CreateObject("Black Screen", ObjTag);
    SpriteSourceSetTexture(blackSS, blackTexture);
    SpriteSetMesh(ObjectGetSprite(blackObj), mesh1x1);
    SpriteSetSpriteSource(ObjectGetSprite(blackObj), blackSS);
    TransformSetScale(ObjectGetTransform(blackObj), &blackScale);

    sceneEnding = false;
    displayedEndText = false;
    winTextTrans = TransformCreate(0.0f, 0.0f);

    //text
    //textPNG = AEGfxTextureLoad("./Assets/Text_White.png");
    //textSS = SpriteSourceCreate(16, 6, textPNG);
    //SpriteSourceSetTexture(textSS, textPNG);
    //startText = CreateObject("Start Text", ObjTag);
    //SpriteSetSpriteSource(ObjectGetSprite(startText), textSS);
    //SpriteSetMesh(ObjectGetSprite(startText), mesh16x6);

    CreateBothPlayers();

#if DEBUGGING
    pHealthTextObj = CreateHealthText(-900.0f, 500.0f, 30.0f, 30.0f);
    eHealthTextObj = CreateHealthText(300.0f, 500.0f, 30.0f, 30.0f);
    p2HealthTextSprite = ObjectGetSprite(pHealthTextObj);
    p1HealthTextSprite = ObjectGetSprite(eHealthTextObj);
    SpriteSetSpriteSource(p2HealthTextSprite, textSS);
    SpriteSetSpriteSource(p1HealthTextSprite, textSS);
    SpriteSetMesh(p2HealthTextSprite, mesh16x6);
    SpriteSetMesh(p1HealthTextSprite, mesh16x6);
#endif


    InitDamagePopupDrawer();
}

// Initialize the memory associated with the PVP game state.
void GameStatePVPInit()
{
    button = 0;
    pauseInit();
    stopSong();
    playSong(5);

    //sceneStarting = true;
    isPaused = false;
    //sceneStartTimer = 3.0f;
    blackAlpha = .0f;
    SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);

    CameraSetPosBounds(-arenaScale.x / 4 + arenaPos.x, arenaScale.x / 4 + arenaPos.x, -arenaScale.y / 4 + arenaPos.y, arenaScale.y / 4 + arenaPos.y);
    CameraSetPosition(0.0f, 0.0f, false, true, false);

}

// Update the PVP game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop
void GameStatePVPUpdate(float dt)
{

    DrawObject(arena);

#pragma region VIBRATES

    if (vibrateTime <= 0)
    {
        vibrateTime = -1.0f;
        ControllerVibrate(0, 0.0f, 0.0f);
    }
    if (vibrateTime >= 0)
        vibrateTime -= dt;
    ////////////////////////////////
    if (vibrateTimeP2 <= 0)
    {
        vibrateTimeP2 = -1.0f;
        ControllerVibrate(1, 0.0f, 0.0f);
    }
    if (vibrateTimeP2 >= 0)
        vibrateTimeP2 -= dt;

#pragma endregion

    if (UpdateHuman(p1Hum))
    {
        p1Hum = NULL;
        p1Obj = NULL;
        player1 = NULL;
        p1Pos->x = 0.0f;
        p1Pos->y = 0.0f;
        //if (p2Hum)
        //{
        //  p1Pos->x = p2Pos->x;
        //  p1Pos->y = p2Pos->y;
        //}
        //else
        //{
        //  p1Pos->x = 0.0f;
        //  p1Pos->y = 0.0f;
        //}
        sceneEnding = true;
    }
    if (UpdateHuman(p2Hum))
    {
        p2Hum = NULL;
        p2Obj = NULL;
        player2 = NULL;
        p2Pos->x = 0.0f;
        p2Pos->y = 0.0f;
        //if (p1Hum)
        //{
        //  p2Pos->x = p1Pos->x;
        //  p2Pos->y = p1Pos->y;
        //}
        //else
        //{
        //  p2Pos->x = 0.0f;
        //  p2Pos->y = 0.0f;
        //}
        sceneEnding = true;
    }
    if (sceneEnding && !displayedEndText)
    {
        displayedEndText = true;
        nextState = GsTown;
        if (p1Hum)
          DamagePopupQueueForDrawing(0.0f, 0.0f, 1.0f, 1.0f, 0, 0.0f, 0.0f, NULL, DPPlayer1Wins, false, 100.0f);
        else if(p2Hum)                                                      
          DamagePopupQueueForDrawing(1.0f, 0.0f, 0.0f, 1.0f, 0, 0.0f, 0.0f, NULL, DPPlayer2Wins, false, 100.0f);
    }


    CollisionUpdate(p1Obj);
    CollisionUpdate(p2Obj);
    DrawObject(blackObj);
    DrawItemsInQueue(); //Uncomment this one when not debugging (This Draw call is the for reals one)
    DamagePopupsDraw();
    CameraUpdate();
    UpdateItems();
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    HumanDrawHealth(p1Hum);
    HumanDrawStamina(p1Hum);
    HumanDrawHealth(p2Hum);
    HumanDrawStamina(p2Hum);

    //player indicators
    AEVec2 playerIndicatorPos;
    if (p1Obj)
    {
    //put it on player 1
      AEVec2Add(&playerIndicatorPos, TransformGetTranslation(ObjectGetTransform(p1Obj)), &pIndicatorOffset);
      TransformSetTranslation(pIndicatorTrans, &playerIndicatorPos);
      MeshRender(pIndicatorMesh, NULL, TransformGetMatrix(pIndicatorTrans), 0);
    }
    if (p2Obj)
    {
      //put it on player 2
      AEGfxSetTintColor(1.0f, 0.0f, 0.0f, 1.0f); //tint it red
      AEVec2Add(&playerIndicatorPos, TransformGetTranslation(ObjectGetTransform(p2Obj)), &pIndicatorOffset);
      TransformSetTranslation(pIndicatorTrans, &playerIndicatorPos);
      MeshRender(pIndicatorMesh, NULL, TransformGetMatrix(pIndicatorTrans), 0);
    }
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); //reset tint color
    if(!sceneEnding)
      CameraOverrideSmoothing( (p1Pos->x+p2Pos->x)/2, (p1Pos->y + p2Pos->y) / 2, 2.5f, false);
    

    //int player1Health = (int)HumanGetHealth(p1Hum);
    //int player2Health = (int)HumanGetHealth(p2Hum);
    //if (player1Health <= 0)
    //{
    //    nextState = GsLose;
    //    sceneEnding = true;
    //}
    //else if (player2Health <= 0)
    //{
    //    nextState = GsWin;
    //    sceneEnding = true;
    //}

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

    sprintf_s(pHealthBuffer, sizeof(pHealthBuffer) / sizeof(*pHealthBuffer), pHealthBaseText, playerHealth);
    sprintf_s(eHealthBuffer, sizeof(eHealthBuffer) / sizeof(*eHealthBuffer), eHealthBaseText, enemyHealth);

    SpriteSetText(p2HealthTextSprite, pHealthBuffer);
    SpriteSetText(p1HealthTextSprite, eHealthBuffer);
    DrawObject(pHealthTextObj);
    DrawObject(eHealthTextObj);
#endif
#pragma endregion

#pragma region INPUT

    if (GetBackButton())
        AESysPrintf("Scoreboard\n");

    if (AEInputCheckTriggered('1'))
    {
        GameStateManagerSetNextState(GsRestart);
    }
    else if (AEInputCheckTriggered('2'))
    {
        GameStateManagerSetNextState(GsLevel2);
    }
    else if (AEInputCheckTriggered('3'))
    {
        GameStateManagerSetNextState(GsArmorShop);
    }
    else if (AEInputCheckTriggered('5'))
    {
        GameStateManagerSetNextState(GsTitle);
    }
    else if (AEInputCheckTriggered('6'))
    {
        GameStateManagerSetNextState(GsMenu);
    }
    else if (AEInputCheckTriggered('7'))
    {
        GameStateManagerSetNextState(GsBattleRoyale);
    }
    else if (AEInputCheckTriggered('P') || GetStartButton())
    {
        if (!isPaused)
            isPaused = true;
        else
            isPaused = false;
    }

#pragma endregion

#pragma region PAUSE_MENU_STUFF

    flag++;

    if (flag % 12 == 0)
        menuFlag = 0;

    if ((AEInputCheckTriggered(VK_DOWN) || GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f) && menuFlag == 0)
    {
        button++;
        if (button > 3)
            button = 0;
        menuFlag = 1;
        flag = 0;
    }
    else if ((AEInputCheckTriggered(VK_UP) || GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f) && menuFlag == 0)
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

        if (AEInputCheckTriggered(VK_RETURN) || GetButtonDown(0, 0))
        {
            isPaused = false;

            if (button == 0)
                isPaused = false;
            else if (button == 1)
                GameStateManagerSetNextState(GsRestart);
            else if (button == 2)
                GameStateManagerSetNextState(GsMenu);
            else if (button == 3)
                GameStateManagerSetNextState(GsQuit);
        }
    }

#pragma endregion

}

// Shutdown any memory associated with the PVP game state.
void GameStatePVPShutdown()
{
    HumanSetHealth(p1Hum, 100);
    HumanSetBool(p1Hum, 0, 1, 0, 0, 0, 0);
    HumanSetFaceDir(p1Hum, down);
    UpdateHuman(p1Hum);

    HumanSetHealth(p2Hum, 100);
    HumanSetBool(p2Hum, 0, 1, 0, 0, 0, 0);
    HumanSetFaceDir(p2Hum, down);
    UpdateHuman(p2Hum);
    
    CameraReset();
    ResetItemDrawer(); //prevent Item Drawer from drawing the previous frame
    ResetDamagePopupDrawer();
}

// Unload the resources associated with the PVP game state.
void GameStatePVPUnload()
{
    //SoundFree(&backgroundMusic);
    AEGfxMeshFree(mesh1x1);
    //AEGfxMeshFree(mesh16x6);
    //AEGfxTextureUnload(textPNG);
    AEGfxTextureUnload(arenaPNG);
    //SpriteSourceFree(&textSS);
    SpriteSourceFree(&arenaSS);
#if DEBUGGING
    FreeObject(&pHealthTextObj);
    FreeObject(&eHealthTextObj);
#endif
    FreeObject(&arena);
    FreePlayer(&player1);
    FreePlayer(&player2);
    ResetDamagePopupDrawer();
    DamagePopupsFree();
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    TransformFree(&winTextTrans);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void CreateBothPlayers()
{
    player1 = CreatePlayer("player", PlayerTag, 100, 100, 5, 30, 130, 5, true, true);
    player2 = CreatePlayer("Erich 2", Player2Tag, 100, 100, 5, 30, 130, 5, true, true);
    PlayerSetControllerID(player2, 1);

    p1Hum = HumanGetHuman(player1, NULL);
    p2Hum = HumanGetHuman(player2, NULL);

    p1Obj = ObjectGetObject(p1Hum, NULL, player1, NULL);
    p2Obj = ObjectGetObject(p2Hum, NULL, player2, NULL);

    TransformSetTranslation(ObjectGetTransform(p1Obj), &p1StartPos);
    TransformSetTranslation(ObjectGetTransform(p2Obj), &p2StartPos);

    p1Pos = TransformGetTranslation(ObjectGetTransform(p1Obj));
    p2Pos = TransformGetTranslation(ObjectGetTransform(p2Obj));

    HumanAddTarget(p1Hum, p2Hum);
    HumanAddTarget(p2Hum, p1Hum);

    HumanSetArmors(p1Hum, ClothHelm, ClothChest, ClothBoots);
    HumanSetArmors(p2Hum, ClothHelm, ClothChest, ClothBoots);

    HumanSetWeapon(p1Hum, WoodSword);
    HumanSetWeapon(p2Hum, WoodSword);

    EquipItem(HumanGetInventoryWorn(p1Hum), DefaultShield);
    EquipItem(HumanGetInventoryWorn(p2Hum), DefaultShield);

    AEVec2 scale = { 20, 30 };
    ColliderSetScale(ObjectGetCollider(p1Obj), &scale);
    ColliderSetScale(ObjectGetCollider(p2Obj), &scale);

    //eObj = ObjectGetObject(p2Hum, NULL, NULL, NULL);
    //HumanAddTarget(HumanGetHuman(NULL, enemy), p1Hum);
    //
    //AEVec2 translate = { 150.0f, 150.0f };
    //
    //ObjectPtr obj = ObjectGetObject(NULL, NULL, NULL, enemy);
    //TransformPtr trans = ObjectGetTransform(obj);
    //
    //
    //TransformSetTranslation(trans, &translate);
    //TransformSetScale(trans, &humanScale);
    //EquipItem(HumanGetInventoryWorn(HumanGetHuman(NULL, enemy)), DefaultShield);
    //return enemy;
}
