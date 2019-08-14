//------------------------------------------------------------------------------
//
// File Name:	CollisionResolution.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "CollisionResolution.h"
#include "Objects.h"
#include "Physics.h"
#include "Transform.h"
#include "Collision.h"
#include "AEVec2.h"

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

void CollisionPlayerResolution(ObjectPtr player, ObjectPtr collisionObject)
{
	PhysicsPtr physics = ObjectGetPhysics(player);
	TransformPtr transformObject = ObjectGetTransform(player);
	TransformPtr transformCollider = ColliderGetTransform(ObjectGetCollider(player));

	if (ObjectGetTag(collisionObject) == EnemyTag/* || ObjectGetTag(collisionObject)==Player2Tag*/)
	{
		AEVec2* translation = PhysicsGetOldTranslation(physics);
		TransformSetTranslation(transformCollider, translation);
		TransformSetTranslation(transformObject, translation);
		ColliderSetTransform(ObjectGetCollider(player), transformCollider);
		ObjectSetTransform(transformObject, player);
	}

}

void CollisionEnemyResolution(ObjectPtr enemy, ObjectPtr collisionObject)
{
	PhysicsPtr physics = ObjectGetPhysics(enemy);
	TransformPtr transformObject = ObjectGetTransform(enemy);
	TransformPtr transformCollider = ColliderGetTransform(ObjectGetCollider(enemy));

	if (ObjectGetTag(collisionObject) == PlayerTag)
	{
		AEVec2* translation = PhysicsGetOldTranslation(physics);
		TransformSetTranslation(transformCollider, translation);
		TransformSetTranslation(transformObject, translation);
		ColliderSetTransform(ObjectGetCollider(enemy), transformCollider);
		ObjectSetTransform(transformObject, enemy);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

