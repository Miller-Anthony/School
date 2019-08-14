//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Knightmare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//#include "AnimationSequence.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Animation * AnimationPtr;
typedef struct Sprite * SpritePtr;
typedef struct SpriteSource* SpriteSourcePtr;
//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new animation object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 sprite = Pointer to the sprite object associated with the animation.
AnimationPtr AnimationCreate(SpritePtr sprite);

// Free the memory associated with an animation.
// (Also, set the animation pointer to NULL.)
// Params:
//	 animation = Pointer to the animation pointer.
void AnimationFree(AnimationPtr * animation);

// Play a simple animation sequence (0 .. frameCount).
// (Hint: Make sure to initialize all variables, except for "sprite".)
// Params:
//	 animation = Pointer to the animation object.
//	 frameCount = The number of frames in the sequence.
//	 frameDuration = The amount of time to wait between frames (in seconds).
//	 isLooping = True if the animation loops, false otherwise.
void AnimationPlay(AnimationPtr animation, int frameCount, float frameDuration, SpriteSourcePtr overrideSS, bool isLooping);

void AnimationSetSpriteSource(AnimationPtr animation, SpriteSourcePtr spriteSource);

// Play a complex animation sequence (any frame/any delay).
// (Hint: Make sure to initialize all variables, except for "sprite".)
// Params:
//	 animation = Pointer to the animation object.
//	 sequence = Pointer to the animation sequence to be played.
//void AnimationPlaySequence(AnimationPtr animation, AnimationSequencePtr sequence);

// Update the animation.
// Params:
//	 animation = Pointer to the animation object.
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(AnimationPtr animation);

// Determine if the animation has reached the end of its sequence.
// Params:
//	 animation = Pointer to the animation object.
// Returns:
//	 If the animation pointer is valid,
//		then return the value in isDone,
//		else return false.
bool AnimationIsDone(AnimationPtr animation);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

