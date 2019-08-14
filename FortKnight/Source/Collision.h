//------------------------------------------------------------------------------
//
// File Name:	Collision.h
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Object* ObjectPtr;
typedef struct Human* HumanPtr;
typedef struct Transform* TransformPtr;
typedef struct AEVec2 AEVec2;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
typedef struct Collider Collider;
typedef Collider* ColliderPtr;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void CollisionUpdate(ObjectPtr object);
bool CollidercheckCollision(ColliderPtr collider1, ColliderPtr collider2);

ColliderPtr ColliderCreate();
void ColliderCreateHitBox(HumanPtr parent);
void ColliderDeleteAllHitBoxes();
void ColliderDelete(ColliderPtr* collider);

ObjectPtr ColliderGetParent(ColliderPtr collider);
TransformPtr ColliderGetTransform(ColliderPtr collider);
bool ColliderGetHitbox(ColliderPtr collider);
void ColliderSetParent(ColliderPtr collider, ObjectPtr parent);
void ColliderSetScale(ColliderPtr collider, AEVec2* scale);
void ColliderSetTransform(ColliderPtr collider, TransformPtr newTransform);
void ColliderSetHitbox(ColliderPtr collider, bool hitbox);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

