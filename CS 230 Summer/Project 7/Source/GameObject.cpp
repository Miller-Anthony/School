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
//#include "Behavior.h"
//#include "BehaviorSpaceship.h"
//#include "BehaviorBullet.h"
//#include "BehaviorAsteroid.h"
//#include "BehaviorHudText.h"
#include "Stream.h"
//#include "Collider.h"
//#include "ColliderCircle.h"
//#include "ColliderLine.h"

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

// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
GameObject::GameObject(void)
{

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
		GameObjectPtr holder = new GameObject;
		if (holder)
		{
			holder->SetName(other->GetName());

			if (other->GetAnimation())
			{
				holder->AddComponent(other->GetAnimation()->Clone());
			}

			//if (other->GetBehavior)
			//{
			//	holder->AddBehavior(BehaviorClone(other->GetBehavior));
			//}

			//if (other->GetCollider)
			//{
			//	holder->AddCollider(ColliderClone(other->GetCollider));
			//}

			if (other->GetPhysics())
			{
				holder->AddComponent((other->GetPhysics())->Clone());
			}

			if (other->GetSprite())
			{
				holder->AddComponent(other->GetSprite()->Clone());
			}

			if (other->GetTransform())
			{
				holder->AddComponent(other->GetTransform()->Clone());
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
GameObject::~GameObject(void)
{
	components.clear();
	/*delete sprite;
	sprite = NULL;
	delete animation;
	animation = NULL;
	//delete behavior;
	//delete collider;
	delete physics;
	physics = NULL;
	delete transform;
	transform = NULL;*/
}

// Read (and construct) the components associated with a game object.
// [NOTE: See project instructions for implementation instructions.]
// Params:
//	 gameObject = Pointer to the game object.
//	 stream = Pointer to the data stream used for reading.
void GameObject::Read(Stream stream)
{
	if (stream)
	{
		SetName(StreamReadToken(stream));
		
		while (true)
		{
			const char * holder = StreamReadToken(stream);
			if (strcmp(holder, "Transform") == 0)
			{
				TransformPtr holdTransform = new Transform;
				holdTransform->Read(stream);
				holdTransform->SetParent(this);
				AddComponent(holdTransform);
			}
			else if (strcmp(holder, "Animation") == 0)
			{
				AnimationPtr holdAnimation = new Animation;
				holdAnimation->Read(stream);
				holdAnimation->SetParent(this);
				AddComponent(holdAnimation);
			}
			else if (strcmp(holder, "Physics") == 0)
			{
				PhysicsPtr holdPhysics = new Physics;
				holdPhysics->Read(stream);
				holdPhysics->SetParent(this);
				AddComponent(holdPhysics);
			}
			else if (strcmp(holder, "Sprite") == 0)
			{
				SpritePtr holdSprite = new Sprite;
				holdSprite->Read(stream);
				holdSprite->SetParent(this);
				AddComponent(holdSprite);
			}
			/*else if (strcmp(holder, "BehaviorSpaceship") == 0)
			{
				BehaviorPtr ship = new BehaviorSpaceship);
				ship->Read(stream);
				AddBehavior(ship);

			}
			else if (strcmp(holder, "BehaviorBullet") == 0)
			{
				BehaviorPtr bullet = new BehaviorBullet;
				bullet->Read(stream);
				AddBehavior(bullet);
			}
			else if (strcmp(holder, "BehaviorAsteroid") == 0)
			{
				BehaviorPtr asteroid = new BehaviorAsteroid;
				asteroid->Read(stream);
				AddBehavior(asteroid);
			}
			else if (strcmp(holder, "BehaviorHudText") == 0)
			{
				BehaviorPtr hudText = new BehaviorHudText;
				hudText->Read(stream);
				AddBehavior(hudText);
			}
			else if (strcmp(holder, "ColliderCircle") == 0)
			{
				ColliderPtr collider = new ColliderCircle;
				collider->Read(stream);
				AddCollider(collider);
			}
			else if (strcmp(holder, "ColliderLine") == 0)
			{
				ColliderPtr collider = new ColliderLine;
				collider->Read(stream);
				AddCollider(collider);
			}*/
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
void GameObject::Destroy(void)
{
	isDestroyed = true;
}

// Check whether a game object has been flagged for destruction.
// Params:
//	 gameObject = Pointer to the game object to be checked.
// Returns:
//	 If 'gameObject' is valid,
//	   then return the 'isDestroyed' boolean variable,
//	   else return false.
bool GameObject::IsDestroyed(void)
{
	if (this)
	{
		return isDestroyed;
	}
	return false;
}

void GameObject::AddComponent(ComponentPtr component)
{
	components.push_back(component);
}

// Attach an animation component to a game object.
// (NOTE: This function must set the animation component's parent pointer by
//	  calling the AnimationSetParent() function.)
// Params:
//	 gameObject = Pointer to the game object.
//   animation = Pointer to the animation component to be attached.
/*void GameObject::AddAnimation(AnimationPtr newAnimation)
{
	if (newAnimation)
	{
		animation = newAnimation;
		newAnimation->SetParent(this);
	}
}

// Attach a behavior component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   behavior = Pointer to the behavior component to be attached.
//void GameObject::AddBehavior(BehaviorPtr behavior)
//{
//	if (behavior)
//	{
//		this->behavior = behavior;
//		behavior->SetParent(this);
//	}
//}

// Attach a collider component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   collider = Pointer to the collider component to be attached.
//void GameObject::AddCollider(ColliderPtr collider)
//{
//	if (collider)
//	{
//		this->collider = collider;
//		collider->SetParent(this);
//	}
//}

// Attach a physics component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   physics = Pointer to the physics component to be attached.
void GameObject::AddPhysics(PhysicsPtr newPhysics)
{
	if (newPhysics)
	{
		physics = newPhysics;
	}
}

// Attach a sprite component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   sprite = Pointer to the sprite component to be attached.
void GameObject::AddSprite(SpritePtr newSprite)
{
	if (newSprite)
	{
		sprite = newSprite;
	}
}

// Attach a transform component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   transform = Pointer to the transform component to be attached.
void GameObject::AddTransform(TransformPtr newTransform)
{
	if (newTransform)
	{
		transform = newTransform;
	}
}*/

// Set the game object's name.
// [NOTE: Verify that both pointers are valid before setting the name.]
// [NOTE: When setting the name, use strncpy_s() to reduce the risk of
//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
//	 calling this function!  Instead, use the _countof() macro to get the
//	 size of the "name" array.]
// Params:
//	 gameObject = Pointer to the game object.
//	 name = Pointer to the game object's new name.
void GameObject::SetName(const char * newName)
{
	if (newName)
	{
		strncpy_s(name, _countof(name), newName, _countof(name));
	}
}

// Get the game object's name.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the game object's name,
//		else return NULL.
const char * GameObject::GetName(void)
{
	return name;
}

// Compare the game object's name with the specified name.
// Params:
//	 gameObject = Pointer to the game object.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the game object pointer is valid,
//		then return true if the names match, false otherwise,
//		else return false.
bool GameObject::IsNamed(const char * check)
{
	return !strcmp(name , check);
}

// Get the animation component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached animation component,
//		else return NULL.
AnimationPtr GameObject::GetAnimation(void)
{
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i]->GetType() == AnimationType)
		{
			return (AnimationPtr)components[i];
		}
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
//BehaviorPtr GameObject::GetBehavior(void)
//{
//	return behavior;
//}

// Get the collider component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached collider component,
//		else return NULL.
//ColliderPtr GameObject::GetCollider(void)
//{
//	return collider;
//}

// Get the physics component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
PhysicsPtr GameObject::GetPhysics(void)
{
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i]->GetType() == PhysicsType)
		{
			return (PhysicsPtr)components[i];
		}
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
SpritePtr GameObject::GetSprite(void)
{
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i]->GetType() == SpriteType)
		{
			return (SpritePtr)components[i];
		}
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
TransformPtr GameObject::GetTransform(void)
{
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i]->GetType() == TransformType)
		{
			return (TransformPtr)components[i];
		}
	}
	return NULL;
}

// Update any components attached to the game object.
// (Hint: You will need to call PhysicsUpdate().)
// (NOTE: You must first check for a valid pointer before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
//	 dt = Change in time (in seconds) since the last game loop.
void GameObject::Update(float dt)
{
	if (GetAnimation())
	{
		GetAnimation()->Update(dt);
	}
	
	//behavior->Update(dt);
	if (GetPhysics())
	{
		GetPhysics()->Update(dt);
	}
	
}

// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObject::Draw(void)
{
	if (GetSprite() && GetTransform())
	{
		GetSprite()->Draw();
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

