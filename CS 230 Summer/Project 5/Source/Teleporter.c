//------------------------------------------------------------------------------
//
// File Name:	Teleporter.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "Vector2D.h"
#include "Teleporter.h"
#include "GameObject.h"
#include "Transform.h"

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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// When a game object goes off-screen, teleport it to the other side.
// Params:
//	 gameObject = Pointer to the game object to be checked.
void TeleporterUpdateObject(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		// Get the position and speed of the game object
		const Vector2D *holdPos = TransformGetTranslation(GameObjectGetTransform(gameObject));
		const Vector2D *holdVel = PhysicsGetVelocity(GameObjectGetPhysics(gameObject));

		//if moving in the direction of the right wall
		if (holdVel->x > 0)
		{
			if (holdPos->x > AEGfxGetWinMaxX())
			{
				Vector2D newX;
				newX.x = holdPos->x * -1;
				newX.y = holdPos->y;
				TransformSetTranslation(GameObjectGetTransform(gameObject), &newX);
			}
		}

		//if moving in the direction of the left wall
		if (holdVel->x < 0)
		{
			if (holdPos->x < AEGfxGetWinMinX())
			{
				Vector2D newX;
				newX.x = holdPos->x * -1;
				newX.y = holdPos->y;
				TransformSetTranslation(GameObjectGetTransform(gameObject), &newX);
			}
		}

		//if moving in the direction of the bottom wall
		if (holdVel->y < 0)
		{
			if (holdPos->y < AEGfxGetWinMinY())
			{
				Vector2D newY;
				newY.x = holdPos->x;
				newY.y = holdPos->y * -1;
				TransformSetTranslation(GameObjectGetTransform(gameObject), &newY);
			}
		}

		//if moving in the direction of the top wall
		if (holdVel->y > 0)
		{
			if (holdPos->y > AEGfxGetWinMaxY())
			{
				Vector2D newY;
				newY.x = holdPos->x;
				newY.y = holdPos->y * -1;
				TransformSetTranslation(GameObjectGetTransform(gameObject), &newY);
			}
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

