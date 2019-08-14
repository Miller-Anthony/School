//------------------------------------------------------------------------------
//
// File Name:	GameObject.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <vector>
#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class GameObject GameObject, *GameObjectPtr;
typedef class Animation *AnimationPtr;
//typedef class Behavior *BehaviorPtr;
//typedef class Collider *ColliderPtr;
typedef class Physics *PhysicsPtr;
typedef class Sprite *SpritePtr;
typedef class Transform *TransformPtr;
typedef class Component * ComponentPtr;
typedef FILE* Stream;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in GameObject.c.
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef class GameObject
{
public:

	// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
	GameObject(void);

	~GameObject(void);

	// Read (and construct) the components associated with a game object.
	// [NOTE: See project instructions for implementation instructions.]
	// Params:
	//	 gameObject = Pointer to the game object.
	//	 stream = Pointer to the data stream used for reading.
	void Read(Stream stream);

	// Flag a game object for destruction.
	// (Note: This is to avoid game objects being destroyed while they are being processed.)
	// Params:
	//	 gameObject = Pointer to the game object to be destroyed.
	// Returns:
	//	 If 'gameObject' is valid,
	//	   then set the 'isDestroyed' boolean variable,
	//	   else do nothing.
	void Destroy(void);

	// Check whether a game object has been flagged for destruction.
	// Params:
	//	 gameObject = Pointer to the game object to be checked.
	// Returns:
	//	 If 'gameObject' is valid,
	//	   then return the 'isDestroyed' boolean variable,
	//	   else return false.
	bool IsDestroyed(void);

	void AddComponent(ComponentPtr component);

	// Attach an animation component to a game object.
	// (NOTE: This function must set the animation component's parent pointer by
	//	  calling the AnimationSetParent() function.)
	// Params:
	//	 gameObject = Pointer to the game object.
	//   animation = Pointer to the animation component to be attached.
	//void AddAnimation(AnimationPtr animation);

	// Attach a behavior component to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   behavior = Pointer to the behavior component to be attached.
	//void AddBehavior(BehaviorPtr behavior);

	// Attach a collider component to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   collider = Pointer to the collider component to be attached.
	//void AddCollider(ColliderPtr collider);

	// Attach a physics component to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   physics = Pointer to the physics component to be attached.
	//void AddPhysics(PhysicsPtr physics);

	// Attach a sprite component to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   sprite = Pointer to the sprite component to be attached.
	//void AddSprite(SpritePtr sprite);

	// Attach a transform component to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   transform = Pointer to the transform component to be attached.
	//void AddTransform(TransformPtr transform);

	// Set the game object's name.
	// [NOTE: Verify that both pointers are valid before setting the name.]
	// [NOTE: When setting the name, use strncpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	// Params:
	//	 gameObject = Pointer to the game object.
	//	 name = Pointer to the game object's new name.
	void SetName(const char * name);

	// Get the game object's name.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the game object's name,
	//		else return NULL.
	const char * GetName(void);

	// Compare the game object's name with the specified name.
	// Params:
	//	 gameObject = Pointer to the game object.
	//   name = Pointer to the name to be checked.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return true if the names match, false otherwise,
	//		else return false.
	bool IsNamed(const char * name);

	// Get the animation component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached animation component,
	//		else return NULL.
	AnimationPtr GetAnimation(void);

	// Get the behavior component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached behavior component,
	//		else return NULL.
	//BehaviorPtr GetBehavior(void);

	// Get the collider component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached collider component,
	//		else return NULL.
	//ColliderPtr GetCollider(void);

	// Get the physics component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached physics component,
	//		else return NULL.
	PhysicsPtr GetPhysics(void);

	// Get the sprite component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached sprite component,
	//		else return NULL.
	SpritePtr GetSprite(void);

	// Get the transform component attached to a game object.
	// Params:
	//	 gameObject = Pointer to the game object.
	// Returns:
	//	 If the game object pointer is valid,
	//		then return a pointer to the attached transform component,
	//		else return NULL.
	TransformPtr GetTransform(void);

	// Update any components attached to the game object.
	// (Hint: You will need to call AnimationUpdate() and PhysicsUpdate().)
	// (NOTE: You must first check for valid pointers before calling these functions.)
	// Params:
	//	 gameObject = Pointer to the game object.
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Draw any visible components attached to the game object.
	// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
	// (NOTE: You must first check for valid pointers before calling this function.)
	// Params:
	//	 gameObject = Pointer to the game object.
	void Draw(void);

private:
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

	std::vector<ComponentPtr> components;

	// Pointer to an attached animation component.
	//AnimationPtr animation;

	// Pointer to an attached behavior component.
	//BehaviorPtr behavior;

	// Pointer to an attached collider component.
	//ColliderPtr collider;

	// Pointer to an attached physics component.
	//PhysicsPtr physics;

	// Pointer to an attached sprite component.
	//SpritePtr sprite;

	// Pointer to an attached transform component.
	//TransformPtr transform;

} GameObject;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


	// Dynamically allocate a clone of an existing game object.
	// (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
	// (WARNING: When you clone the behavior component you need to change the 'parent' variable.)
	// Params:
	//	 other = Pointer to the game object to be cloned.
	// Returns:
	//	 If 'other' is valid and the memory allocation was successful,
	//	   then return a pointer to the cloned object,
	//	   else return NULL.
	GameObjectPtr GameObjectClone(const GameObjectPtr other);

//------------------------------------------------------------------------------
