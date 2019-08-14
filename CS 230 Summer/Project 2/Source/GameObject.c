//------------------------------------------------------------------------------
//
// File Name:	GameObject.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct GameObject
{
	// The name of the game object.
	// A buffer is used to allow each game object to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strncpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	char name[32];

	// Pointer to an attached physics component.
	PhysicsPtr physics;

	// Pointer to an attached sprite component.
	SpritePtr sprite;

	// Pointer to an attached transform component.
	TransformPtr transform;

} GameObject;

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

// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
GameObjectPtr GameObjectCreate(void)
{
	GameObjectPtr holder = calloc(1, sizeof(GameObject));

	if (!holder)
	{
		return NULL;
	}

	return holder;
}

// Free the memory associated with a game object, including all components.
// (Also, set the game object pointer to NULL.)
// Params:
//	 gameObject = Pointer to the game object pointer.
void GameObjectFree(GameObjectPtr * gameObject)
{
	if (gameObject)
	{
		SpriteFree(&((*gameObject)->sprite));
		PhysicsFree(&((*gameObject)->physics));
		TransformFree(&((*gameObject)->transform));
		free(*gameObject);
		*gameObject = NULL;
	}
}

// Read (and construct) the components associated with a game object.
// [NOTE: See project instructions for implementation instructions.]
// Params:
//	 gameObject = Pointer to the game object.
//	 stream = Pointer to the data stream used for reading.
void GameObjectRead(GameObjectPtr gameObject, Stream stream)
{
	if (gameObject && stream)
	{
		GameObjectSetName(gameObject, StreamReadToken(stream));
		
		while (true)
		{
			const char * holder = StreamReadToken(stream);
			if (strcmp(holder, "Transform") == 0)
			{
				TransformPtr holdTransform = TransformCreate();
				TransformRead(holdTransform, stream);
				GameObjectAddTransform(gameObject, holdTransform);
			}
			else if (strcmp(holder, "Physics") == 0)
			{
				PhysicsPtr holdPhysics = PhysicsCreate();
				PhysicsRead(holdPhysics, stream);
				GameObjectAddPhysics(gameObject, holdPhysics);
			}
			else if (strcmp(holder, "Sprite") == 0)
			{
				SpritePtr holdSprite = SpriteCreate();
				SpriteRead(holdSprite, stream);
				GameObjectAddSprite(gameObject, holdSprite);
			}
			else if (strlen(holder) == 0)
			{
				break;
			}
		}
	}
}

// Attach a physics component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   physics = Pointer to the physics component to be attached.
void GameObjectAddPhysics(GameObjectPtr gameObject, PhysicsPtr physics)
{
	if (gameObject && physics)
	{
		gameObject->physics = physics;
	}
}

// Attach a sprite component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   sprite = Pointer to the sprite component to be attached.
void GameObjectAddSprite(GameObjectPtr gameObject, SpritePtr sprite)
{
	if (gameObject && sprite)
	{
		gameObject->sprite = sprite;
	}
}

// Attach a transform component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   transform = Pointer to the transform component to be attached.
void GameObjectAddTransform(GameObjectPtr gameObject, TransformPtr transform)
{
	if (gameObject && transform)
	{
		gameObject->transform = transform;
	}
}

// Set the game object's name.
// [NOTE: Verify that both pointers are valid before setting the name.]
// [NOTE: When setting the name, use strncpy_s() to reduce the risk of
//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
//	 calling this function!  Instead, use the _countof() macro to get the
//	 size of the "name" array.]
// Params:
//	 gameObject = Pointer to the game object.
//	 name = Pointer to the game object's new name.
void GameObjectSetName(GameObjectPtr gameObject, const char * name)
{
	if (gameObject && name)
	{
		strncpy_s(gameObject->name, _countof(gameObject->name), name, _countof(gameObject->name));
	}
}

// Get the game object's name.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the game object's name,
//		else return NULL.
const char * GameObjectGetName(const GameObject * gameObject)
{
	if (gameObject)
	{
		return gameObject->name;
	}
	return NULL;
}

// Get the physics component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
PhysicsPtr GameObjectGetPhysics(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		PhysicsPtr holder = gameObject->physics;
		return holder;
	}
	return NULL;
}

// Get the sprite component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached sprite component,
//		else return NULL.
SpritePtr GameObjectGetSprite(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		SpritePtr holder = gameObject->sprite;
		return holder;
	}
	return NULL;
}

// Get the transform component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached transform component,
//		else return NULL.
TransformPtr GameObjectGetTransform(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		TransformPtr holder = gameObject->transform;
		return holder;
	}
	return NULL;
}

// Update any components attached to the game object.
// (Hint: You will need to call PhysicsUpdate().)
// (NOTE: You must first check for a valid pointer before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectUpdate(GameObjectPtr gameObject, float dt)
{
	if (gameObject)
	{
		PhysicsUpdate(gameObject->physics, gameObject->transform, dt);
	}
}

// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectDraw(GameObjectPtr gameObject)
{
	if (gameObject->sprite && gameObject->transform)
	{
		SpriteDraw(gameObject->sprite, gameObject->transform);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

