//------------------------------------------------------------------------------
//
// File Name:	Collision.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Collision.h"
#include "Objects.h"
#include "AEVec2.h"
#include "Transform.h"
#include "CollisionResolution.h"
#include "Text.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Collider
{
	ObjectPtr parent;
	TransformPtr transform;
	ColliderPtr next;
	bool hitbox;
}Collider;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

ColliderPtr head = NULL;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
 
static void ColliderLLAdd(ColliderPtr collider);
static void ColliderLLDelete(ColliderPtr collider);
static void ColliderLLClearAll(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void CollisionUpdate(ObjectPtr object)
{
	if (object != NULL)
	{
		ColliderPtr objectCollider = ObjectGetCollider(object);
    if (!objectCollider)
        return;
		ColliderPtr current = head;

		AEVec2 translationCollider1 = *TransformGetTranslation(ColliderGetTransform(ObjectGetCollider(object)));
		AEVec2 translationObject1 = *TransformGetTranslation(ObjectGetTransform(object));
		
		translationCollider1.y = translationObject1.y;
		translationCollider1.x = translationObject1.x;

		TransformSetTranslation(objectCollider->transform, &translationCollider1);

		while (current != NULL)
		{
			if (objectCollider != current)
			{
				if (current->hitbox == false && current->parent != NULL)
				{
					AEVec2 translationCollider = *TransformGetTranslation(ColliderGetTransform(current));
					AEVec2 translationObject = *TransformGetTranslation(ObjectGetTransform(current->parent));

					translationCollider.x = translationObject.x;
					translationCollider.y = translationObject.y;

					TransformSetTranslation(current->transform, &translationCollider);
				}

				if (ObjectGetTag(current->parent) != ItemTag)
				{
					if (CollidercheckCollision(objectCollider, current) == true)
					{
						if (ObjectGetTag(object) == EnemyTag)
						{
							CollisionEnemyResolution(object, current->parent);
						}
						else if (ObjectGetTag(object) == PlayerTag || ObjectGetTag(object) == Player2Tag)
						{
							CollisionPlayerResolution(object, current->parent);
						}
					}
				}
			}

			current = current->next;
		}
	}
}


bool CollidercheckCollision(ColliderPtr collider1, ColliderPtr collider2)
{
	AEVec2 translation1 = *TransformGetTranslation(collider1->transform);
	AEVec2 translation2 = *TransformGetTranslation(collider2->transform);

	AEVec2 scale1 = *TransformGetScale(collider1->transform);
	AEVec2 scale2 = *TransformGetScale(collider2->transform);

	if (translation1.x - scale1.x < translation2.x + scale2.x &&
		translation1.x + scale1.x > translation2.x - scale2.x &&
		translation1.y - scale1.y < translation2.y + scale2.y &&
		translation1.y + scale1.y > translation2.y - scale2.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ColliderPtr ColliderCreate(void)
{
	ColliderPtr collider = calloc(1, sizeof(Collider));

	if (collider != NULL)
	{
		ColliderLLAdd(collider);
		return collider;
	}
	else
	{
		return NULL;
	}
}

void ColliderCreateHitBox(HumanPtr parent)
{
	ObjectPtr parentObject = ObjectGetObject(parent, NULL, NULL, NULL);
	TransformPtr transform = TransformCreate(0, 0);
	AEVec2* scale = TransformGetScale(transform);
	AEVec2* objectScale = TransformGetScale(ColliderGetTransform(ObjectGetCollider(parentObject)));
	AEVec2* translation = TransformGetTranslation(transform);
	AEVec2* objectTranslation = TransformGetTranslation(ColliderGetTransform(ObjectGetCollider(parentObject)));
	ColliderPtr hitboxCollider = ColliderCreate();

	//check direction of the object
	//if the object is facing up or down
	if (HumanGetFaceDir(parent) == up ||
		HumanGetFaceDir(parent) == down)
	{
		//set the Y scale to range and X scale to object's X scale
		scale->x = TransformGetScale(ObjectGetTransform(parentObject))->x;
		scale->y = ItemGetRange(HumanGetWeapon(parent));
	}
	//else if the object is facing right or left
	else if (HumanGetFaceDir(parent) == right ||
		HumanGetFaceDir(parent) == left)
	{
		//set the X scale to range and Y scale to object's Y scale
		scale->x = ItemGetRange(HumanGetWeapon(parent));
		scale->y = TransformGetScale(ObjectGetTransform(parentObject))->y;
	}

	if (HumanGetFaceDir(parent) == up)
	{
		translation->x = objectTranslation->x;
		translation->y = objectTranslation->y + (objectScale->y / 2.0f + scale->y / 2.0f);
	}
	else if (HumanGetFaceDir(parent) == down)
	{
		translation->x = objectTranslation->x;
		translation->y = objectTranslation->y - (objectScale->y / 2.0f + scale->y / 2.0f);
	}
	else if (HumanGetFaceDir(parent) == right)
	{
		translation->x = objectTranslation->x + (objectScale->x / 2.0f + scale->x / 2.0f);
		translation->y = objectTranslation->y;
	}
	else if (HumanGetFaceDir(parent) == left)
	{
		translation->x = objectTranslation->x - (objectScale->x / 2.0f + scale->x / 2.0f);
		translation->y = objectTranslation->y;
	}

	TransformSetScale(transform, scale);
	TransformSetTranslation(transform, translation);
	ColliderSetTransform(hitboxCollider, transform);
	ColliderSetParent(hitboxCollider, parentObject);
	ColliderSetHitbox(hitboxCollider, true);
}

void ColliderDeleteAllHitBoxes()
{
	ColliderPtr current = head;
	ColliderPtr temp = NULL;

	while (current != NULL)
	{
		if (current->hitbox == true)
		{
			temp = current->next;
			ColliderDelete(&current);
			current = temp;
		}
		else
		{
			current = current->next;
		}
	}
}

void ColliderDelete(ColliderPtr* collider)
{
	if (collider != NULL && *collider != NULL)
	{
		ColliderLLDelete(*collider);
		free((*collider)->transform);
		free(*collider);
		*collider = NULL;
	}
}

void ColliderClearALL(void)
{
	ColliderLLClearAll();
}

#pragma region GETTERS
ObjectPtr ColliderGetParent(ColliderPtr collider)
{
	if (collider != NULL)
	{
		return collider->parent;
	}
	else
	{
		return NULL;
	}
}

TransformPtr ColliderGetTransform(ColliderPtr collider)
{
	if (collider != NULL)
	{
		return collider->transform;
	}
	else
	{
		return NULL;
	}
}

bool ColliderGetHitbox(ColliderPtr collider)
{
	if (collider != NULL)
	{
		return collider->hitbox;
	}
	else
	{
		return false;
	}
}
#pragma endregion

#pragma region SETTERS
void ColliderSetParent(ColliderPtr collider, ObjectPtr parent)
{
	if (collider != NULL)
	{
		collider->parent = parent;
	}
}

void ColliderSetTransform(ColliderPtr collider, TransformPtr newTransform)
{
	if (collider != NULL)
	{
		collider->transform = newTransform;
	}
}

void ColliderSetScale(ColliderPtr collider, AEVec2* scale)
{
	if (scale != NULL)
	{
		TransformSetScale(collider->transform, scale);
	}
}

void ColliderSetHitbox(ColliderPtr collider, bool hitbox)
{
	collider->hitbox = hitbox;
}
#pragma endregion

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

#pragma region LINKEDLIST
static void ColliderLLAdd(ColliderPtr collider)
{
	if (collider != NULL)
	{
		if (head == NULL)
		{
			head = collider;
		}
		else
		{
			collider->next = head;
			head = collider;
		}
	}
}
static void ColliderLLDelete(ColliderPtr collider)
{
	ColliderPtr previous = head;
	ColliderPtr current = head;

	if (collider != NULL)
	{
		if (collider == head)
		{
			head = collider->next;
		}
		else
		{
			while (current != NULL)
			{
				if (current == collider)
				{
					previous->next = current->next;
					return;
				}

				previous = current;
				current = current->next;
			}
		}
	}
}

static void ColliderLLClearAll(void)
{
	ColliderPtr temp;

	while (head != NULL)
	{
		temp = head->next;
		ColliderLLDelete(head);
		head = temp;
	}
	
	head = NULL;
}
#pragma endregion