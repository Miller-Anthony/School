//------------------------------------------------------------------------------
//
// File Name:	SaveSelect.c
// Author(s):	Akshat Madan
// Project:		Knightmare
// Course:		CS230S19-A
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <AEEngine.h>
#include "GameStateManager.h"
#include "SaveSelect.h"
#include "Trace.h"
#include "Player.h"
#include "Input.h"
#include "Mesh.h"
#include "Objects.h"
#include "Sound.h"
#include "InventoryWorn.h"
#include "ItemData.h"
#include "GameStateLevel2.h"
#include "OST.h"
#include <ShlObj.h>

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

static errno_t error1;
static errno_t error2;
static errno_t error3;
static FILE *save1;
static FILE *save2;
static FILE *save3;

static char buffer1[6][16];
static char buffer2[6][16];
static char buffer3[6][16];

extern Prog pTemp;

static int button = 0;
static int flag = 0;
static int load = 0;


static int count = 0;
static int highlight = 0;
static int highlight1 = 0;
static int numSave = 0;

static float WinX;
static float WinY;
static float backX;
static float backY;
static float backX2;
static float backY2;

static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

static char backBuffer[16] = "";

static AEVec2 backPos = { 0, 0 };
static AEVec2 pos11 = { -485, 37.5 };
static AEVec2 pos12 = { -485, -60 };
static AEVec2 pos13 = { -485, -155 };
static AEVec2 pos21 = { 0, 37.5 };
static AEVec2 pos22 = { 0, -60 };
static AEVec2 pos23 = { 0, -155 };
static AEVec2 pos31 = { 485, 37.5 };
static AEVec2 pos32 = { 485, -60 };
static AEVec2 pos33 = { 485, -155 };

SpritePtr backSprite;
SpritePtr highlighterSprite;
SpritePtr backgroundSprite;
SpritePtr background1Sprite;
SpritePtr background2Sprite;
SpritePtr background3Sprite;

TransformPtr backTransform;
TransformPtr highlighterTransform;
TransformPtr backgroundTransform;

static ObjectPtr backGameObject;
static ObjectPtr highlighterGameObject;
static ObjectPtr backgroundGameObject;
static ObjectPtr background1GameObject;
static ObjectPtr background2GameObject;
static ObjectPtr background3GameObject;

static AEGfxVertexList *fontSheetVertexList;     
static AEGfxTexture *fontSheet;                 
static SpriteSourcePtr fontSheetSpriteSource;  

static AEGfxVertexList *highlighterVertexList;   
static AEGfxTexture *highlighterTexture;	       
static SpriteSourcePtr highlighterSpriteSource; 

static AEGfxVertexList *backgroundVertexList;    
static AEGfxTexture *backgroundTexture;			 
static SpriteSourcePtr backgroundSpriteSource;

static AEGfxVertexList *background1VertexList;
static AEGfxTexture *background1Texture;
static SpriteSourcePtr background1SpriteSource;
static AEGfxVertexList *background2VertexList;
static AEGfxTexture *background2Texture;
static SpriteSourcePtr background2SpriteSource;
static AEGfxVertexList *background3VertexList;
static AEGfxTexture *background3Texture;
static SpriteSourcePtr background3SpriteSource;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level2 game state.
void SaveSelectLoad()
{
	// Load the data for the font sheet
	fontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	fontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	fontSheetSpriteSource = SpriteSourceCreate(16, 6, fontSheet);

	// Load the data for the selection indecator
	highlighterVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	highlighterTexture = AEGfxTextureLoad("Assets/buttonSelect.png");
	highlighterSpriteSource = SpriteSourceCreate(1, 1, highlighterTexture);

	// Load the data for the background
	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");;
	backgroundTexture = AEGfxTextureLoad("Assets/SaveScreenNoSave.png");
	backgroundSpriteSource = SpriteSourceCreate(1, 1, backgroundTexture);

	// Load the data for the background
	background1VertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");;
	background1Texture = AEGfxTextureLoad("Assets/SaveScreenSave1.png");
	background1SpriteSource = SpriteSourceCreate(1, 1, background1Texture);

	// Load the data for the background
	background2VertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");;
	background2Texture = AEGfxTextureLoad("Assets/SaveScreenSave2.png");
	background2SpriteSource = SpriteSourceCreate(1, 1, background2Texture);

	// Load the data for the background
	background3VertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");;
	background3Texture = AEGfxTextureLoad("Assets/SaveScreenSave3.png");
	background3SpriteSource = SpriteSourceCreate(1, 1, background3Texture);
}

	// Initialize the memory associated with the Level2 game state.
void SaveSelectInit()
{
	load = 0;
	highlight = 0;
	highlight1 = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			buffer1[i][j] = 0;
			buffer2[i][j] = 0;
			buffer3[i][j] = 0;
		}
	}

	LPWSTR wpath = NULL;
	HRESULT hr;
	wchar_t buffer[MAX_PATH];
	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

	char folder[MAX_PATH];
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}

	error1 = fopen_s(&save1, folder, "r"); // Open file

	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));

	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error2 = fopen_s(&save2, folder, "r"); // Open file

	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));

	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error3 = fopen_s(&save3, folder, "r"); // Open file

	if (error1 == 0 && error2 == 0 && error3 == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			fgets(buffer1[i], 16, save1);
			fgets(buffer2[i], 16, save2);
			fgets(buffer3[i], 16, save3);
		}
		fclose(save1);
		fclose(save2);
		fclose(save3);
	}

	highlight = pTemp + 1;
	WinX = AEGfxGetWinMaxX() * 2;
	WinY = AEGfxGetWinMaxY() * 2;
	backX = -WinX / (float)2.5;
	backX2 = -WinX / (float)2.35;
	backY = -WinY / (float)2.7;
	backY2 = -WinY / (float)2.72;
	backPos.x = backX;
	backPos.y = backY;

	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);

	AEGfxSetBackgroundColor(1.0f, 1.0f, 1.0f);

	backGameObject = CreateObject("BackText", ObjTag);
	highlighterGameObject = CreateObject("Highlighter", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	sprintf_s(backBuffer, 16, "Back");

	backTransform = TransformCreate(backX2, backY2);
	highlighterTransform = TransformCreate(backX, backY);

	backgroundTransform = TransformCreate(0, 0);
	AEVec2 backgroundScale = { 0, 0 };
	backgroundScale.x = WinX;
	backgroundScale.y = WinY;
	TransformSetRotation(backgroundTransform, 0);
	TransformSetScale(backgroundTransform, &backgroundScale);

	backgroundSprite = SpriteCreate("Background sprite");
	SpriteSetMesh(backgroundSprite, backgroundVertexList);
	SpriteSetSpriteSource(backgroundSprite, backgroundSpriteSource);

	ObjectSetTransform(backgroundTransform, backgroundGameObject);
	ObjectSetSprite(backgroundSprite, backgroundGameObject);

	AEVec2 buttonselectScale = { 350, 300 };
	TransformSetRotation(highlighterTransform, 0);
	TransformSetScale(highlighterTransform, &buttonselectScale);

	highlighterSprite = SpriteCreate("Highlighter Sprite");
	SpriteSetMesh(highlighterSprite, highlighterVertexList);
	SpriteSetSpriteSource(highlighterSprite, highlighterSpriteSource);

	ObjectSetTransform(highlighterTransform, highlighterGameObject);
	ObjectSetSprite(highlighterSprite, highlighterGameObject);

	PrintText(backGameObject, backBuffer, backSprite, backTransform);

	background1Sprite = SpriteCreate("Background1 sprite");
	SpriteSetMesh(background1Sprite, background1VertexList);
	SpriteSetSpriteSource(background1Sprite, background1SpriteSource);
	background2Sprite = SpriteCreate("Background2 sprite");
	SpriteSetMesh(background2Sprite, background2VertexList);
	SpriteSetSpriteSource(background2Sprite, background2SpriteSource);
	background3Sprite = SpriteCreate("Background3 sprite");
	SpriteSetMesh(background3Sprite, background3VertexList);
	SpriteSetSpriteSource(background3Sprite, background3SpriteSource);

	background1GameObject = CreateObject("Background1", ObjTag);
	background2GameObject = CreateObject("Background1", ObjTag);
	background3GameObject = CreateObject("Background1", ObjTag);

	ObjectSetTransform(backgroundTransform, background1GameObject);
	ObjectSetSprite(background1Sprite, background1GameObject);
	ObjectSetTransform(backgroundTransform, background2GameObject);
	ObjectSetSprite(background2Sprite, background2GameObject);
	ObjectSetTransform(backgroundTransform, background3GameObject);
	ObjectSetSprite(background3Sprite, background3GameObject);
}

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SaveSelectUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	flag++;

	if (flag % 12 == 0)
	{
		button = 0;
	}

	DrawObject(backgroundGameObject);

	LPWSTR wpath = NULL;
	HRESULT hr;
	wchar_t buffer[MAX_PATH];
	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

	char folder[MAX_PATH];
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error1 = fopen_s(&save1, folder, "r"); // Open file

	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));

	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error2 = fopen_s(&save2, folder, "r"); // Open file

	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));

	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error3 = fopen_s(&save3, folder, "r"); // Open file

	if (error1 == 0 && error2 == 0 && error3 == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			fgets(buffer1[i], 16, save1);
			fgets(buffer2[i], 16, save2);
			fgets(buffer3[i], 16, save3);
		}

		fclose(save1);
		fclose(save2);
		fclose(save3);
	}


	if (buffer1[0][0] != 0)
	{
		DrawObject(background1GameObject);
		numSave++;
	}
	if (buffer2[0][0] != 0)
	{
		DrawObject(background2GameObject);
		numSave++;
	}
	if (buffer3[0][0] != 0)
	{
		DrawObject(background3GameObject);
		numSave++;
	}

	DrawObject(highlighterGameObject);
	DrawObject(backGameObject);

	if ((/*AEInputCheckTriggered(VK_LEFT) || */GetDpadButton(3) || GetJoystickX(SIDE_L) <= -0.25f) && button == 0)
	{
		highlight--;
		highlight1 = 0;
		button = 1;
		SoundPlay(&optionSound, false);
		flag = 0;
	}
	else if ((/*AEInputCheckTriggered(VK_RIGHT) || */GetDpadButton(1) || GetJoystickX(SIDE_L) >= 0.25f) && button == 0)
	{
		highlight++;
		highlight1 = 0;
		button = 1;
		SoundPlay(&optionSound, false);
		flag = 0;
	}


	if (highlight == 0)
	{
		TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &backPos);
		count = 0;

		if (/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0))
		{
			playSwingSound();
			GameStateManagerSetNextState(GsMenu);
		}
	}
	else
	{
		if ((/*AEInputCheckTriggered(VK_DOWN) || */GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f) && button == 0)
		{
			highlight1++;
			SoundPlay(&optionSound, false);
			button = 1;
			flag = 0;
		}
		if ((/*AEInputCheckTriggered(VK_UP) || */GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f) && button == 0)
		{
			highlight1--;
			SoundPlay(&optionSound, false);
			button = 1;
			flag = 0;
		}

		if (highlight == 1)
		{
			if (buffer1[0][0] != 0)
			{
				if (highlight1 == 0)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos11);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						playSwingSound();
						load = 1;
						PlayerSetGold(0);
						PlayerAddGold(atoi(buffer1[1]));
						if (buffer1[0][0] == '2')
						{
							pTemp = Start;
							SetSelect();
						}
						else if (buffer1[0][0] == '3')
						{
							pTemp = Secnd;
							SetSelect();
						}

						int weapon = atoi(buffer1[2]);
						int head = atoi(buffer1[3]);
						int body = atoi(buffer1[4]);
						int legs = atoi(buffer1[5]);

						HumanPtr human = HumanGetHuman(player, NULL);

						HumanSetWeapon(human, weapon);
						HumanSetArmors(human, head, body, legs);
						GameStateManagerSetNextState(GsTown);
					}
				}
				else if (highlight1 == 1)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos12);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						int gold = PlayerGetGold();
						error1 = fopen_s(&save1, folder, "wt"); // Open file
						if (pTemp == Secnd)
							fputc('2', save1);
						else if (pTemp == Third)
							fputc('3', save1);
						else
							fputc('1', save1);

						fputc('\n', save1);

						char goldC[16] = { 0 };

						sprintf_s(goldC, 16, "%d", gold);

						fputs(goldC, save1);
						fputc('\n', save1);

						HumanPtr human = HumanGetHuman(player, NULL);

						char bufferW[16];
						char bufferH[16];
						char bufferB[16];
						char bufferL[16];
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

						fputs(bufferW, save1);
						fputc('\n', save1);
						fputs(bufferH, save1);
						fputc('\n', save1);
						fputs(bufferB, save1);
						fputc('\n', save1);
						fputs(bufferL, save1);
						fputc('\n', save1);
						
						fclose(save1);
					}
				}
				else if (highlight1 == 2)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos13);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						//load = 1;
						error1 = fopen_s(&save1, folder, "wt"); // Open file
						fputc(0, save1);
						fclose(save1);
						highlight = 0;
					}
				}
			}
			else
			{
				TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos12);
				if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
				{
					hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
					wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

					for (int i = 0; i < MAX_PATH; i++)
					{
						if (buffer[i] == '0')
							break;
						else
							folder[i] = (char)buffer[i];
					}
					playSwingSound();
					int gold = PlayerGetGold();
					error1 = fopen_s(&save1, folder, "wt"); // Open file
					if (pTemp == Secnd)
						fputc('2', save1);
					else if (pTemp == Third)
						fputc('3', save1);
					else
						fputc('1', save1);

					fputc('\n', save1);

					char goldC[16] = { 0 };

					sprintf_s(goldC, 16, "%d", gold);

					fputs(goldC, save1);
					fputc('\n', save1);

					HumanPtr human = HumanGetHuman(player, NULL);

					char bufferW[16];
					char bufferH[16];
					char bufferB[16];
					char bufferL[16];
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

					fputs(bufferW, save1);
					fputc('\n', save1);
					fputs(bufferH, save1);
					fputc('\n', save1);
					fputs(bufferB, save1);
					fputc('\n', save1);
					fputs(bufferL, save1);
					fputc('\n', save1);

					fclose(save1);
				}
			}

			count = 1;
		}
		if (highlight == 2)
		{
			TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos21);

			if (buffer2[0][0] != 0)
			{
				if (highlight1 == 0)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos21);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						playSwingSound();
						int gold = atoi(buffer2[1]);
						PlayerSetGold(0);
						PlayerAddGold(gold);
						load = 1;
						
						if (buffer2[0][0] == '2')
						{
							pTemp = Start;
							SetSelect();
						}
						else if (buffer2[0][0] == '3')
						{
							pTemp = Secnd;
							SetSelect();
						}

						int weapon = atoi(buffer2[2]);
						int head = atoi(buffer2[3]);
						int body = atoi(buffer2[4]);
						int legs = atoi(buffer2[5]);

						HumanPtr human = HumanGetHuman(player, NULL);

						HumanSetWeapon(human, weapon);
						HumanSetArmors(human, head, body, legs);
						GameStateManagerSetNextState(GsTown);
					}
				}
				else if (highlight1 == 1)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos22);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						int gold = PlayerGetGold();
						error1 = fopen_s(&save2, folder, "wt"); // Open file
						if (pTemp == Secnd)
							fputc('2', save2);
						else if (pTemp == Third)
							fputc('3', save2);
						else
							fputc('1', save2);

						fputc('\n', save2);

						char goldC[16] = { 0 };

						sprintf_s(goldC, 16, "%d", gold);

						fputs(goldC, save2);
						fputc('\n', save2);

						HumanPtr human = HumanGetHuman(player, NULL);

						char bufferW[16];
						char bufferH[16];
						char bufferB[16];
						char bufferL[16];
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

						fputs(bufferW, save2);
						fputc('\n', save2);
						fputs(bufferH, save2);
						fputc('\n', save2);
						fputs(bufferB, save2);
						fputc('\n', save2);
						fputs(bufferL, save2);
						fputc('\n', save2);

						fclose(save2);
					}
				}
				else if (highlight1 == 2)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos23);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						//load = 1;
						error2 = fopen_s(&save2, folder, "wt"); // Open file
						fputc(0, save2);
						fclose(save2);
						highlight = 0;
					}
				}
			}
			else
			{
				TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos22);
				if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
				{
					hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
					wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save2.txt"));

					for (int i = 0; i < MAX_PATH; i++)
					{
						if (buffer[i] == '0')
							break;
						else
							folder[i] = (char)buffer[i];
					}
					playSwingSound();
					int gold = PlayerGetGold();
					error1 = fopen_s(&save2, folder, "wt"); // Open file
					if (pTemp == Secnd)
						fputc('2', save2);
					else if (pTemp == Third)
						fputc('3', save2);
					else
						fputc('1', save2);

					fputc('\n', save2);

					char goldC[16] = { 0 };

					sprintf_s(goldC, 16, "%d", gold);

					fputs(goldC, save2);
					fputc('\n', save2);

					HumanPtr human = HumanGetHuman(player, NULL);

					char bufferW[16];
					char bufferH[16];
					char bufferB[16];
					char bufferL[16];
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

					fputs(bufferW, save2);
					fputc('\n', save2);
					fputs(bufferH, save2);
					fputc('\n', save2);
					fputs(bufferB, save2);
					fputc('\n', save2);
					fputs(bufferL, save2);
					fputc('\n', save2);

					fclose(save2);
				}
			}

			count = 2;
		}
		if (highlight == 3)
		{
			TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos31);

			if (buffer3[0][0] != 0)
			{
				if (highlight1 == 0)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos31);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						playSwingSound();
						load = 1;
						PlayerSetGold(0);
						PlayerAddGold(atoi(buffer3[1]));
						if (buffer3[0][0] == '2')
						{
							pTemp = Start;
							SetSelect();
						}
						else if (buffer3[0][0] == '3')
						{
							pTemp = Secnd;
							SetSelect();
						}

						int weapon = atoi(buffer3[2]);
						int head = atoi(buffer3[3]);
						int body = atoi(buffer3[4]);
						int legs = atoi(buffer3[5]);

						HumanPtr human = HumanGetHuman(player, NULL);

						HumanSetWeapon(human, weapon);
						HumanSetArmors(human, head, body, legs);

						GameStateManagerSetNextState(GsTown);
					}
				}
				else if (highlight1 == 1)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos32);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						int gold = PlayerGetGold();
						error1 = fopen_s(&save3, folder, "wt"); // Open file
						if (pTemp == Secnd)
							fputc('2', save3);
						else if (pTemp == Third)
							fputc('3', save3);
						else
							fputc('1', save3);

						fputc('\n', save3);

						char goldC[16] = { 0 };

						sprintf_s(goldC, 16, "%d", gold);

						fputs(goldC, save3);
						fputc('\n', save3);

						HumanPtr human = HumanGetHuman(player, NULL);

						char bufferW[16];
						char bufferH[16];
						char bufferB[16];
						char bufferL[16];
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
						_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

						fputs(bufferW, save3);
						fputc('\n', save3);
						fputs(bufferH, save3);
						fputc('\n', save3);
						fputs(bufferB, save3);
						fputc('\n', save3);
						fputs(bufferL, save3);
						fputc('\n', save3);

						fclose(save3);
					}
				}
				else if (highlight1 == 2)
				{
					TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos33);
					if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
					{
						hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
						wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));

						for (int i = 0; i < MAX_PATH; i++)
						{
							if (buffer[i] == '0')
								break;
							else
								folder[i] = (char)buffer[i];
						}
						playSwingSound();
						//load = 1;
						error3 = fopen_s(&save3, folder, "wt"); // Open file
						fputc(0, save3);
						fclose(save3);
						highlight = 0;
					}
				}
			}
			else
			{
				TransformSetTranslation(ObjectGetTransform(highlighterGameObject), &pos32);
				if ((/*AEInputCheckTriggered(VK_RETURN) || */GetButtonDown(0, 0)) && load == 0)
				{
					hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
					wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save3.txt"));

					for (int i = 0; i < MAX_PATH; i++)
					{
						if (buffer[i] == '0')
							break;
						else
							folder[i] = (char)buffer[i];
					}
					playSwingSound();
					int gold = PlayerGetGold();
					error1 = fopen_s(&save3, folder, "wt"); // Open file
					if (pTemp == Secnd)
						fputc('2', save3);
					else if (pTemp == Third)
						fputc('3', save3);
					else
						fputc('1', save3);

					fputc('\n', save3);

					char goldC[16] = { 0 };

					sprintf_s(goldC, 16, "%d", gold);

					fputs(goldC, save3);
					fputc('\n', save3);

					HumanPtr human = HumanGetHuman(player, NULL);

					char bufferW[16];
					char bufferH[16];
					char bufferB[16];
					char bufferL[16];
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotWeapon), bufferW, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotHead), bufferH, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotBody), bufferB, 16, 10);
					_itoa_s(WornInventoryGetId(HumanGetInventoryWorn(human), slotLegs), bufferL, 16, 10);

					fputs(bufferW, save3);
					fputc('\n', save3);
					fputs(bufferH, save3);
					fputc('\n', save3);
					fputs(bufferB, save3);
					fputc('\n', save3);
					fputs(bufferL, save3);
					fputc('\n', save3);

					fclose(save3);
				}
			}

			count = 3;
		}
	}
	
	if (highlight > 3)
		highlight = 0;
	else if (highlight < 0)
		highlight = 3;

	if (highlight1 > 2)
		highlight1 = 0;
	else if (highlight1 < 0)
		highlight1 = 2;
}

// Shutdown any memory associated with the Level2 game state.
void SaveSelectShutdown()
{
	FreeObject(&backGameObject);
	FreeObject(&highlighterGameObject);
	//FreeObject(&backgroundGameObject);
	//FreeObject(&background1GameObject);
	//FreeObject(&background2GameObject);
	//FreeObject(&background3GameObject);
}

// Unload the resources associated with the Level2 game state.
void SaveSelectUnload()
{
	SpriteSourceFree(&fontSheetSpriteSource);
	AEGfxTextureUnload(fontSheet);
	AEGfxMeshFree(fontSheetVertexList);

	SpriteSourceFree(&highlighterSpriteSource);
	AEGfxTextureUnload(highlighterTexture);
	AEGfxMeshFree(highlighterVertexList);
	SpriteSourceFree(&backgroundSpriteSource);
	AEGfxTextureUnload(backgroundTexture);
	AEGfxMeshFree(backgroundVertexList);

	SpriteSourceFree(&background1SpriteSource);
	AEGfxTextureUnload(background1Texture);
	AEGfxMeshFree(background1VertexList);
	SpriteSourceFree(&background2SpriteSource);
	AEGfxTextureUnload(background2Texture);
	AEGfxMeshFree(background2VertexList);
	SpriteSourceFree(&background3SpriteSource);
	AEGfxTextureUnload(background3Texture);
	AEGfxMeshFree(background3VertexList);
}

void SaveSelectContinue(void)
{
	LPWSTR wpath = NULL;
	HRESULT hr;
	wchar_t buffer[MAX_PATH];
	hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
	wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("save1.txt"));

	char folder[MAX_PATH];
	for (int i = 0; i < MAX_PATH; i++)
	{
		if (buffer[i] == '0')
			break;
		else
			folder[i] = (char)buffer[i];
	}
	error1 = fopen_s(&save1, folder, "r"); // Open file

	if (error1 == 0)
	{
		for (int i = 0; i < 6; i++)
			fgets(buffer1[i], 16, save1);
		fclose(save1);
	}

	if (buffer1[0][0] < '1' || buffer1[0][0] > '3')
		return;

	int gold = atoi(buffer1[1]);
	PlayerSetGold(0);
	PlayerAddGold(gold);
	load = 1;

	if (buffer1[0][0] == '2')
	{
		pTemp = Start;
		SetSelect();
	}
	else if (buffer1[0][0] == '3')
	{
		pTemp = Secnd;
		SetSelect();
	}

	int weapon = atoi(buffer1[2]);
	int head = atoi(buffer1[3]);
	int body = atoi(buffer1[4]);
	int legs = atoi(buffer1[5]);

	HumanPtr human = HumanGetHuman(player, NULL);

	HumanSetWeapon(human, weapon);
	HumanSetArmors(human, head, body, legs);
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

	pSpriteSrc = SpriteCreate("Highlighter Sprite");
	SpriteSetMesh(pSpriteSrc, fontSheetVertexList);
	SpriteSetSpriteSource(pSpriteSrc, fontSheetSpriteSource);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}