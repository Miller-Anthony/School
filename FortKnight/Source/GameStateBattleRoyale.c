//------------------------------------------------------------------------------
//
// File Name:	GameStateBattleRoyale.c
// Author(s):	Brayan Lopez, Erich Atwell
// Project:		Knightmare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "GameStateManager.h"
#include "GameStateBattleRoyale.h"
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
#include "Utils.h"
#include "Camera.h"
#include "OST.h"
#include "PauseMenu.h"
#include "ParticleManager.h"
#include "ParticleEmitter.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

#define KILLFEED_LENGTH 5

//static float killFeedX;
//static float killFeedYs[KILLFEED_LENGTH];
static bool killFeedSlotActive[KILLFEED_LENGTH] = { 0 };
static float killFeedAlphas[KILLFEED_LENGTH] = { 1.0f, .9f, .8f, .7f, .6f };
static char* killFeedStrings[KILLFEED_LENGTH] = { 0 };
static SpritePtr killFeedSprite;
static TransformPtr killFeedTrans;
//static const char* killFeedKillas[KILLFEED_LENGTH] = { 0 };
//static const char* killFeedDeads[KILLFEED_LENGTH] = { 0 };

// Do not open this
typedef enum Names //close this
{
	Josef,
	Robin,
	Thomas,
	Peter,
	Fredrick,
	Arthur,
	Donald,
	Doran,
	Merek,
	Rowan,
	Brom,
	Edmund,
	William,
	Matthew,
	Justin,
	Charles,
	Kris,
	Boris,
	Michael,
	John,
	Ajay,
	Walter,
	Juanes,
	Simon,
	Carl, 
	Geoffrey,
	Oliver,
	Henry, 
	Ralph, 
	Sadio,
	Mohammed,
	Tristan, 
	Collin,
	Zane,
	Daniel,
	Gordan,
	Maxwell,
	Vladimir,
	Rishabh,
	Robert,
	Hunter, 
	Alex,
	Alexander,
	James,
	Kyle, 
	Jack, 
	Hugh,
	Feron,
	Aditya,
	Leo,
	Phillip,
	Cedric, 
	Terryn,
	Johnny,
	Anthony,
	Erich,
	Spice, 
	Brayan, 
	Dieter,
	Hans,
	Francesco,
	Pierre,
	Podrick, 
	Jaime, 
	Ethan, 
	Rolland,
	Ronald, 
	Blake, 
	Christian,
	Jessie, 
	Axielle, 
	Jacquelyn,
	Michelle,
	Arabella,
	Elizabeth, 
	Beatrix,
	Ellyn,
	Anne,
	Mary, 
	Carolyn, 
	Rose,
	Helena,
	Victoria,
	Gwendolynn,
	Katerina,
	Seraphina,
	Emily,
	Winifred,
	Alexia,
	Isabel,
	Alice, 
	Julianna, 
	Tamara,
	Opal,
	Juniper,
	Veronica,
	Quinn,
	Lucilia,
	Erza, 
	Juvia,
	NamesMax
}Names;

static bool nameChosen[NamesMax] = { 0 };

static const char* names[NamesMax] = 
{ // close this
	"Josef",
	"Robin",
	"Thomas",
	"Peter",
	"Fredrick",
	"Arthur",
	"Donald",
	"Doran",
	"Merek",
	"Rowan",
	"Brom",
	"Edmund",
	"William",
	"Matthew",
	"Justin",
	"Charles",
	"Kris",
	"Boris",
	"Michael",
	"John",
	"Ajay",
	"Walter",
	"Juanes",
	"Simon",
	"Carl",
	"Geoffrey",
	"Oliver",
	"Henry",
	"Ralph",
	"Sadio",
	"Mohammed",
	"Tristan",
	"Collin",
	"Zane",
	"Daniel",
	"Gordan",
	"Maxwell",
	"Vladimir",
	"Rishabh",
	"Robert",
	"Hunter",
	"Alex",
	"Alexander",
	"James",
	"Kyle",
	"Jack",
	"Hugh",
	"Feron",
	"Aditya",
	"Leo",
	"Phillip",
	"Cedric",
	"Terryn",
	"Johnny",
	"Anthony",
	"Erich",
	"Spice",
	"Brayan",
	"Dieter",
	"Hans",
	"Francesco",
	"Pierre",
	"Podrick",
	"Jaime",
	"Ethan",
	"Rolland",
	"Ronald",
	"Blake",
	"Christian",
	"Jessie",
	"Axielle",
	"Jacquelyn",
	"Michelle",
	"Arabella",
	"Elizabeth",
	"Beatrix",
	"Ellyn",
	"Anne",
	"Mary",
	"Carolyn",
	"Rose",
	"Helena",
	"Victoria",
	"Gwendolynn",
	"Katerina",
	"Seraphina",
	"Emily",
	"Winifred",
	"Alexia",
	"Isabel",
	"Alice",
	"Julianna",
	"Tamara",
	"Opal",
	"Juniper",
	"Veronica",
	"Quinn",
	"Lucilia",
	"Erza",
	"Juvia"
}; // thank you

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
extern float vibrateTime;
int BRplacing;
extern bool isPaused;
extern bool followKillLeader; //camera following kill leader (defined and modified in Objects.c)
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static AEGfxVertexList* mesh1x1;
static unsigned mostKills;
static HumanPtr killLeader;
static HumanPtr pastKillLeader;

static int setkill = 0;
static int button = 0;
static int flag = 0;
static int menuFlag = 0;
static int wavy = 0;
static float alphaH = 0.2f;
static float fadeout = 0.0f;
static int spectate = 0;

//static FMOD_SOUND* backgroundMusic;

//static SpritePtr pHealthTextSprite;
//static SpritePtr eHealthTextSprite;

#pragma region PLAYER_STUFF

static PlayerPtr playerBR;
static HumanPtr pHumBR;
static TransformPtr pTransBR;  //player transform


static AEGfxVertexList* pIndicatorMesh; //the triangle thing floating above the player
static AEVec2 pIndicatorOffset = { 0.0f, 150.0f }; //offset from player
static AEVec2 pIndicatorScale = { 50.0f, 50.0f };
static TransformPtr pIndicatorTrans;
static SpritePtr pIndicatorSprite;

//static ObjectPtr pHealthTextObj;
//static char pHealthBaseText[] = { "playerBR Health: %d" };
//static char pHealthBuffer[32] = { 0 };
#pragma endregion

#pragma region ARENA_STUFF

static ObjectPtr arena;
static SpriteSourcePtr arenaSS;
static const char* arenaFile = "./Assets/Arena9.png";
static AEGfxTexture* arenaPNG;
static AEVec2 arenaScale = { 1920 * 2, 1080 * 2 };
static AEVec2 arenaPos = { 0.0f,155.0f };
#pragma endregion

#pragma region SCENE_START_STUFF

static bool sceneStarting = true;
static float sceneStartTimer = 3.0f;
static ObjectPtr startText;
static AEVec2 startTextScale = { 75.0f,75.0f };
static AEVec2 startTextPos = { -650.0f,350.0f };
static AEVec2 startTimerPos = { 0.0f,-50.0f };
static char startTextString[] = "Battle Starting in:";
static char* startTextTimerString[] = { "3","2","1" };

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

static ObjectPtr spectatingTextObj;
static AEVec2 spectatingTextScale = { 30.0f,30.0f };
static char spectatingBuffer[64] = { 0 };
static int playerKills;

static void PrintText(ObjectPtr GameObject, char *charBuffer,
	SpritePtr pSpriteSrc, TransformPtr pTransform);
static void displayhumancount();
static HumanPtr ActiveHumanList[MAXOBJECTAMOUNT];
static HumanPtr DeadHumanList[MAXOBJECTAMOUNT];
static int ActiveHumanCount = 1;
static int DeadHumanCount = 0;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BattleRoyaleUpdateHumans();
static void BattleRoyaleSpawnHumans();
static void BattleRoyaleSetAllTargets();
static void BattleRoyaleFreeHumans();
static EnemyPtr CreateRandomEnemy();
//static void QueueKill(const char* killer, const char* dead); //now public
static void KillFeedInit();
static void DisplayKillFeed();
static void ResetKillFeed();
static void FreeKillFeed();

//static void UpdateHealth();

// Display Battle Royal Huds
static float WinY;									  
static float WinX;									  
static char displayBuffer[16] = "";					  
SpritePtr displaySprite;							  
TransformPtr displayTransform;						  
static ObjectPtr displayObject;						  
static AEGfxVertexList *displayVertexList;			  
static AEGfxTexture *displayTexture;				  
static SpriteSourcePtr displaySpriteSource;			  
static char display2Buffer[16] = "";				  
SpritePtr display2Sprite;							  
TransformPtr display2Transform;						  
static ObjectPtr display2Object;					  
static AEGfxVertexList *display2VertexList;			  
static AEGfxTexture *display2Texture;				  
static SpriteSourcePtr display2SpriteSource;		  
static char display3Buffer[16] = "";				  
SpritePtr display3Sprite;							  
TransformPtr display3Transform;						  
static ObjectPtr display3Object;					  
static AEGfxVertexList *display3VertexList;			  
static AEGfxTexture *display3Texture;				  
static SpriteSourcePtr display3SpriteSource;		  
static char continueBuffer[16] = "";				  
SpritePtr continueSprite;							  
TransformPtr continueTransform;						  
static ObjectPtr continueObject;					  
static AEGfxVertexList *continueVertexList;			  
static AEGfxTexture *continueTexture;				  
static SpriteSourcePtr continueSpriteSource;		  
static AEGfxVertexList *highlighterVertexList;		  
static AEGfxTexture *highlighterTexture;			  
static SpriteSourcePtr highlighterSpriteSource;	
static ObjectPtr highlighterGameObject;
static TransformPtr highlighterTransform;
static SpritePtr highlighterSprite;

static AEGfxVertexList *victoryVertexList;
static AEGfxTexture *victoryTexture;
static SpriteSourcePtr victorySpriteSource;
static ObjectPtr victoryGameObject;
static TransformPtr victoryTransform;
static SpritePtr victorySprite;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateBattleRoyaleLoad()
{
	//ParticleEmitterCreateTemplate(cTemplateDirt, 5.0f);
	//ParticleEmitterCreateTemplate(cTemplateSpark, 1.0f);

    //meshes
    mesh1x1 = MeshCreateQuad(.5f,.5f,1.0f,1.0f,"Mesh1x1");
    mesh16x6 = MeshCreateQuad(.5f,.5f,1.0f/16,1.0f/6,"Mesh16x6");

    //triangle player indicator mesh
    AEGfxMeshStart();       //blue?
    AEGfxTriAdd(-.5f, .0f, 0xff00ff00, 0.0f, 1.0f, //top left
      .5f, .0f, 0xff00ff00, 1.0f, 1.0f, //top right
      .0f, -.5f, 0xff00ff00, 0.0f, 0.0f);//bottom
    pIndicatorMesh = AEGfxMeshEnd();
    AE_ASSERT_MESG(pIndicatorMesh, "Failed to create mesh: %s", "Player Indicator Mesh");

    //more triangle indicator stuff
    pIndicatorTrans = TransformCreate(0.0f, 0.0f);
    TransformSetScale(pIndicatorTrans, &pIndicatorScale);
    pIndicatorSprite = SpriteCreate("Player Indicator");
    SpriteSetMesh(pIndicatorSprite, pIndicatorMesh);
    

    //arena
    arenaPNG = AEGfxTextureLoad(arenaFile);
    arenaSS = SpriteSourceCreate(1,1,arenaPNG);
    arena = CreateObject("Arena",ObjTag);
    TransformSetScale(ObjectGetTransform(arena), &arenaScale);
    TransformSetTranslation(ObjectGetTransform(arena), &arenaPos);
    SpriteSetSpriteSource(ObjectGetSprite(arena), arenaSS);
    SpriteSetMesh(ObjectGetSprite(arena), mesh1x1);
    
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
    spectatingTextObj = CreateObject("Spectating Text", ObjTag);
    TransformSetScale(ObjectGetTransform(spectatingTextObj), &spectatingTextScale);
    SpriteSetMesh(ObjectGetSprite(spectatingTextObj), mesh16x6);
    SpriteSetSpriteSource(ObjectGetSprite(spectatingTextObj), textSS);

    InitDamagePopupDrawer();

	// display huds for kill count and shtuph
	displayVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	displayTexture = AEGfxTextureLoad("Assets/Text_White.png");
	displaySpriteSource = SpriteSourceCreate(16, 6, displayTexture);

	// highlit yea
	highlighterVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	highlighterTexture = AEGfxTextureLoad("Assets/buttonSelect.png");
	highlighterSpriteSource = SpriteSourceCreate(1, 1, highlighterTexture);

	victoryVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	victoryTexture = AEGfxTextureLoad("Assets/Victory.png");
	victorySpriteSource = SpriteSourceCreate(1, 1, victoryTexture);

  KillFeedInit();
}

// Initialize the memory associated with the game state.
void GameStateBattleRoyaleInit()
{
	setkill = 0;
	wavy = 0;
	alphaH = 0.2f;
	BRplacing = 0;
    button = 0;
	fadeout = 0.0f;
	spectate = 0;
    pauseInit();
    ActiveHumanCount = 1;
    BattleRoyaleSpawnHumans();
    BattleRoyaleSetAllTargets();
    CameraSetPosBounds(-arenaScale.x / 4 + arenaPos.x, arenaScale.x / 4 + arenaPos.x, -arenaScale.y / 4 + arenaPos.y, arenaScale.y / 4 + arenaPos.y);
    CameraSetPosition(0.0f, 0.0f, false, true, false);

	WinX = AEGfxGetWinMaxX() * 2;
	WinY = AEGfxGetWinMaxY() * 2;

	displayObject = CreateObject("Display", ObjTag);
	sprintf_s(displayBuffer, 16, "Fighters");
	displayTransform = TransformCreate(0, 0);
	TransformSetRotation(displayTransform, 0);
	PrintText(displayObject, displayBuffer, displaySprite, displayTransform);

	display2Object = CreateObject("Display2", ObjTag);
	sprintf_s(display2Buffer, 16, "Remaining:");
	display2Transform = TransformCreate(0, 0);
	TransformSetRotation(display2Transform, 0);
	PrintText(display2Object, display2Buffer, display2Sprite, display2Transform);

	display3Object = CreateObject("Display3", ObjTag);
	sprintf_s(display3Buffer, 16, "%d", ActiveHumanCount);
	display3Transform = TransformCreate(0, 0);
	TransformSetRotation(display3Transform, 0);
	PrintText(display3Object, display3Buffer, display3Sprite, display3Transform);

	continueObject = CreateObject("Continue", ObjTag);
	sprintf_s(continueBuffer, 16, "Continue");
	continueTransform = TransformCreate(0, 0);
	TransformSetRotation(continueTransform, 0);
	PrintText(continueObject, continueBuffer, continueSprite, continueTransform);

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

	victoryGameObject = CreateObject("Victory", ObjTag);
	victoryTransform = TransformCreate(0, 0);
	AEVec2 victoryScale = { 250, 250 };
	TransformSetRotation(victoryTransform, 0);
	TransformSetScale(victoryTransform, &victoryScale);
	victorySprite = SpriteCreate("Victory Sprite");
	SpriteSetMesh(victorySprite, victoryVertexList);
	SpriteSetSpriteSource(victorySprite, victorySpriteSource);
	ObjectSetTransform(victoryTransform, victoryGameObject);
	ObjectSetSprite(victorySprite, victoryGameObject);

	stopSong();
	playSong(8);

  sceneStarting = true;
  isPaused = true;
  sceneStartTimer = 3.0f;
  blackAlpha = 1.0f;
  SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);

  pTransBR = ObjectGetTransform(ObjectGetObject(pHumBR,NULL,NULL,NULL));

}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateBattleRoyaleUpdate(float dt)
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
        else if (sceneStartTimer > 1)
            SpriteSetText(ObjectGetSprite(startText), startTextTimerString[1]);
        else if (sceneStartTimer > 0)
            SpriteSetText(ObjectGetSprite(startText), startTextTimerString[2]);
        else
        {
            sceneStarting = false;
            isPaused = false;
            blackAlpha = .0f;
            SpriteSetAlpha(ObjectGetSprite(blackObj), blackAlpha);
        }
        if (sceneStartTimer > 0)
            DrawObject(startText);  //Draw "3", "2", "1"
        return;
    }

    if (vibrateTime <= 0)
    {
        vibrateTime = -1.0f;
        ControllerVibrate(0, 0.0f, 0.0f);
    }
    if (vibrateTime >= 0)
        vibrateTime -= dt;
  //UpdateHealth();
  

    DrawObject(arena);
    BattleRoyaleUpdateHumans();
	/*ParticleEmitterUpdateEmitter(dt);
	ParticleManagerUpdateParticles(dt);*/
  DamagePopupsDraw();
  CameraUpdate();
  UpdateItems();
	displayhumancount();
	HumanDrawHealth(pHumBR);
	HumanDrawStamina(pHumBR);
  DisplayKillFeed();
  //player indicator triangle rendering
  if (pHumBR)
  {
    //AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);
    AEVec2 playerIndicatorPos;
    AEVec2Add(&playerIndicatorPos, TransformGetTranslation(pTransBR), &pIndicatorOffset);
    TransformSetTranslation(pIndicatorTrans, &playerIndicatorPos);
    SpriteDraw(pIndicatorSprite, pIndicatorTrans);
    playerKills = HumanGetKillCount(pHumBR);
  }
  AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

#pragma region INPUT

  /*if (AEInputCheckTriggered('1'))
  {
      GameStateManagerSetNextState(GsLevel1);
  }
  else if (AEInputCheckTriggered('2'))
  {
      GameStateManagerSetNextState(GsBREnd);
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
      GameStateManagerSetNextState(GsRestart);
  }
  else */if (/*AEInputCheckTriggered('P') || */GetStartButton())
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
		  else if (button == 2)
			  GameStateManagerSetNextState(GsMenu);
		  else if (button == 3)
			  GameStateManagerSetNextState(GsQuit);
	  }
  }

  if (setkill == 1)
  {
	  if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
	  {
		  GameStateManagerSetNextState(GsBREnd);
	  }
  }
}

// Free any memory associated with the Battle Royale game state.
void GameStateBattleRoyaleShutdown()
{
    ResetItemDrawer();
    ResetKillFeed();
    CameraReset();
    BattleRoyaleFreeHumans();
    ResetDamagePopupDrawer();
	//ParticleManagerClear();
	//ParticleEmitterClear();
	FreeObject(&continueObject);
	FreeObject(&highlighterGameObject);
	FreeObject(&victoryGameObject);
}

// Unload the resources associated with the Battle Royale game state.
void GameStateBattleRoyaleUnload()
{
    AEGfxMeshFree(mesh1x1);
    //AEGfxMeshFree(mesh16x6);
    //AEGfxTextureUnload(textPNG);
    //SpriteSourceFree(&textSS);
    SpriteSourceFree(&arenaSS);
    //FreeObject(&pHealthTextObj);
    //FreeObject(&eHealthTextObj);
    FreeObject(&arena);
    AEGfxTextureUnload(arenaPNG);
    //FreeEnemy(&enemy);
    //HumanResetTargets(pHumBR);
    DamagePopupsFree();
	SpriteSourceFree(&highlighterSpriteSource);
	AEGfxTextureUnload(highlighterTexture);
	AEGfxMeshFree(highlighterVertexList);
	SpriteSourceFree(&continueSpriteSource);
	AEGfxTextureUnload(continueTexture);
	AEGfxMeshFree(continueVertexList);
	SpriteSourceFree(&victorySpriteSource);
	AEGfxTextureUnload(victoryTexture);
	AEGfxMeshFree(victoryVertexList);

  SpriteFree(&pIndicatorSprite);
  TransformFree(&pIndicatorTrans);

  FreeKillFeed();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static EnemyPtr CreateRandomEnemy()
{
    AIFightFunctionPtr fightStyle = NULL;
    int randInt = RandomRange(0, 4);
    switch (randInt)
    {
    case 0:
        fightStyle = AIFightBlockFocus;
        break;
    case 1:
        fightStyle = AIFightAttackFocus;
        break;
    case 2:
        fightStyle = AIFightDodgeFocus;
        break;
    case 3:
        fightStyle = AIFIghtCustom;
        break;
    case 4:
        fightStyle = AIFightRandom;
        break;
    }

    EnemyPtr enemy = CreateEnemy("Enemy", EnemyTag, 100, 100, 0, RandomRangeFloat(3.0f,5.0f)*5, RandomRangeFloat(5.0f,10.0f)*5, 0.01f, fightStyle, 7, 5, 1, 2, 7, false, false);


    AEVec2 translate;
    translate.x = RandomRangeFloat(-900.0f, 960.0f);
    translate.y = RandomRangeFloat(-500.0f, 500.0f);

    ObjectPtr obj = ObjectGetObject(NULL, NULL, NULL, enemy);
    TransformPtr trans = ObjectGetTransform(obj);

    AEVec2 scale = { 20, 30 };
    ColliderSetScale(ObjectGetCollider(obj), &scale);

    TransformSetTranslation(trans, &translate);

    HumanSetWeapon(HumanGetHuman(NULL, enemy), WoodSword);
    int helms[3] = { LeatherHelm,IronHelm,SteelHelm };
    int chests[3] = { LeatherChest,IronChest,SteelChest };
    int legs[3] = { LeatherBoots,IronBoots,SteelBoots };
    int swords[3] = { WoodSword,IronSword,SteelSword };
    HumanSetArmors(HumanGetHuman(NULL,enemy),helms[RandomRange(0,2)],chests[RandomRange(0,2)],legs[RandomRange(0,2)]);
    HumanSetWeapon(HumanGetHuman(NULL, enemy), swords[RandomRange(0, 2)]);
    EquipItem(HumanGetInventoryWorn(HumanGetHuman(NULL,enemy)), DefaultShield);
    return enemy;
}

static void BattleRoyaleUpdateHumans()
{
	ActiveHumanCount = 0;
    mostKills = 0;
    for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
    {
        if (ActiveHumanList[i]) //human exists
        {
            if (!HumanGetBool(ActiveHumanList[i], 0, 0, 0, 1, 0, 0)) //human is alive
            {
                UpdateHuman(ActiveHumanList[i]);
				        ActiveHumanCount++;
                if (HumanGetKillCount(ActiveHumanList[i]) > mostKills)
                {
                    mostKills = HumanGetKillCount(ActiveHumanList[i]);
                    killLeader = ActiveHumanList[i];        //update kill leader
                }
            }
            else
            {
                for (int j = 0; j < MAXOBJECTAMOUNT; ++j)
                {
                    if (!DeadHumanList[j])
                    {
						if (ActiveHumanList[i] == pHumBR)
						{
							pHumBR = NULL;
						}
                        DeadHumanList[j] = ActiveHumanList[i];
                        ActiveHumanList[i] = NULL;
                        ++DeadHumanCount;
                        break;
                    }
                }
            }
        }
        if (DeadHumanList[i])
        {
            if (UpdateHuman(DeadHumanList[i]))
            {
                DeadHumanList[i] = NULL;
                --DeadHumanCount;
            }
        }
    }     
	  if (!pHumBR && setkill == 0)
	  {
		  BRplacing = ActiveHumanCount + 1;
		  spectate = 1;
		  setkill = 1;
		  wavy = 1;
	  }
    if (pastKillLeader)                                  //kill leader stuff
    {                                                    //kill leader stuff
        if (killLeader != pastKillLeader)                //kill leader stuff
        {                                                //kill leader stuff
            HumanSetKillLeader(pastKillLeader, false);   //kill leader stuff
            HumanSetKillLeader(killLeader, true);        //kill leader stuff
        }                                                //kill leader stuff
    }                                                    //kill leader stuff
    else                                                 //kill leader stuff
    {                                                    //kill leader stuff
        pastKillLeader = killLeader;                     //kill leader stuff
        HumanSetKillLeader(killLeader, true);            //kill leader stuff
    }

    for (int i = 0; i < MAXOBJECTAMOUNT; ++i) //update collisions
    {
        if (ActiveHumanList[i]) //human exists
            CollisionUpdate(ObjectGetObject(ActiveHumanList[i],NULL,NULL,NULL));
    }
    for (int i = 0; i < MAXOBJECTAMOUNT; ++i) //remove dead humans from alive human's potential targets
    {
        for (int j = 0; j < DeadHumanCount; ++j)
        {
            HumanRemoveTarget(ActiveHumanList[i], DeadHumanList[j]);
        }
    }
    DrawItemsInQueue();
}

static void BattleRoyaleSpawnHumans()
{
    playerBR = CreatePlayer("player", PlayerTag, 100, 100, 10, 35, 130, 45, true, true);
    pHumBR = HumanGetHuman(playerBR,NULL);
    ActiveHumanList[0] = pHumBR;
    AEVec2 pos = { 0 };
    pos.x = -arenaScale.x / 4;
    //AEVec2 humanScale = { 102.3f,60.0f };

    ObjectPtr obj = ObjectGetObject(pHumBR, NULL, NULL, NULL);
    TransformPtr trans = ObjectGetTransform(obj);

    AEVec2 scale = { 20, 30 };
    ColliderSetScale(ObjectGetCollider(obj), &scale);

    TransformSetTranslation(trans, &pos);
    //TransformSetScale(trans, &humanScale);
    EquipItem(HumanGetInventoryWorn(pHumBR), WoodSword);
    EquipItem(HumanGetInventoryWorn(pHumBR), ClothHelm);
    EquipItem(HumanGetInventoryWorn(pHumBR), ClothChest);
    EquipItem(HumanGetInventoryWorn(pHumBR), ClothBoots);
    EquipItem(HumanGetInventoryWorn(pHumBR), DefaultShield);

    for (int i = ActiveHumanCount; i < MAXOBJECTAMOUNT; ++i)
    {
        ActiveHumanList[i] = (HumanPtr)CreateRandomEnemy();
		int randNameIndex = RandomRange(0, NamesMax - 1);
		while (nameChosen[randNameIndex]) //while name is already taken
		{
			randNameIndex = RandomRange(0, NamesMax - 1); //choose a different one
		}
		HumanSetName(ActiveHumanList[i], names[randNameIndex]); //set the name
		nameChosen[randNameIndex] = true; //tell namesChosen that that name is now taken
        ++ActiveHumanCount;
    }
}

static void BattleRoyaleSetAllTargets()
{
    for (int i = 0; i < ActiveHumanCount; ++i)
    {
        if (ObjectGetTag(ObjectGetObject(ActiveHumanList[i], NULL, NULL, NULL)) == EnemyTag)
        {
            HumanAddTarget(pHumBR, ActiveHumanList[i]);
            HumanSetTargets(ActiveHumanList[i], ActiveHumanList);
        }
    }
}

static void BattleRoyaleFreeHumans()
{
    for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
    {
        if (ActiveHumanList[i])
        {
            if (ObjectGetTag(ObjectGetObject(ActiveHumanList[i], NULL, NULL, NULL)) == PlayerTag)
                FreeHuman(&ActiveHumanList[i]);
            else if (ObjectGetTag(ObjectGetObject(ActiveHumanList[i], NULL, NULL, NULL)) == EnemyTag)
                FreeEnemy(&(EnemyPtr)ActiveHumanList[i]);
            ActiveHumanList[i] = NULL;
        }
        if (DeadHumanList[i])
        {
            if (ObjectGetTag(ObjectGetObject(DeadHumanList[i], NULL, NULL, NULL)) == PlayerTag)
                FreeHuman(&DeadHumanList[i]);
            else if (ObjectGetTag(ObjectGetObject(DeadHumanList[i], NULL, NULL, NULL)) == EnemyTag)
                FreeEnemy(&(EnemyPtr)DeadHumanList[i]);
            DeadHumanList[i] = NULL;
        }
    }
}
/*
static void UpdateHealth()
{
	float health = HumanGetHealth(HumanGetHuman(playerBR, NULL));
	if (health != 100)
	{
 		health = health;
	}
	DrawFilledRect(-700 - (400 - (health * 4)), 490, health * 4, 20); //player health bar
}*/

static void displayhumancount()
{
	if (setkill == 0)
	{
		AEVec2 position = { 0 };
		CameraGetPosition(&position.x, &position.y);
		position.x += -WinX / (float)2.25;
		position.y += WinY / (float)2.6;
		TransformSetTranslation(displayTransform, &position);
		DrawObject(displayObject);

		AEVec2 position2 = { 0 };
		CameraGetPosition(&position2.x, &position2.y);
		position2.x += -WinX / (float)2.25;
		position2.y += WinY / (float)2.9;
		TransformSetTranslation(display2Transform, &position2);
		DrawObject(display2Object);

		AEVec2 position3 = { 0 };
		AEVec2 Scale = { 0, 0 };
		CameraGetPosition(&position3.x, &position3.y);
		position3.x += -WinX / (float)2.3;
		position3.y += WinY / (float)3.5;
		Scale.x = 50;
		Scale.y = 50;
		TransformSetTranslation(display3Transform, &position3);
		TransformSetScale(display3Transform, &Scale);
		DrawObject(display3Object);

		//kills counter for player
		AEVec2 topMid;
		CameraGetPosition(&topMid.x, &topMid.y);
		topMid.x -= 75.0f;
		topMid.y += 500.0f;
		sprintf_s(spectatingBuffer, 64, "Kills: %d", playerKills);
		SpriteSetText(ObjectGetSprite(spectatingTextObj), spectatingBuffer);
		TransformSetTranslation(ObjectGetTransform(spectatingTextObj), &topMid);
		SpriteDraw(ObjectGetSprite(spectatingTextObj), ObjectGetTransform(spectatingTextObj));
	}

	if (setkill == 1)
	{
		if (wavy == 1)
		{
			if (alphaH >= 1.0f)
			{
				wavy = 2;
			}
			alphaH += 0.03f;
		}
		if (wavy == 2)
		{
			if (alphaH <= 0.2f)
			{
				wavy = 1;
			}
			alphaH -= 0.03f;
		}

		AEVec2 contPos = { 0 };
		AEVec2 contScale = { 0, 0 };
		CameraGetPosition(&contPos.x, &contPos.y);
		contPos.x -= 115.0f;
		contPos.y -= WinY / 2.3f;
		contScale.x = 50;
		contScale.y = 50; 
		TransformSetTranslation(continueTransform, &contPos);
		TransformSetScale(continueTransform, &contScale);
		DrawObject(continueObject);

		AEVec2 highlightPos = { 0 };
		AEVec2 highlightScale = { 0, 0 };
		CameraGetPosition(&highlightPos.x, &highlightPos.y);
		highlightPos.y -= WinY / 2.27f;
		highlightScale.x = 550;
		highlightScale.y = 400;
		TransformSetTranslation(highlighterTransform, &highlightPos);
		TransformSetScale(highlighterTransform, &highlightScale);
		SpriteSetAlpha(highlighterSprite, alphaH);
		DrawObject(highlighterGameObject);

		//kills counter for player
		AEVec2 topMid;
		CameraGetPosition(&topMid.x, &topMid.y);
		topMid.x -= 75.0f;
		topMid.y += 500.0f;
		sprintf_s(spectatingBuffer, 64, "Kills: %d", playerKills);
		SpriteSetText(ObjectGetSprite(spectatingTextObj), spectatingBuffer);
		TransformSetTranslation(ObjectGetTransform(spectatingTextObj), &topMid);
		SpriteDraw(ObjectGetSprite(spectatingTextObj), ObjectGetTransform(spectatingTextObj));

		if (spectate == 1)
		{
			AEVec2 topLeft;
			CameraGetPosition(&topLeft.x, &topLeft.y);
			topLeft.x -= 930.0f;
			topLeft.y += 500.0f;
			sprintf_s(spectatingBuffer, 64, "Spectating: %s", HumanGetName(killLeader));
			SpriteSetText(ObjectGetSprite(spectatingTextObj), spectatingBuffer);
			TransformSetTranslation(ObjectGetTransform(spectatingTextObj), &topLeft);
			SpriteDraw(ObjectGetSprite(spectatingTextObj), ObjectGetTransform(spectatingTextObj));

			//kills counter for kill leader
			topMid.x -= 855.0f;
			topMid.y -= 100.0f;
			sprintf_s(spectatingBuffer, 64, "Kills: %d", HumanGetKillCount(killLeader));
			SpriteSetText(ObjectGetSprite(spectatingTextObj), spectatingBuffer);
			TransformSetTranslation(ObjectGetTransform(spectatingTextObj), &topMid);
			SpriteDraw(ObjectGetSprite(spectatingTextObj), ObjectGetTransform(spectatingTextObj));
		}
	}

	if (ActiveHumanCount == 1)
	{
		if (!pHumBR)
		{
			fadeout += 0.006f;
			SpriteSetAlpha(ObjectGetSprite(blackObj), fadeout);
			DrawObject(blackObj);
			if (fadeout >= 1.0f)
				GameStateManagerSetNextState(GsBREnd);
		}
		if (pHumBR)
		{
			BRplacing = 1;
			setkill = 1;
			wavy = 1;

			AEVec2 victoryPos = { 0 };
			AEVec2 victoryScale = { 0, 0 };
			CameraGetPosition(&victoryPos.x, &victoryPos.y);
			victoryScale.x = 1450;
			victoryScale.y = 600;
			TransformSetTranslation(victoryTransform, &victoryPos);
			TransformSetScale(victoryTransform, &victoryScale);
			SpriteSetAlpha(ObjectGetSprite(blackObj), 0.2f);
			DrawObject(blackObj);
			DrawObject(victoryGameObject);
		}
	}
	sprintf_s(display3Buffer, 16, "%d", ActiveHumanCount);
}

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform)
{

	AEVec2 scale;
	TransformSetRotation(pTransform, 0);
	scale.x = 25;
	scale.y = 25;
	TransformSetScale(pTransform, &scale);

	pSpriteSrc = SpriteCreate("Dsplay Sprite");
	SpriteSetMesh(pSpriteSrc, displayVertexList);
	SpriteSetSpriteSource(pSpriteSrc, displaySpriteSource);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}

#pragma region KILLFEED

static void KillFeedInit()
{
  killFeedSprite = SpriteCreate("KillFeed");
  SpriteSetMesh(killFeedSprite, mesh16x6);
  SpriteSetSpriteSource(killFeedSprite, textSS);
  killFeedTrans = TransformCreate(0.0f, 0.0f);
  AEVec2 killFeedScale;
  killFeedScale.x = 20.0f;
  killFeedScale.y = 20.0f;
  TransformSetScale(killFeedTrans, &killFeedScale);
	for (int i = 0; i < KILLFEED_LENGTH; ++i)
	{
		killFeedStrings[i] = calloc(64, sizeof(char));
	}
}

void QueueKill(const char* killer, const char* dead)
{
  if (!strcmp(dead,"player"))
    dead = "You";
 	for (int i = KILLFEED_LENGTH - 1; i > 0; --i)
	{
    strcpy_s(killFeedStrings[i], 64, killFeedStrings[i - 1]);
	}
  sprintf_s(killFeedStrings[0], 64, "%s -> %s", killer, dead);
}

static void DisplayKillFeed()
{
  for (int i = 0; i < KILLFEED_LENGTH; ++i)
  {
    SpriteSetText(killFeedSprite, killFeedStrings[i]);
    AEVec2 pos;
    CameraGetPosition(&pos.x, &pos.y);
    pos.x += 525.0f;
    pos.y = AEGfxGetWinMaxY() - (30 * i) - 30;
    TransformSetTranslation(killFeedTrans, &pos);
    SpriteSetAlpha(killFeedSprite, killFeedAlphas[i]);
    SpriteDraw(killFeedSprite, killFeedTrans);
  }
}

static void ResetKillFeed()
{
	//killFeedX = 0.0f;
	for (int i = 0; i < KILLFEED_LENGTH; ++i)
	{
		//killFeedYs[i] = 0.0f;
		killFeedSlotActive[i] = false;
    *killFeedStrings[i] = 0;
    
		//killFeedStrings[i] = NULL;
	}
  for (int i = 0; i < NamesMax; ++i)
    nameChosen[i] = false;

}

static void FreeKillFeed()
{
  SpriteFree(&killFeedSprite);
  killFeedSprite = NULL;
  TransformFree(&killFeedTrans);
  killFeedTrans = NULL;
	for (int i = 0; i < KILLFEED_LENGTH; ++i)
	{
		free(killFeedStrings[i]);
		killFeedStrings[i] = NULL;
	}
}

#pragma endregion KILLFOOD