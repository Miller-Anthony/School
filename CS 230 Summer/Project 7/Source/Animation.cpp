//------------------------------------------------------------------------------
//
// File Name:	Animation.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "GameObject.h"
#include "Sprite.h"
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

Animation::Animation(void) : Component(AnimationType)
{

}

// Dynamically allocate a clone of an existing animation.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ComponentPtr Animation::Clone(void) const
{
	AnimationPtr holder = new Animation;
	if (holder)
	{
		*holder = *this;
	}
	return holder;
}

// Read the properties of an Animation component from a file.
// [NOTE: Read the integer values for frameIndex and frameCount.]
// [NOTE: Read the float values for frameDelay and frameDuration.]
// [NOTE: Read the boolean values for isRunning and isLooping.]
// Params:
//	 animation = Pointer to the Animation component.
//	 stream = Pointer to the data stream used for reading.
void Animation::Read(Stream stream)
{
	if (stream)
	{
		frameIndex = StreamReadInt(stream);
		frameCount = StreamReadInt(stream);
		frameDelay = StreamReadFloat(stream);
		frameDuration = StreamReadFloat(stream);
		isRunning = StreamReadBoolean(stream);
		isLooping = StreamReadBoolean(stream);
	}
}

// Set the parent game object for an animation component.
// Params:
//	 animation = Pointer to the animation pointer.
//	 parent = Pointer to the parent game object.
void Animation::SetParent(GameObjectPtr newParent)
{
	if (newParent)
	{
		parent = newParent;
	}
}

// Play a simple animation sequence (0 .. frameCount).
// (Hint: Make sure to initialize all variables, except for "sprite".)
// Params:
//	 animation = Pointer to the animation object.
//	 frameCount = The number of frames in the sequence.
//	 frameDuration = The amount of time to wait between frames (in seconds).
//	 isLooping = True if the animation loops, false otherwise.
void Animation::Play(int newFrameCount, float newFrameDuration, bool newIsLooping)
{
	frameCount = newFrameCount;
	frameDuration = newFrameDuration;
	isLooping = newIsLooping;
	frameDelay = 0;
	frameIndex = 0;
	isDone = 0;
	isRunning = 1;
	parent->GetSprite()->SetFrame(0);
}

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
void Animation::Update(float dt)
{
	if (this)
	{
		isDone = false;
		if (isRunning)
		{
			frameDelay -= dt;
			if (frameDelay <= 0)
			{
				FrameAdvance();
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
bool Animation::IsDone(void)
{
	return isDone;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

//advance a sprite to its next frame
//Param:
//	animation = Pointer to the animation object
void Animation::FrameAdvance(void)
{
	frameIndex += 1;
	if (frameIndex >= frameCount)
	{
		if (isLooping)
		{
			frameIndex = 0;
		}
		else
		{
			frameIndex = frameCount - 1;
			isRunning = false;
		}
		isDone = true;
	}
	if (isRunning)
	{
		parent->GetSprite()->SetFrame(frameIndex);
		frameDelay += frameDuration;
	}
	else
	{
		frameDelay = 0;
	}
}