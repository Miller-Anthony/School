//------------------------------------------------------------------------------
//
// File Name:	Settings.c
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
#include "Objects.h"
#include "Sound.h"
#include "Settings.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Input.h"
#include "OST.h"
#include <Shlobj.h>

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
static int button = 0;
static int time = 0;
static int time2 = 0;
static int frame = 168;
static int menuFlag = 0;
static int showController = 0;

// Font Sheet Buffers
static char continueBuffer[256] = "";
static char newgameBuffer[256] = "";
static char loadBuffer[256] = "";
static char optionsBuffer[256] = "";
static char creditsBuffer[256] = "";
static char quitBuffer[256] = "";

static FMOD_SOUND* optionSound;
static FMOD_SOUND* swordSound;

// Font Sheet Sprites
SpritePtr continueSprite;
SpritePtr newgameSprite;
SpritePtr loadSprite;
SpritePtr optionsSprite;
SpritePtr creditsSprite;
SpritePtr quitSprite;

SpritePtr titleSprite;

SpritePtr buttonselectSpritePtr;
SpritePtr backgroundSprite;

// Font Sheet Transforms
TransformPtr continueTransform;
TransformPtr newgameTransform;
TransformPtr loadTransform;
TransformPtr optionsTransform;
TransformPtr creditsTransform;
TransformPtr quitTransform;

TransformPtr titleTransform;

TransformPtr buttonselectTransform;
TransformPtr backgroundTransform;

static AEGfxVertexList *pFontSheetVertexList; // Font Sheet Vertex List
static AEGfxTexture *pFontSheet; // Font Sheet Texture
static SpriteSourcePtr pFontSheetSprite; // Font Sheet Sprite

static AEGfxVertexList *buttonselectVertexList;
static AEGfxTexture *buttonselect;
static SpriteSourcePtr buttonselectSprite;

static AEGfxVertexList *pTitleVertexList;
static AEGfxTexture *pTitleTexture;
static SpriteSourcePtr pTitleSpriteSource;

static AEGfxVertexList *backgroundVertexList;
static AEGfxTexture *backgroundTexture;
static SpriteSourcePtr backgroundSpriteSource;

static AEGfxVertexList *psubTitleVertexList;
static AEGfxTexture *psubTitleTexture;
static SpriteSourcePtr psubTitleSpriteSource;
static TransformPtr subtitleTransform;
static SpritePtr subtitleSprite;

// Font Sheet Game Objects
static ObjectPtr continueGameObject;
static ObjectPtr newgameGameObject;
static ObjectPtr loadGameObject;
static ObjectPtr optionsGameObject;
static ObjectPtr creditsGameObject;
static ObjectPtr quitGameObject;

static ObjectPtr titleGameObject;

static ObjectPtr buttonselectGameObject;
static ObjectPtr backgroundGameObject;

static int windowed;
static int resolution;
static int music;
static FILE *settings; // File to read lives from
static int updated;
static errno_t error;

static FMOD_SYSTEM *FmodSystem;  //for initializing and shutting down FMOD
static FMOD_SOUNDGROUP *soundGroup;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void PrintText(ObjectPtr GameObject, char *charBuffer, SpritePtr pSpriteSrc, TransformPtr pTransform);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void SettingsLoad()
{
	pFontSheetVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 16, 1.0f / 6, "Mesh16x6");
	pFontSheet = AEGfxTextureLoad("Assets/Text_White.png");
	pFontSheetSprite = SpriteSourceCreate(16, 6, pFontSheet);

	buttonselectVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
	buttonselect = AEGfxTextureLoad("Assets/buttonSelect.png");
	buttonselectSprite = SpriteSourceCreate(1, 1, buttonselect);

	backgroundVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 13, 1.0f / 13, "Mesh 13x13");;
	backgroundTexture = AEGfxTextureLoad("Assets/menuBg1.png");
	backgroundSpriteSource = SpriteSourceCreate(13, 13, backgroundTexture);

	pTitleVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "MeshTitle");
	pTitleTexture = AEGfxTextureLoad("Assets/Title.png");
	pTitleSpriteSource = SpriteSourceCreate(1, 1, pTitleTexture);

	psubTitleVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f / 2, 1.0f / 2, "MeshSubtitle");
	psubTitleTexture = AEGfxTextureLoad("Assets/subtitle.png");
	psubTitleSpriteSource = SpriteSourceCreate(2, 2, psubTitleTexture);

	FmodSystem = SoundGetSystem();
	FMOD_System_GetMasterSoundGroup(FmodSystem, &soundGroup);
}

// Initialize the memory associated with the Level1 game state.
void SettingsInit()
{
	float volume;
	showController = 0;
	FMOD_SoundGroup_GetVolume(soundGroup, &volume);

	if (volume)
		music = 1;
	else
		music = 0;

	updated = 0;
	button = 0;
	SoundInit("./Assets/Sound/sfxType.wav", FMOD_LOOP_OFF, &optionSound);
	SoundInit("./Assets/Sound/swordSfx.wav", FMOD_LOOP_OFF, &swordSound);
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	continueGameObject = CreateObject("ContinueText", ObjTag);
	newgameGameObject = CreateObject("NewGameText", ObjTag);
	loadGameObject = CreateObject("LoadText", ObjTag);
	optionsGameObject = CreateObject("OptionsText", ObjTag);
	creditsGameObject = CreateObject("CreditsText", ObjTag);
	quitGameObject = CreateObject("QuitText", ObjTag);

	titleGameObject = CreateObject("TitleLogo", ObjTag);

	buttonselectGameObject = CreateObject("buttonSelect", ObjTag);
	backgroundGameObject = CreateObject("Background", ObjTag);

	
	sprintf_s(newgameBuffer, 256, "Controls");
	sprintf_s(loadBuffer, 256, "Frames      :      %d", (int)(1 / AEFrameRateControllerGetFrameTime()));

	if(music)
		sprintf_s(optionsBuffer, 256, "Music       :      ON");
	else
		sprintf_s(optionsBuffer, 256, "Music       :      OFF");

	sprintf_s(creditsBuffer, 16, "Back");
	sprintf_s(quitBuffer, 16, "Quit");

	continueTransform = TransformCreate(-800, 0);
	newgameTransform = TransformCreate(-800, -50);
	loadTransform = TransformCreate(-800, -100);
	optionsTransform = TransformCreate(-800, -150);
	creditsTransform = TransformCreate(-800, -200);
	quitTransform = TransformCreate(-800, -250);

	titleTransform = TransformCreate(-500, 200);
	AEVec2 titleScale = { 688, 341 };
	TransformSetRotation(titleTransform, 0);
	TransformSetScale(titleTransform, &titleScale);
	titleSprite = SpriteCreate("Title Sprite");
	SpriteSetMesh(titleSprite, pTitleVertexList);
	SpriteSetSpriteSource(titleSprite, pTitleSpriteSource);
	ObjectSetTransform(titleTransform, titleGameObject);
	ObjectSetSprite(titleSprite, titleGameObject);

	backgroundTransform = TransformCreate(0, 0);
	AEVec2 backgroundScale;
	backgroundScale.x = -1920;
	backgroundScale.y = 1080;
	TransformSetRotation(backgroundTransform, 0);
	TransformSetScale(backgroundTransform, &backgroundScale);

	backgroundSprite = SpriteCreate("Background sprite");
	SpriteSetMesh(backgroundSprite, backgroundVertexList);
	SpriteSetSpriteSource(backgroundSprite, backgroundSpriteSource);

	ObjectSetTransform(backgroundTransform, backgroundGameObject);
	ObjectSetSprite(backgroundSprite, backgroundGameObject);

	buttonselectTransform = TransformCreate(85, -2.5);

	AEVec2 buttonselectScale;
	TransformSetRotation(buttonselectTransform, 0);
	buttonselectScale.x = 312.5;
	buttonselectScale.y = 250;
	TransformSetScale(buttonselectTransform, &buttonselectScale);

	buttonselectSpritePtr = SpriteCreate("MenuText Sprite");
	SpriteSetMesh(buttonselectSpritePtr, buttonselectVertexList);
	SpriteSetSpriteSource(buttonselectSpritePtr, buttonselectSprite);

	ObjectSetTransform(buttonselectTransform, buttonselectGameObject);
	ObjectSetSprite(buttonselectSpritePtr, buttonselectGameObject);

	PrintText(continueGameObject, continueBuffer, continueSprite, continueTransform);
	PrintText(newgameGameObject, newgameBuffer, newgameSprite, newgameTransform);
	PrintText(loadGameObject, loadBuffer, loadSprite, loadTransform);
	PrintText(optionsGameObject, optionsBuffer, optionsSprite, optionsTransform);
	PrintText(creditsGameObject, creditsBuffer, creditsSprite, creditsTransform);
	PrintText(quitGameObject, quitBuffer, quitSprite, quitTransform);

	subtitleTransform = TransformCreate(-475, 125);
	AEVec2 subtitleScale = { 1020, 576 };
	TransformSetRotation(subtitleTransform, 0);
	TransformSetScale(subtitleTransform, &subtitleScale);
	subtitleSprite = SpriteCreate("Subtitle Sprite");
	SpriteSetMesh(subtitleSprite, psubTitleVertexList);
	SpriteSetSpriteSource(subtitleSprite, psubTitleSpriteSource);
	SpriteSetFrame(subtitleSprite, 3);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SettingsUpdate(float dt)
{
	if (updated == 0)
	{
		HWND window = AESysGetWindowHandle();
		LPWSTR wpath = NULL;
		HRESULT hr;
		wchar_t buffer[MAX_PATH];
		hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
		wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("Settings.txt"));

		char folder[MAX_PATH];
		for (int i = 0; i < MAX_PATH; i++)
		{
			if (buffer[i] == '0')
				break;
			else
				folder[i] = (char)buffer[i];
		}
		error = fopen_s(&settings, folder, "r"); // Open file

		if (error == 0)
		{
			windowed = fgetc(settings);	  // If opened, read windowed / fullscreen 
			resolution = fgetc(settings); // If opened, read resolution
		}

		fclose(settings);

		if (windowed == 'f')
		{
			SetWindowLongA(window, GWL_STYLE, WS_POPUP);
			SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW); // Set window to 0,0 and 1080p, CHANGE WITH FOPEN AND SETTINGS CALL LATER
			sprintf_s(continueBuffer, 256, "Screen      :      Fullscreen");
			updated = 1;
		}
		else if (resolution == '0')
		{
			SetWindowLongA(window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
			sprintf_s(continueBuffer, 256, "Screen      :      Windowed");
			updated = 1;
		}
		else if (resolution == '1')
		{
			SetWindowLongA(window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(window, HWND_TOP, 0, 0, 1280, 720, SWP_SHOWWINDOW);
			sprintf_s(continueBuffer, 256, "Screen      :      Windowed");
			updated = 1;
		}
		else
		{
			SetWindowLongA(window, GWL_STYLE, WS_OVERLAPPEDWINDOW);

			SetWindowPos(window, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
			sprintf_s(continueBuffer, 256, "Screen      :      Windowed");
			updated = 1;
		}
	}

	//SoundModuleUpdate();
	UNREFERENCED_PARAMETER(dt);
	SpriteSetFrame(ObjectGetSprite(backgroundGameObject), frame);
	DrawObject(backgroundGameObject);
	DrawObject(titleGameObject);
	SpriteDraw(subtitleSprite, subtitleTransform);

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

	DrawObject(continueGameObject);
	DrawObject(newgameGameObject);
	DrawObject(loadGameObject);
	DrawObject(optionsGameObject);
	DrawObject(creditsGameObject);
	DrawObject(quitGameObject);
	DrawObject(buttonselectGameObject);

	if (AEInputCheckTriggered(VK_DOWN) || GetDpadButton(2) || GetJoystickY(SIDE_L) <= -0.25f)
	{
		if (menuFlag == 0)
		{
			SoundPlay(&optionSound, false);
			time2 = 0;
			menuFlag = 1;
			button++;
		}
	}
	else if (AEInputCheckTriggered(VK_UP) || GetDpadButton(0) || GetJoystickY(SIDE_L) >= 0.25f)
	{
		if (menuFlag == 0)
		{
			SoundPlay(&optionSound, false);
			time2 = 0;
			menuFlag = 1;
			button--;
		}
	}

	if (button < 0)
		button = 5;
	if (button > 5)
		button = 0;

	if (AEInputCheckTriggered(VK_RETURN) || GetButtonDown(0, 0))
	{
		playSwingSound();

		if (button == 0)
		{
			LPWSTR wpath = NULL;
			HRESULT hr;
			wchar_t buffer[MAX_PATH];
			hr = SHGetKnownFolderPath(&FOLDERID_AppDataDocuments, KF_FLAG_CREATE, NULL, &wpath);
			wsprintf(buffer, TEXT("%s\\%s"), wpath, TEXT("Settings.txt"));

			char folder[MAX_PATH];
			for (int i = 0; i < MAX_PATH; i++)
			{
				if (buffer[i] == '0')
					break;
				else
					folder[i] = (char)buffer[i];
			}
			error = fopen_s(&settings, folder, "wt"); // Open file
			updated = 0;
			if (windowed == 'f')
			{
				fgetc(settings);
				fgetc(settings);
				fputc('w', settings);
				fputc('0', settings);
			}
			else
			{
				fgetc(settings);
				fgetc(settings);
				fputc('f', settings);
				fputc('0', settings);
			}

			fclose(settings);
		}
		if (button == 1)
		{
			showController = 1;
			//GameStateManagerSetNextState(GsTown);
		}
		if (button == 2)
			button; // Do nothing
			//GameStateManagerSetNextState(GsTown);
		if (button == 3)
		{
			if (music)
			{
				sprintf_s(optionsBuffer, 256, "Music       :      OFF");
				FMOD_SoundGroup_SetVolume(soundGroup, 0.0f);
				music = 0;
			}
			else
			{
				sprintf_s(optionsBuffer, 256, "Music       :      ON");
				FMOD_SoundGroup_SetVolume(soundGroup, 1.0f);
				music = 1;
			}
		}
		if (button == 4)
			GameStateManagerSetNextState(GsMenu);
		if (button == 5)
			GameStateManagerSetNextState(GsQuit);
	}

	if (showController)
	{
		static AEGfxVertexList *background;
		static SpritePtr bgSprite;
		static TransformPtr transformBG;

		bgSprite = SpriteCreate("Background Pause");
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
			0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f);
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
			-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
			0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
		background = AEGfxMeshEnd();

		SpriteSetMesh(bgSprite, background);
		SpriteSetAlpha(bgSprite, 0.85f);

		static AEGfxVertexList *buttonVertexList;
		static AEGfxTexture *buttonLol;
		static SpriteSourcePtr buttonSpritePtr;
		static TransformPtr buttonTransform;
		static SpritePtr buttonSprite;

		buttonVertexList = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh 1x1");
		buttonLol = AEGfxTextureLoad("Assets/Controls.png");
		buttonSpritePtr = SpriteSourceCreate(1, 1, buttonLol);

		transformBG = TransformCreate(0, 0);
		AEVec2 bgTranslation = { 0, 0 };
		AEGfxGetCamPosition(&bgTranslation.x, &bgTranslation.y);
		TransformSetTranslation(transformBG, &bgTranslation);
		AEVec2 scaleBg = { 1920, 1080 };
		TransformSetScale(transformBG, &scaleBg);
		SpriteDraw(bgSprite, transformBG);

		buttonSprite = SpriteCreate("Pause Select");
		buttonTransform = TransformCreate(0, 0);
		AEVec2 selectScale = { 1024, 1024 };
		TransformSetScale(buttonTransform, &selectScale);
		SpriteSetMesh(buttonSprite, buttonVertexList);
		SpriteSetSpriteSource(buttonSprite, buttonSpritePtr);
		SpriteDraw(buttonSprite, buttonTransform);

		if (GetButtonDown(0, Button_B))
			showController = 0;
	}

	AEVec2 choice0 = { -740, -2.5 };
	AEVec2 choice1 = { -740, -52.5 };
	AEVec2 choice2 = { -740, -102.5 };
	AEVec2 choice3 = { -740, -152.5 };
	AEVec2 choice4 = { -740, -202.5 };
	AEVec2 choice5 = { -740, -252.5 };

	if (button == 0)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice0);
	if (button == 1)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice1);
	if (button == 2)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice2);
	if (button == 3)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice3);
	if (button == 4)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice4);
	if (button == 5)
		TransformSetTranslation(ObjectGetTransform(buttonselectGameObject), &choice5);

	//PrintBatteryInfo();

}

// Shutdown any memory associated with the Level1 game state.
void SettingsShutdown()
{
	FreeObject(&continueGameObject);
	FreeObject(&newgameGameObject);
	FreeObject(&loadGameObject);
	FreeObject(&optionsGameObject);
	FreeObject(&creditsGameObject);
	FreeObject(&quitGameObject);
	FreeObject(&titleGameObject);
	FreeObject(&buttonselectGameObject);
	FreeObject(&backgroundGameObject);
	fclose(settings);
}

// Unload the resources associated with the Level1 game state.
void SettingsUnload()
{
	SpriteSourceFree(&pFontSheetSprite);
	AEGfxMeshFree(pFontSheetVertexList);
	AEGfxTextureUnload(pFontSheet);

	SpriteSourceFree(&buttonselectSprite);
	AEGfxMeshFree(buttonselectVertexList);
	AEGfxTextureUnload(buttonselect);
	SpriteSourceFree(&pTitleSpriteSource);
	AEGfxMeshFree(pTitleVertexList);
	AEGfxTextureUnload(pTitleTexture);
	SpriteSourceFree(&backgroundSpriteSource);
	AEGfxMeshFree(backgroundVertexList);
	AEGfxTextureUnload(backgroundTexture);
	SpriteSourceFree(&psubTitleSpriteSource);
	AEGfxMeshFree(psubTitleVertexList);
	AEGfxTextureUnload(psubTitleTexture);
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
	SpriteSetMesh(pSpriteSrc, pFontSheetVertexList);
	SpriteSetSpriteSource(pSpriteSrc, pFontSheetSprite);

	SpriteSetText(pSpriteSrc, charBuffer);

	ObjectSetTransform(pTransform, GameObject);
	ObjectSetSprite(pSpriteSrc, GameObject);
}
