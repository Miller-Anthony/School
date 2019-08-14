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
#include "Animation.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"
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

	// Flag to indicate that the game object is dead and should be destroyed.
	bool isDestroyed;

	// Pointer to an attached animation component.
	AnimationPtr animation;

	// Pointer to an attached behavior component.
	BehaviorPtr behavior;

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

// Dynamically allocate a clone of an existing game object.
// (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
// (WARNING: When you clone the behavior component you need to change the 'parent' variable.)
// Params:
//	 other = Pointer to the game object to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned object,
//	   else return NULL.
GameObjectPtr GameObjectClone(const GameObjectPtr other)
{
	if (other)
	{
		GameObjectPtr holder = calloc(1, sizeof(GameObject));
		if (holder)
		{
			GameObjectSetName(holder, other->name);

			if (other->animation)
			{
				GameObjectAddAnimation(holder, AnimationClone(other->animation));
			}

			if (other->behavior)
			{
				GameObjectAddBehavior(holder, BehaviorClone(other->behavior));
			}

			if (other->physics)
			{
				GameObjectAddPhysics(holder, PhysicsClone(other->physics));
			}

			if (other->sprite)
			{
				GameObjectAddSprite(holder, SpriteClone(other->sprite));
			}

			if (other->transform)
			{
				GameObjectAddTransform(holder, TransformClone(other->transform));
			}
			return holder;
		}
	}
	return NULL;
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
		AnimationFree(&((*gameObject)->animation));
		BehaviorFree(&((*gameObject)->behavior));
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
			else if (strcmp(holder, "Animation") == 0)
			{
				AnimationPtr holdAnimation = AnimationCreate();
				AnimationRead(holdAnimation, stream);
				GameObjectAddAnimation(gameObject, holdAnimation);
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
			else if (strcmp(holder, "BehaviorSpaceship") == 0)
			{
				BehaviorPtr ship = BehaviorSpaceshipCreate();
				BehaviorRead(ship, stream);
				GameObjectAddBehavior(gameObject, ship);

			}
			else if (strcmp(holder, "BehaviorBullet") == 0)
			{
				BehaviorPtr bullet = BehaviorBulletCreate();
				BehaviorRead(bullet, stream);
				GameObjectAddBehavior(gameObject, bullet);
			}
			else if (strlen(holder) == 0)
			{
				break;
			}
		}
	}
}

// Flag a game object for destruction.
// (Note: This is to avoid game objects being destroyed while they are being processed.)
// Params:
//	 gameObject = Pointer to the game object to be destroyed.
// Returns:
//	 If 'gameObject' is valid,
//	   then set the 'isDestroyed' boolean variable,
//	   else do nothing.
void GameObjectDestroy(GameObjectPtr gameObject)
{
    if (gameObject)
	{
		gameObject->isDestroyed = true;
	}
}

// Check whether a game object has been flagged for destruction.
// Params:
//	 gameObject = Pointer to the game object to be checked.
// Returns:
//	 If 'gameObject' is valid,
//	   then return the 'isDestroyed' boolean variable,
//	   else return false.
bool GameObjectIsDestroyed(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->isDestroyed;
	}
	return false;
}

// Attach an animation component to a game object.
// (NOTE: This function must set the animation component's parent pointer by
//	  calling the AnimationSetParent() function.)
// Params:
//	 gameObject = Pointer to the game object.
//   animation = Pointer to the animation component to be attached.
void GameObjectAddAnimation(GameObjectPtr gameObject, AnimationPtr animation)
{
	if (gameObject && animation)
	{
		gameObject->animation = animation;
		AnimationSetParent(animation, gameObject);
	}
}

// Attach a behavior component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   behavior = Pointer to the behavior component to be attached.
void GameObjectAddBehavior(GameObjectPtr gameObject, BehaviorPtr behavior)
{
	if (gameObject && behavior)
	{
		gameObject->behavior = behavior;
		behavior->parent = gameObject;
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

// Compare the game object's name with the specified name.
// Params:
//	 gameObject = Pointer to the game object.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the game object pointer is valid,
//		then return true if the names match, false otherwise,
//		else return false.
bool GameObjectIsNamed(const GameObject * gameObject, const char * name)
{
	if (gameObject)
	{
		return !strcmp(gameObject->name , name);
	}
	return false;
}

// Get the animation component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached animation component,
//		else return NULL.
AnimationPtr GameObjectGetAnimation(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->animation;
	}
	return NULL;
}

// Get the behavior component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached behavior component,
//		else return NULL.
BehaviorPtr GameObjectGetBehavior(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->behavior;
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
		AnimationUpdate(gameObject->animation, dt);
		BehaviorUpdate(gameObject->behavior, dt);
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

