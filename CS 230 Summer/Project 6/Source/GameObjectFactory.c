//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Stream.h"

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

// Build a single instance of the specified game object.
// Params:
//	 filename = The name of the file to be deserialized.
// Returns:
//	 If the filename is valid
//	   then return a pointer to a new instance of the specified game object,
//	   else NULL.
GameObjectPtr GameObjectFactoryBuild(const char * objectName)
{
	if (objectName)
	{
		GameObjectPtr object = GameObjectManagerGetArchetype(objectName);

		if (!object)
		{
			char pathName[FILENAME_MAX] = "";
			sprintf_s(pathName, _countof(pathName), "Data/%s.txt", objectName);

			Stream stream = StreamOpen(pathName);

			if (stream)
			{
				const char * holder = StreamReadToken(stream);

				if (strncmp(holder, "GameObject", _countof("GameObject")) == 0)
				{
					object = GameObjectCreate();
					GameObjectRead(object, stream);
					GameObjectManagerAddArchetype(object);
				}
				StreamClose(&stream);
			}
		}

		if (object)
		{
			return GameObjectClone(object);
		}
	}
	return NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

