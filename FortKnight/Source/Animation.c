//------------------------------------------------------------------------------
//
// File Name:	Animation.c
// Author(s):	Brayan Lopez
// Project:		Project2
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "Sprite.h"
#include "DT.h"
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Animation
{
    // Pointer to the sprite associated with the animation.
    SpritePtr sprite;

    // The current frame being displayed.
    unsigned int frameIndex;

    // The maximum number of frames in the sequence.
    unsigned int frameCount;

    // The time remaining for the current frame.
    float frameDelay;

    // The amount of time to display each frame.
    // (Used only when playing simple animations (0 .. numFrame).)
    float frameDuration;

    // True if the animation is running; false if the animation has stopped.
    bool isRunning;

    // True if the animation loops back to the beginning.
    bool isLooping;

    // True if the end of the animation has been reached, false otherwise.
    // (Hint: This should be true for only one game loop.)
    bool isDone;

    //has updated this frame (frameIndex changed)
    //bool hasUpdated;

    // The animation sequence currently being played, if any.
    //AnimationSequencePtr	sequence;

} Animation;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//Advances animation frame
static void AnimationAdvanceFrame(AnimationPtr animation);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new animation object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 sprite = Pointer to the sprite object associated with the animation.
AnimationPtr AnimationCreate(SpritePtr sprite)
{
    AnimationPtr animPtr = (AnimationPtr)calloc(1, sizeof(Animation));

    if (animPtr)
        animPtr->sprite = sprite;

    return animPtr;
}

// Free the memory associated with an animation.
// (Also, set the animation pointer to NULL.)
// Params:
//	 animation = Pointer to the animation pointer.
void AnimationFree(AnimationPtr * animation)
{
    if (animation)
    {
        free(*animation);
        *animation = NULL;
    }
}

// Play a simple animation sequence (0 .. frameCount).
// (Hint: Make sure to initialize all variables, except for "sprite".)
// Params:
//	 animation = Pointer to the animation object.
//	 frameCount = The number of frames in the sequence.
//	 frameDuration = The amount of time to wait between frames (in seconds).
//	 isLooping = True if the animation loops, false otherwise.
void AnimationPlay(AnimationPtr animation, int frameCount, float frameDuration, SpriteSourcePtr overrideSS, bool isLooping)
{
    if (animation)
    {
        animation->frameCount = frameCount;
        animation->frameDuration = frameDuration;
        animation->isLooping = isLooping;
        animation->frameDelay = frameDuration;
        //animation->frameIndex = 0;
        animation->isDone = false;
        animation->isRunning = true;
        if (overrideSS)
            SpriteSetSpriteSource(animation->sprite, overrideSS);
        //SpriteSetFrame(animation->sprite, 0);
        //animation->hasUpdated = false;
    }
}

void AnimationSetSpriteSource(AnimationPtr animation, SpriteSourcePtr spriteSource)
{
    if (animation)
        SpriteSetSpriteSource(animation->sprite, spriteSource);

}

// Update the animation.
// Params:
//	 animation = Pointer to the animation object.
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(AnimationPtr animation)
{
    if (animation)
    {
        animation->isDone = false;
        if (animation->isRunning)
        {
            animation->frameDelay -= dt;
            if (animation->frameDelay <= 0)
            {
                //unsigned frameIndexBefore = animation->frameIndex;
                AnimationAdvanceFrame(animation);
                //animation->hasUpdated = frameIndexBefore != animation->frameIndex;
            }
        }
    }
}

// Determine if the animation has reached the end of its sequence.
// Params:
//	 animation = Pointer to the animation object.
// Returns:
//	 If the animation pointer is valid,
//		then return the value in isDone,
//		else return false.
bool AnimationIsDone(AnimationPtr animation)
{
    if (animation)
        return animation->isDone;

    return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

//Advance animation frame
static void AnimationAdvanceFrame(AnimationPtr animation)
{
    if (animation)
    {
        //if(!animation->hasUpdated)
        animation->frameIndex++;
        if (animation->frameIndex >= animation->frameCount)
        {
            if (animation->isLooping)
                animation->frameIndex = 0;
            else
            {
                animation->frameIndex = animation->frameCount - 1;
                animation->isRunning = false;
            }
            animation->isDone = true;
        }

        if (animation->isRunning)
        {
            SpriteSetFrame(animation->sprite, animation->frameIndex);
            animation->frameDelay += animation->frameDuration;
        }
        else
            animation->frameDelay = 0;
    }
}
