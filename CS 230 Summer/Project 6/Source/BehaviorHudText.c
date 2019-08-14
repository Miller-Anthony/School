//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorHudText.h"
#include "Behavior.h"
#include "GameObject.h"
#include "ScoreSystem.h"
#include "Stream.h"
#include "Sprite.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

typedef enum HudTextStates
{
	cHudTextInvalid = -1,	// HUD Text has not yet been initialized.
	cHudTextIdle,			// HUD Text will normally remain static.

} HudTextStates;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BehaviorHudText
{
	// Inherit the base behavior structure.
	Behavior	base;

	// Add HUD Text-specific behavior variables.

		// The index used to access values from the Score System.
	ScoreSystemId scoreSystemId;

	// The format string to be used with sprintf_s() when updating the HUD Text object.
	// (For example: "Score: %d")
	// (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
	//	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
	char formatString[32];

	// The buffer to be used with sprintf_s() when updating the HUD Text object.
	// (For example: "Score: 9001")
	// (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
	//	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
	char displayString[32];

	// The value currently being displayed by the HUD Text object.
	// (NOTE: This value can be compared with *watchValue to determine when the text must be updated.)
	// (NOTE: Make sure to update this value each time the text is updated.)
	int displayValue;

} BehaviorHudText, *BehaviorHudTextPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorHudTextUpdateText(BehaviorHudTextPtr hudText);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Bullet) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorHudTextCreate(void)
{
	BehaviorHudTextPtr holder = calloc(1, sizeof(BehaviorHudText));

	holder->base.stateCurr = cHudTextInvalid;
	holder->base.stateNext = cHudTextIdle;
	holder->base.onInit = BehaviorHudTextInit;
	holder->base.onUpdate = BehaviorHudTextUpdate;
	holder->base.onExit = BehaviorHudTextExit;
	holder->base.memorySize = sizeof(BehaviorHudText);

	return (BehaviorPtr)holder;
}

// Read the properties of a Behavior component from a file.
// [NOTE: Read the base Behavior values using BehaviorRead.]
// [NOTE: Read the format string using StreamReadString.]
// Params:
//	 behavior = Pointer to the Behavior component.
//	 stream = Pointer to the data stream used for reading.
void BehaviorHudTextRead(BehaviorPtr behavior, Stream stream)
{
	if (behavior && stream)
	{
		BehaviorRead(behavior, stream);
		BehaviorHudTextPtr text = (BehaviorHudTextPtr)behavior;
		strcpy_s(text->formatString, 32, StreamReadToken(stream));
		text->scoreSystemId = StreamReadInt(stream);
	}
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorHudTextInit(BehaviorPtr behavior)
{
	BehaviorHudTextPtr holder = (BehaviorHudTextPtr)behavior;
	SpritePtr holdSprite = GameObjectGetSprite(holder->base.parent);
	SpriteSetText(holdSprite, holder->displayString);
	BehaviorHudTextUpdateText(holder);
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorHudTextUpdate(BehaviorPtr behavior, float dt)
{
	dt;
	if (behavior)
	{
		BehaviorHudTextPtr holder = (BehaviorHudTextPtr)behavior;
		if (holder->displayValue != ScoreSystemGetValue(holder->scoreSystemId))
		{
			BehaviorHudTextUpdateText(holder);
		}
	}
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorHudTextExit(BehaviorPtr behavior)
{
	behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorHudTextUpdateText(BehaviorHudTextPtr hudText)
{
	if (hudText)
	{
		if (hudText->scoreSystemId != SsiInvalid)
		{
			hudText->displayValue = ScoreSystemGetValue(hudText->scoreSystemId);
			sprintf_s(hudText->displayString, sizeof(hudText->displayString), hudText->formatString, hudText->displayValue);
		}
	}
}