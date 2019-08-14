//------------------------------------------------------------------------------
//
// File Name:	Component.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 1
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "GameObject.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class GameObject GameObject, *GameObjectPtr;
typedef class Component * ComponentPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum
{
	AnimationType, 
	//Behavior, 
	ColliderType, 
	PhysicsType, 
	SpriteType, 
	TransformType,
	numTypes,
}ComponentType;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef class Component
{
public:

	Component(ComponentType setType) { type = setType; }

	virtual ComponentPtr Clone(void) const = 0;

	virtual void Update(float dt);

	virtual void Draw() const;

	ComponentType GetType(void);

	void SetParent(GameObjectPtr newParent);

	GameObjectPtr GetParent(void);

private:

	ComponentType type;

	GameObjectPtr parent;

} Component;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void ComponentInit();

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void ComponentUpdate(float dt);

// Shutdown the ...
void ComponentShutdown();

//------------------------------------------------------------------------------
