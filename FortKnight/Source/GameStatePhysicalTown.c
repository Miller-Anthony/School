//------------------------------------------------------------------------------
//
// File Name:	GameStatePhysicalTown.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "GameStateManager.h"
#include "GameStatePhysicalTown.h"
#include "Trace.h"
#include "Input.h"
#include "Mesh.h"
#include "Objects.h"
#include "Sound.h"
#include "OST.h"
#include "Text.h"
#include "Player.h"
#include "Collision.h"
#include "Camera.h"
#include "text.H"
#include "ItemData.h"
#include "ParticleEmitter.h"
#include "ParticleManager.h"
#include "PauseMenu.h"
#include "Utils.h"
#include "Animation.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//sound
static FMOD_SOUND* townSound;

//Sprites
static SpriteSourcePtr townSpriteSource;

//textures
static const char* townFile = "./Assets/Town.png";
static AEGfxTexture* townPNG;
static AEGfxVertexList* mesh16x6;
static AEGfxTexture* textPNG;
static SpriteSourcePtr textSS;

//meshes
static AEGfxVertexList* mesh1x1;
static AEGfxVertexList* pMeshLine;

//Player
extern PlayerPtr player;
extern bool isPaused;
static ObjectPtr pObj;
extern HumanPtr pHum;

int button = 0;
int flag = 0;
int menuFlag = 0;

//town
static ObjectPtr town;
static AEVec2 townScale = { 1920, 1080 };
static AEVec2 townPos = { 0.0f,155.0f };

//collider
ColliderPtr collider1;
ColliderPtr collider2;
ColliderPtr collider3;
ColliderPtr collider4;
ColliderPtr collider5;
ColliderPtr collider6;

//collider objects
ObjectPtr colliderObject1;
ObjectPtr colliderObject2;
ObjectPtr colliderObject3;
ObjectPtr colliderObject4;
ObjectPtr colliderObject5;
ObjectPtr colliderObject6;

//trigger objects
ObjectPtr triggerObjectArena;
ObjectPtr triggerObjectArmorShop; 
ObjectPtr triggerObjectHome;

//NPC
EnemyPtr NPCEnemy;
ObjectPtr NPCObj;
HumanPtr NPCHum;

ObjectPtr NPCText;
static char* NPCTextString = NULL;
static char* NPCTextString1 = "Go to the Armor to upgrade your weapons!";
static char* NPCTextString2 = "Time your blocks to perform a perfect block";
static char* NPCTextString3 = "Go to the arena to fight! Hopefully not lose";
static char* NPCTextString4 = "Win a game to gain gold! Then spend the gold!";
static char* NPCTextString5 = "Your Armor is impressive! I love the design!";
static char* NPCTextString6 = "Your last fight was amazing! Well done!";
static AEVec2 NPCTextScale = { 15.0f, 15.0f };
static AEVec2 NPCTextPos;
static float textTimer = 0.0f;
static float NPCTimer = 0.0f;
static float NPCPauseTimer = 0.0f;
static int direction = 0;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static float eWidth = 0;  //current width of the mesh
static float eHeight = 0; //current height of the mesh
static AEVec2 lastPosition = { 500.0f, 25.0f};

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//static void DrawRectangle(float x, float y, float w, float h);
static void InitColliders();
static void InitTriggerObjects();
static bool distanceBetween(ObjectPtr player, ObjectPtr object, float distance);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the PhysicalTown game state.
void GameStatePhysicalTownLoad()
{
	mesh1x1 = MeshCreateQuad(.5f, .5f, 1.0f, 1.0f, "Mesh1x1");
	mesh16x6 = MeshCreateQuad(.5f, .5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");

	//town
	town = CreateObject("Town", ObjTag);
	townPNG = AEGfxTextureLoad(townFile);
	townSpriteSource = SpriteSourceCreate(1, 1, townPNG);
	SpriteSourceSetTexture(townSpriteSource, townPNG);
	SpriteSetMesh(ObjectGetSprite(town), mesh1x1);
	SpriteSetSpriteSource(ObjectGetSprite(town), townSpriteSource);
	TransformSetTranslation(ObjectGetTransform(town), &townPos);
	TransformSetScale(ObjectGetTransform(town), &townScale);

	//text
	textPNG = AEGfxTextureLoad("./Assets/Text_White.png");
	textSS = SpriteSourceCreate(16, 6, textPNG);
	SpriteSourceSetTexture(textSS, textPNG);
	NPCText = CreateObject("NPC Text", ObjTag);
	SpriteSetSpriteSource(ObjectGetSprite(NPCText), textSS);
	SpriteSetMesh(ObjectGetSprite(NPCText), mesh16x6);

	ParticleEmitterCreateTemplate(cTemplateSpark, 1.5f);
	ParticleEmitterCreateTemplate(cTemplateDirt, 1.0f);
}

// Initialize the memory associated with the PhysicalTown game state.
void GameStatePhysicalTownInit()
{
	pHum = PlayerGetHuman();
	pObj = ObjectGetObject(pHum, NULL, NULL, NULL);
  HumanSetSpeed(pHum, 30.0f);
  HumanSetDodgeSpeed(pHum, 125.0f);
	TransformSetTranslation(ObjectGetTransform(pObj), &lastPosition);
	isPaused = false;

	pauseInit();
	InitColliders();
	InitTriggerObjects();
	ControllerVibrate(0,0,0);
	playSong(0);

	NPCEnemy = CreateEnemy("NPC", EnemyTag, 100, 100, 5, 150, 100, 10, NULL, 12, 8, 3, 5, 10, true, true);
	NPCHum = HumanGetHuman(NULL, NPCEnemy);
	HumanSetWeapon(HumanGetHuman(NULL, NPCEnemy), IronSword);
	HumanSetArmors(NPCHum, IronHelm, IronChest, IronBoots);

	NPCObj = ObjectGetObject(NPCHum, NULL, NULL, NULL);
	TransformPtr NPCTrans = ObjectGetTransform(NPCObj);
	AEVec2 NPCPos = { 0.0f, 0.0f};
	TransformSetTranslation(NPCTrans, &NPCPos);

	AEVec2 scale = { 20, 30 };
	ColliderSetScale(ObjectGetCollider(NPCObj), &scale);
	CameraSetPosition(0.0f, 155.0f, false, false, false);
}

// Update the PhysicalTown game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStatePhysicalTownUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	CameraOverrideSmoothing(0.0f, 155.0f, 10.0f, true);

	UpdateHuman(pHum);
	UpdateHuman(NPCHum);
	CollisionUpdate(pObj);
	DrawObject(town);
	ParticleManagerDrawParticles(cTemplateDirt);
	DrawItemsInQueue();
	ParticleManagerDrawParticles(cTemplateSpark);
	UpdateItems();
	CameraUpdate();
	ParticleEmitterUpdateEmitter(dt);
    ParticleManagerUpdateParticles(dt);
	
	if (NPCTimer > 0.0f)
	{
		AEVec2 position = *TransformGetTranslation(ObjectGetTransform(NPCObj));
		float speed = HumanGetSpeed(NPCHum);

		switch (direction)
		{
		case 0:
			position.x += speed * dt;
			break;
		case 1:
			position.x -= speed * dt;
			break;
		case 2:
			position.y += speed * dt;
			break;
		case 3:
			position.y -= speed * dt;
			break;
		}

		if (position.x > 600)
		{
			position.x = 450;
		}
		if (position.x < -450)
		{
			position.x = -450;
		}
		if (position.y > 400)
		{
			position.y = 300;
		}
		if (position.y < -200)
		{
			position.y = -200;
		}

		if (CollidercheckCollision(ObjectGetCollider(NPCObj), ObjectGetCollider(pObj)) == false)
		{
			TransformSetTranslation(ObjectGetTransform(NPCObj), &position);
		}

		NPCTimer -= dt;
	}

	if (NPCTimer <= 0.0f)
	{
		NPCPauseTimer = RandomRangeFloat(0, 3);
		HumanSetNextState(NPCHum, HSidle);
	}
	
	if(NPCPauseTimer > 0.0f)
	{
		NPCPauseTimer -= dt;
	}

	if (NPCPauseTimer <= 0.0f && NPCTimer <= 0.0f)
	{
		direction = RandomRange(0, 3);

		HumanSetNextState(NPCHum, HSrun);

		switch (direction)
		{
		case 0:
			HumanSetFaceDir(NPCHum, right);
			break;
		case 1:
			HumanSetFaceDir(NPCHum, left);
			break;
		case 2:
			HumanSetFaceDir(NPCHum, up);
			break;
		case 3:
			HumanSetFaceDir(NPCHum, down);
			break;
		}

		NPCTimer = 1.0f;
	}

	if (textTimer > 0.0f)
	{
		NPCTextPos = *TransformGetTranslation(ObjectGetTransform(NPCObj));
		NPCTextPos.x -= 300.0f;
		NPCTextPos.y += 125.0f;
		TransformSetScale(ObjectGetTransform(NPCText), &NPCTextScale);
		TransformSetTranslation(ObjectGetTransform(NPCText), &NPCTextPos);
		SpriteSetText(ObjectGetSprite(NPCText), NPCTextString);
		DrawObject(NPCText);
		textTimer -= dt;
	}

	if (GetButton(0,0) && textTimer <= 0.0f)
	{
		if (distanceBetween(NPCObj, pObj, 150.0f) == true)
		{
			textTimer = 3.0f;

			int randomText = RandomRange(1, 6);
			
			switch (randomText)
			{
			case 1:
				NPCTextString = NPCTextString1;
				break;
			case 2:
				NPCTextString = NPCTextString2;
				break;
			case 3:
				NPCTextString = NPCTextString3;
				break;
			case 4:
				NPCTextString = NPCTextString4;
				break;
			case 5:
				NPCTextString = NPCTextString5;
				break;
			case 6:
				NPCTextString = NPCTextString6;
				break;
			}
		}
	}

	if (GetStartButton())
	{
		if (!isPaused)
			isPaused = true;
		else
			isPaused = false;
	}
	flag++;
	if (flag % 12 == 0)
		menuFlag = 0;

	if ((GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f) && menuFlag == 0)
	{
		button++;
		if (button > 3)
			button = 0;
		menuFlag = 1;
		flag = 0;
	}
	else if (( GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f) && menuFlag == 0)
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

		if (GetButtonDown(0, 0))
		{
			isPaused = false;

			if (button == 0)
				isPaused = false;
			else if (button == 1)
				GameStateManagerSetNextState(GsPhysicalTown);
			else if (button == 2)
				GameStateManagerSetNextState(GsPhysicalTown);
			else if (button == 3)
				GameStateManagerSetNextState(GsQuit);
		}
	}

	if (GetButton(0, 0)/* || AEInputCheckTriggered('1')*/)
	{
		if (distanceBetween(pObj, triggerObjectArena, 150.0f) == true)
		{
			CameraSetPosition(0.0f, 0.0f, false, true, false);
			GameStateManagerSetNextState(GsTown);
		}
		else if (distanceBetween(pObj, triggerObjectArmorShop, 150.0f) == true)
		{
			CameraSetPosition(0.0f, 0.0f, false, true, false);
			GameStateManagerSetNextState(GsArmorShop);
		}
		/*
		else if (distanceBetween(pObj, triggerObjectHome, 150.0f) == true)
		{
			CameraSetPosition(0.0f, 0.0f, false, true, false);
			GameStateManagerSetNextState(GsMenu);
		}
		*/
	}
}

// Free any memory associated with the PhysicalTown game state.
void GameStatePhysicalTownShutdown()
{
	// Free all objects.
	ParticleManagerClear();
	ParticleEmitterClear();
	ColliderDelete(&collider1);
	ColliderDelete(&collider2);
	ColliderDelete(&collider3);
	ColliderDelete(&collider4);
	ColliderDelete(&collider5);
	ColliderDelete(&collider6);

	FreeObject(&town);
	FreeObject(&triggerObjectArmorShop);
	FreeObject(&triggerObjectArena);
	FreeObject(&triggerObjectHome);
	FreeObject(&NPCObj);

	lastPosition = *TransformGetTranslation(ObjectGetTransform(pObj));
}

// Unload the resources associated with the PhysicalTown game state.
void GameStatePhysicalTownUnload()
{
	// Free all sprite sources.
	SpriteSourceFree(&townSpriteSource);
	SpriteSourceFree(&textSS);
	// Unload all textures.
	AEGfxTextureUnload(townPNG);
	AEGfxTextureUnload(textPNG);
	// Free all meshes.
	AEGfxMeshFree(pMeshLine);
	AEGfxMeshFree(mesh1x1);
	AEGfxMeshFree(mesh16x6);
  CameraReset();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

/*
static void DrawRectangle(float x, float y, float w, float h)
{
	if (eWidth != w || eHeight != h || !pMeshLine)
	{
		AEGfxMeshFree(pMeshLine);
		pMeshLine = NULL;
		eWidth = w;
		eHeight = h;
		AEGfxMeshStart();
		// This shape has 4 vertices
		AEGfxVertexAdd(x - w, y - h, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(x + w, y - h, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(x + w, y + h, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(x - w, y + h, 0xFF000000, 0.0f, 0.0f);
		AEGfxVertexAdd(x - w, y - h, 0xFF000000, 0.0f, 0.0f);
		pMeshLine = AEGfxMeshEnd();
		AE_WARNING_MESG(pMeshLine, "Failed to create mesh 2!!");
	}

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxSetPosition(x, y);
	AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);
}*/

static void InitColliders()
{
	colliderObject1 = CreateObject("colliderObject1", EnemyTag);
	TransformPtr transform1 = TransformCreate(0.0f, 650.0f);
	AEVec2 scale1 = { 900.0f, 50.0f };
	TransformSetScale(transform1, &scale1);
	ObjectSetTransform(transform1, colliderObject1);

	collider1 = ColliderCreate();
	ColliderSetTransform(collider1, transform1);
	ColliderSetParent(collider1, colliderObject1);
	
	colliderObject2 = CreateObject("colliderObject2", EnemyTag);
	TransformPtr transform2 = TransformCreate(0.0f, -300.0f);
	AEVec2 scale2 = { 900.0f, 50.0f };
	TransformSetScale(transform2, &scale2);
	ObjectSetTransform(transform2, colliderObject2);

	collider2 = ColliderCreate();
	ColliderSetTransform(collider2, transform2);
	ColliderSetParent(collider2, colliderObject2);

	colliderObject3 = CreateObject("colliderObject3", EnemyTag);
	TransformPtr transform3 = TransformCreate(-650.0f, 0.0f);
	AEVec2 scale3 = { 50.0f, 900.0f };
	TransformSetScale(transform3, &scale3);
	ObjectSetTransform(transform3, colliderObject3);

	collider3 = ColliderCreate();
	ColliderSetTransform(collider3, transform3);
	ColliderSetParent(collider3, colliderObject3);
	
	colliderObject4 = CreateObject("colliderObject4", EnemyTag);
	TransformPtr transform4 = TransformCreate(700.0f, 500.0f);
	AEVec2 scale4 = { 100.0f, 300.0f };
	TransformSetScale(transform4, &scale4);
	ObjectSetTransform(transform4, colliderObject4);

	collider4 = ColliderCreate();
	ColliderSetTransform(collider4, transform4);
	ColliderSetParent(collider4, colliderObject4);

	colliderObject5 = CreateObject("colliderObject5", EnemyTag);
	TransformPtr transform5 = TransformCreate(850.0f, 300.0f);
	AEVec2 scale5 = { 100.0f, 300.0f };
	TransformSetScale(transform5, &scale5);
	ObjectSetTransform(transform5, colliderObject5);

	collider5 = ColliderCreate();
	ColliderSetTransform(collider5, transform5);
	ColliderSetParent(collider5, colliderObject5);

	colliderObject6 = CreateObject("colliderObject6", EnemyTag);
	TransformPtr transform6 = TransformCreate(950.0f, 00.0f);
	AEVec2 scale6 = { 100.0f, 300.0f };
	TransformSetScale(transform6, &scale6);
	ObjectSetTransform(transform6, colliderObject6);

	collider6 = ColliderCreate();
	ColliderSetTransform(collider6, transform6);
	ColliderSetParent(collider6, colliderObject6);
}

static void InitTriggerObjects()
{
	triggerObjectArmorShop = CreateObject("trigger object armor shop", ObjTag);
	TransformPtr transformAmorShop = TransformCreate(-650.0f, 75.0f);
	AEVec2 scaleArmorShop = { 0.0f, 0.0f };
	TransformSetScale(transformAmorShop, &scaleArmorShop);
	ObjectSetTransform(transformAmorShop, triggerObjectArmorShop);

	triggerObjectHome = CreateObject("trigger object home", ObjTag);
	TransformPtr transformHome = TransformCreate(750.0f, 75.0f);
	AEVec2 scaleHome = { 0.0f, 0.0f };
	TransformSetScale(transformHome, &scaleHome);
	ObjectSetTransform(transformHome, triggerObjectHome);

	triggerObjectArena = CreateObject("trigger object Arena", ObjTag);
	TransformPtr transformArena = TransformCreate(0.0f, 650.0f);
	AEVec2 scaleArena = { 0.0f, 0.0f };
	TransformSetScale(transformArena, &scaleArena);
	ObjectSetTransform(transformArena, triggerObjectArena);
}

static bool distanceBetween(ObjectPtr object1, ObjectPtr object2, float distance)
{
	AEVec2 object1Pos = *TransformGetTranslation(ObjectGetTransform(object1));
	AEVec2 object2Pos = *TransformGetTranslation(ObjectGetTransform(object2));

	if (AEVec2Distance(&object1Pos, &object2Pos) < distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}