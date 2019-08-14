//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel2.c
// Author(s):	Anthony Miller
// Project:		Project 1
// Course:		CS230SU19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "GameStateManager.h"
#include "GameStateLevel2.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Stream.h"
#include "Trace.h"
#include "Physics.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Sprite.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

static const float spaceshipSpeed = 500.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static AEGfxVertexList * pMeshSpaceship;
static GameObjectPtr spaceShip;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void GameStateLevel2MovementController(GameObjectPtr gameObject);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level2 game state.
void GameStateLevel2Load()
{
	// Create a "unit"-sized triangular mesh.
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
		0.5f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	pMeshSpaceship = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshSpaceship, "Failed to create spaceship mesh!");

}

// Initialize the memory associated with the Level2 game state.
void GameStateLevel2Init()
{
	spaceShip = GameObjectFactoryBuild("SpaceshipHoming");

	if (spaceShip)
	{
		SpritePtr sprite = spaceShip->GetSprite();
		sprite->SetMesh(pMeshSpaceship);
	}

	AEGfxSetBackgroundColor(0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

// Update the Level2 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateLevel2Update(float dt)
{
	if (AEInputCheckCurr('Z'))
	{
		SpritePtr holdSprite = spaceShip->GetSprite();
		holdSprite->SetAlpha(0.5f);
	}
	else if (AEInputCheckCurr('X'))
	{
		SpritePtr holdSprite = spaceShip->GetSprite();
		holdSprite->SetAlpha(1.0f);
	}

	GameStateLevel2MovementController(spaceShip);
	spaceShip->Update(dt);
	spaceShip->Draw();


	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsLevel1);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	/*else if (AEInputCheckTriggered('3'))
	{
		GameStateManagerSetNextState(GsAsteroids);
	}
	else if (AEInputCheckTriggered('4'))
	{
		GameStateManagerSetNextState(GsOmega);
	}*/
}

// Shutdown any memory associated with the Level2 game state.
void GameStateLevel2Shutdown()
{
	delete spaceShip;
	spaceShip = NULL;
}

// Unload the resources associated with the Level2 game state.
void GameStateLevel2Unload()
{
	AEGfxMeshFree(pMeshSpaceship);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void GameStateLevel2MovementController(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		PhysicsPtr physics = gameObject->GetPhysics();
		TransformPtr transform = gameObject->GetTransform();

		if (physics && transform)
		{
			//floats to hold mouse data
			s32 screenX;
			s32 screenY;
			float worldX;
			float worldY;

			//vectors to hold information
			Vector2D translation = *transform->GetTranslation();
			Vector2D holder;

			//get mouse position and convert it to world position
			AEInputGetCursorPosition(&screenX, &screenY);
			AEGfxConvertScreenCoordinatesToWorld((float)screenX, (float)screenY, &worldX, &worldY);
			//store the mouse position in a vector
			holder.x = worldX;
			holder.y = worldY;

			//calculate the direction between the ship and the mouse and normalize it
			Vector2DSub(&holder, &holder, &translation);
			Vector2DNormalize(&holder, &holder);

			//set the new rotation of the ship
			transform->SetRotation(Vector2DToAngleRad(&holder));

			//update the velocity of the ship
			Vector2DScale(&holder, &holder, spaceshipSpeed);
			physics->SetVelocity(&holder);
		}
	}
}
