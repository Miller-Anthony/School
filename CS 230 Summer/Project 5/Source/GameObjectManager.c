//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectManager.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct GameObjectManager
{
	// The current number of game objects currently in the list.
	unsigned int objectCount;

	// The maximum number of game objects ever in the list, at any given moment.
	unsigned int objectMax;

	// This list can be a fixed-length array (minimum size of 100 entries)
	// or a dynamically sized array, such as a linked list.
	GameObjectPtr	objectList[100];

} GameObjectManager;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static GameObjectManager gameObjectActiveList;
static GameObjectManager gameObjectArchetypes;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the game object manager.
// (NOTE: This function should initialize the lists for both active game objects
//    and the archetype objects.)
void GameObjectManagerInit(void)
{
	unsigned int i; //looping variable

	gameObjectActiveList.objectCount = 0;
	gameObjectActiveList.objectMax = 100;

	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		gameObjectActiveList.objectList[i] = 0;
	}

	gameObjectArchetypes.objectCount = 0;
	gameObjectArchetypes.objectMax = 100;

	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		gameObjectActiveList.objectList[i] = 0;
	}
}

// Update all objects in the active game objects list.
// (NOTE: After a game object has been updated, if it has been flagged as
//    destroyed, then it must be removed from the list and freed properly.
//    Additionally, the count of active objects must be reduced by 1.)
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManagerUpdate(float dt)
{
	unsigned int i; // loop variable

	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		if (gameObjectActiveList.objectList[i])
		{
			GameObjectUpdate(gameObjectActiveList.objectList[i], dt);
		}

		if (GameObjectIsDestroyed(gameObjectActiveList.objectList[i]))
		{
			GameObjectFree(&gameObjectActiveList.objectList[i]);
			gameObjectActiveList.objectList[i] = NULL;
			gameObjectActiveList.objectCount -= 1;
		}
	}
}

// Check collisions between all objects held by the game object manager.
void GameObjectManagerCheckCollisions(void)
{
	unsigned int i, j; // ooping variables

	//for all objects in the list
	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		//for all remaining object in list
		for (j = i + 1; j < gameObjectActiveList.objectMax; j++)
		{
			if (GameObjectGetCollider(gameObjectActiveList.objectList[i]) != NULL && GameObjectGetCollider(gameObjectActiveList.objectList[j]) != NULL)
			{
				ColliderCheck(GameObjectGetCollider(gameObjectActiveList.objectList[i]), GameObjectGetCollider(gameObjectActiveList.objectList[j]));
			}
		}
	}
}

// Draw all game objects in the active game object list.
void GameObjectManagerDraw(void)
{
	unsigned int i; // loop variable

	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		if (gameObjectActiveList.objectList[i])
		{
			GameObjectDraw(gameObjectActiveList.objectList[i]);
		}
	}
}

// Shutdown the game object manager.
// (NOTE: This means removing all game objects from both the active and
//	  archetype game object lists.  Make sure that the object counts are
//	  properly updated in both situations.)
void GameObjectManagerShutdown(void)
{
	unsigned int i; // loop variable

	for (i = 0; i < gameObjectActiveList.objectMax; i++)
	{
		if (gameObjectActiveList.objectList[i])
		{
			GameObjectFree(&gameObjectActiveList.objectList[i]);
			gameObjectActiveList.objectList[i] = NULL;
			gameObjectActiveList.objectCount -= 1;
		}
	}

	for (i = 0; i < gameObjectArchetypes.objectMax; i++)
	{
		if (gameObjectArchetypes.objectList[i])
		{
			GameObjectFree(&gameObjectArchetypes.objectList[i]);
			gameObjectArchetypes.objectList[i] = NULL;
			gameObjectArchetypes.objectCount -= 1;
		}
	}
}

// Add a game object to the active game object list.
// (Hint: This function and the GameObjectManagerAddArchetype functions require
//    the same code.  Consider creating a single function that adds an object
//	  to a list that is passed as a parameter.)
// Params:
//	 gameObject = Pointer to the game object to be added to the list.
void GameObjectManagerAdd(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		int i = 0; //looping variable

		while (gameObjectActiveList.objectList[i])
		{
			i++;
		}

		gameObjectActiveList.objectList[i] = gameObject;
		gameObjectActiveList.objectCount += 1;
	}
}

// Add a game object to the game object archetype list.
// (Hint: This function and the GameObjectManagerAdd functions require
//    the same code.  Consider creating a single, private function that adds
//	 an object to a list that is passed as a parameter.)
// Params:
//	 gameObject = Pointer to the game object to be added to the list.
void GameObjectManagerAddArchetype(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		int i = 0; //looping variable

		while (gameObjectArchetypes.objectList[i])
		{
			i++;
		}

		gameObjectArchetypes.objectList[i] = gameObject;
		gameObjectArchetypes.objectCount += 1;
	}
}

// Returns a pointer to the first active game object matching the specified name.
// (Hint: This function and the GameObjectManagerGetObjectByName functions require
//    the same code.  Consider creating a single, private function that searches
//	  for the named game object in a list that is passed as a parameter.)
// Params:
//	 name = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return NULL.
GameObjectPtr GameObjectManagerGetObjectByName(const char * name)
{
	for (unsigned i = 0; i < gameObjectActiveList.objectMax; ++i)
	{
		if (gameObjectActiveList.objectList[i])
		{
			if (!strcmp(GameObjectGetName(gameObjectActiveList.objectList[i]), name))
			{
				return gameObjectActiveList.objectList[i];
			}
		}
	}
	return NULL;
}

// Returns a pointer to the first game object archetype matching the specified name.
// (Hint: This function and the GameObjectManagerGetObjectByName functions require
//    the same code.  Consider creating a single, private function that searches
//	  for the named game object in a list that is passed as a parameter.)
// Params:
//	 name = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return NULL.
GameObjectPtr GameObjectManagerGetArchetype(const char * name)
{
	int i = 0; //looping variable

	while (gameObjectArchetypes.objectList[i])
	{
		if (!strcmp(GameObjectGetName(gameObjectArchetypes.objectList[i]), name))
		{
			return gameObjectArchetypes.objectList[i];
		}
		i++;
	}
	return NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

