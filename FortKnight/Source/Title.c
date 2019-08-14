//------------------------------------------------------------------------------
//
// File Name:	Title.c
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
#include "Title.h"
#include "Sound.h"
#include "Mesh.h"
#include "Objects.h"
#include "Trace.h"
#include "SpriteSource.h"
#include "Input.h"
#include "Player.h"
#include "ItemData.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
static AEGfxVertexList * pLogoInit;
static AEGfxVertexList * pLogoFinal;
static AEGfxTexture * pLogoInitTexture;
static AEGfxTexture * pLogoFinalTexture;
static SpriteSourcePtr spriteSourceLogoInit;
static SpriteSourcePtr spriteSourceLogoFinal;

static AEGfxVertexList * teamlogoVertexList;
static AEGfxTexture * teamlogoTexture;
static SpriteSourcePtr teamlogoSpriteSource;

static ObjectPtr LogoInit;
static ObjectPtr LogoFinal;
static SpritePtr pSpriteLogoInit;
static SpritePtr pSpriteLogoFinal;
static TransformPtr pTransformLogoInit;
static TransformPtr pTransformLogoInit;

static ObjectPtr teamlogo;
static SpritePtr teamlogoSprite;
static TransformPtr teamlogoTransform;

static FMOD_SOUND* mainMenuSound;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static int logoDone = 0;
static int everythingDone = 0;
static float initAlpha = 0.0f;
static float initAlpha2 = 0.0f;
static float finalAlpha = 0.0f;
static float finalAlpha2 = 0.0f;
static AEVec2 positionInit = { 0, 0 };
unsigned int frame = 0;
unsigned int time = 0;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void TitleLoad()
{
	ItemTablePopulate();
	InitItemDrawer();
	PlayerCreate();
	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	teamlogoVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 4, 1.0f / 4, "Mesh1x1");
	teamlogoTexture = AEGfxTextureLoad("Assets/teamLogo.png");
	teamlogoSpriteSource = SpriteSourceCreate(4, 4, teamlogoTexture);
	teamlogoSprite = SpriteCreate("TeamLogo");

	pLogoInit = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	pLogoFinal = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	pLogoInitTexture = AEGfxTextureLoad("Assets/TitleInit.png");
	pLogoFinalTexture = AEGfxTextureLoad("Assets/TitleFinal.png");

	spriteSourceLogoInit = SpriteSourceCreate(1, 1, pLogoInitTexture);
	spriteSourceLogoFinal = SpriteSourceCreate(1, 1, pLogoFinalTexture);

	pSpriteLogoInit = SpriteCreate("LogoInit");
	pSpriteLogoFinal = SpriteCreate("LogoFinal");
}

// Initialize the memory associated with the Level1 game state.
void TitleInit()
{
	SoundModuleInit();
	SoundInit("./Assets/Sound/titleTrack.wav", FMOD_LOOP_OFF, &mainMenuSound);
	SoundPlay(&mainMenuSound, false);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEVec2 position = { 0.0f, 0.0f };
	AEVec2 scale = { 123.5, 123.5 };
	AEVec2 scale2 = { 512, 123.5f };
	AEVec2 scaleTeamLogo = { 512, 512 };
	
	teamlogo = CreateObject("TeamLogo", ObjTag);

	LogoInit = CreateObject("LogoInit", ObjTag);
	LogoFinal = CreateObject("LogoFinal", ObjTag);

	TransformPtr transformTeamLogo = ObjectGetTransform(teamlogo);

	TransformSetScale(transformTeamLogo, &scaleTeamLogo);
	TransformSetTranslation(transformTeamLogo, &position);
	SpriteSourceSetTexture(teamlogoSpriteSource, teamlogoTexture);
	ObjectSetSprite(teamlogoSprite, teamlogo);
	SpriteSetSpriteSource(teamlogoSprite, teamlogoSpriteSource);
	SpriteSetMesh(ObjectGetSprite(teamlogo), teamlogoVertexList);

	TransformPtr transform = ObjectGetTransform(LogoInit);
	TransformPtr transform2 = ObjectGetTransform(LogoFinal);

	TransformSetScale(transform, &scale);
	TransformSetTranslation(transform, &position);

	TransformSetScale(transform2, &scale2);
	TransformSetTranslation(transform2, &position);

	SpriteSourceSetTexture(spriteSourceLogoInit, pLogoInitTexture);
	SpriteSourceSetTexture(spriteSourceLogoFinal, pLogoFinalTexture);

	ObjectSetSprite(pSpriteLogoInit, LogoInit);
	ObjectSetSprite(pSpriteLogoFinal, LogoFinal);

	SpriteSetSpriteSource(ObjectGetSprite(LogoInit), spriteSourceLogoInit);
	SpriteSetSpriteSource(ObjectGetSprite(LogoFinal), spriteSourceLogoFinal);

	SpriteSetMesh(ObjectGetSprite(LogoInit), pLogoInit);
	SpriteSetMesh(ObjectGetSprite(LogoFinal), pLogoFinal);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void TitleUpdate(float dt)
{
	if (AEInputCheckTriggered(VK_RETURN) || GetButtonDown(0, 0))
	{
		SoundPlay(&mainMenuSound, TRUE);
		GameStateManagerSetNextState(GsMenu);
	}

	//SoundModuleUpdate();

	if(logoDone == 0)
	{

		if (finalAlpha < 0.9f)
		{
			initAlpha += 0.01f;
			SpriteSetAlpha(ObjectGetSprite(LogoInit), initAlpha);
		}
		else
		{
			initAlpha2 -= 0.01f;
			SpriteSetAlpha(ObjectGetSprite(LogoInit), initAlpha2);
		}

		//if (finalAlpha < 1.0f)
		DrawObject(LogoInit);

		if (initAlpha >= 1.0f)
		{
			positionInit.x -= 2;

			if (positionInit.x <= -194.5f && logoDone == 0)
			{
				positionInit.x = -194.5f;

				SpriteSetAlpha(ObjectGetSprite(LogoFinal), finalAlpha);
				finalAlpha += 0.01f;
				DrawObject(LogoFinal);

				if (finalAlpha >= 1.0f)
				{
					finalAlpha = 1.0f;
					logoDone = 1;
				}
			}
		}

		TransformPtr transform = ObjectGetTransform(LogoInit);
		TransformSetTranslation(transform, &positionInit);
	}

	if (logoDone == 1)
	{
		finalAlpha -= 0.01f;
		SpriteSetAlpha(ObjectGetSprite(LogoFinal), finalAlpha);
		DrawObject(LogoFinal);

		if (finalAlpha <= 0.0f)
			logoDone = 2;
	}
	if (logoDone == 2 && everythingDone == 0)
	{
		SpriteSetFrame(ObjectGetSprite(teamlogo), frame);
		DrawObject(teamlogo);
		time++;

		if (time % 20 == 0)
			frame++;

		if (frame >= 12)
			frame = 12;

		if (time % 260 == 0)
		{
			float alpha = 0.0f;
			SpriteSetAlpha(ObjectGetSprite(teamlogo), alpha);
		}

		if (time % 300 == 0)
			everythingDone = 1;
	}

	if (everythingDone == 1)
		GameStateManagerSetNextState(GsMenu);

	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

}

// Shutdown any memory associated with the Level1 game state.
void TitleShutdown()
{
	FreeObject(&LogoInit);
	FreeObject(&LogoFinal);
	FreeObject(&teamlogo);
}

// Unload the resources associated with the Level1 game state.
void TitleUnload()
{
	SoundFree(&mainMenuSound);

	AEGfxTextureUnload(pLogoInitTexture);
	AEGfxTextureUnload(pLogoFinalTexture);
	AEGfxTextureUnload(teamlogoTexture);

	AEGfxMeshFree(pLogoInit);
	AEGfxMeshFree(pLogoFinal);
	AEGfxMeshFree(teamlogoVertexList);

	SpriteSourceFree(&spriteSourceLogoFinal);
	SpriteSourceFree(&spriteSourceLogoInit);
	SpriteSourceFree(&teamlogoSpriteSource);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

