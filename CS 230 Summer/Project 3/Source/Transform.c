//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Anthony Miller
// Project:		MyGame
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct Transform
{
	// The translation (or world position) of a game object.
	Vector2D	translation;

	// The rotation (or orientation) of a game object (in radians).
	float	rotation;

	// The scale (or size) of a game object.
	// (Hint: This should be initialized to (1, 1).)
	Vector2D	scale;

	// The transformation matrix resulting from concatenating the 
	//	 matrix = Translation*Rotation*Scale matrices.
	Matrix2D	matrix;

	// True if the transformation matrix needs to be recalculated.
	// (Hint: this should be initialized to true.)
	bool	isDirty;

} Transform;

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

// Dynamically allocate a new transform object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Failing to initialize the scale values to non-zero values will result in invisible sprites.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
TransformPtr TransformCreate(void)
{
	TransformPtr holder = calloc(1, sizeof(Transform));

	if (!holder)
	{
		return NULL;
	}

	holder->scale.x = 1;
	holder->scale.y = 1;
	holder->isDirty = true;

	return holder;

}

// Free the memory associated with a transform object.
// (Also, set the transform pointer to NULL.)
// Params:
//	 transform = Pointer to the transform pointer.
void TransformFree(TransformPtr * transform)
{
	if (transform)
	{
		free(*transform);
		*transform = NULL;
	}
}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// [NOTE: Read the rotation value using StreamReadFloat.]
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Transform component.
//	 stream = Pointer to the data stream used for reading.
void TransformRead(TransformPtr transform, Stream stream)
{
	if (transform && stream)
	{
		Vector2D holdVec; // vector to hold the translation and scale
		float holdRotation;

		//Read in and set the translation
		StreamReadVector2D(stream, &holdVec);
		TransformSetTranslation(transform, &holdVec);

		//Read in and set the rotation
		holdRotation = StreamReadFloat(stream);
		TransformSetRotation(transform, holdRotation);

		//read in and set the scale
		StreamReadVector2D(stream, &holdVec);
		TransformSetScale(transform, &holdVec);
	}
}

// Get the transform matrix, based upon translation, rotation and scale settings.
// (HINT: If the isDirty flag is true, then recalculate the transform matrix.)
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's matrix structure,
//		else return a NULL pointer.
Matrix2D * TransformGetMatrix(const TransformPtr transform)
{
	if (transform)
	{
		if (transform->isDirty)
		{
			//matrix holders
			Matrix2D scaleHolder;
			Matrix2D rotationHolder;
			Matrix2D translateHolder;
			Matrix2D middleHolder;

			//calculate the matrixes based off transforms stats
			Matrix2DScale(&scaleHolder, transform->scale.x, transform->scale.y);
			Matrix2DRotRad(&rotationHolder, transform->rotation);
			Matrix2DTranslate(&translateHolder, transform->translation.x, transform->translation.y);

			//concatinate the matrixes
			Matrix2DConcat(&middleHolder, &rotationHolder, &scaleHolder);
			Matrix2DConcat(&transform->matrix, &translateHolder, &middleHolder);

			transform->isDirty = false;
		}
		return &(transform->matrix);
	}
	return NULL;
}

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
const Vector2D * TransformGetTranslation(const TransformPtr transform)
{
	if (transform)
	{
		return &(transform->translation);
	}
	return NULL;
}

// Get the rotation value of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float TransformGetRotation(const TransformPtr transform)
{
	if (transform)
	{
		return transform->rotation;
	}
	return 0.0f;
}

// Get the scale of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's scale structure,
//		else return a NULL pointer.
const Vector2D * TransformGetScale(const TransformPtr transform)
{
	if (transform)
	{
		return &(transform->scale);
	}
	return NULL;
}

// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void TransformSetTranslation(TransformPtr transform, const Vector2D * translation)
{
	if (transform && translation)
	{
		transform->translation = *translation;
		transform->isDirty = true;
	}
}

// Set the rotation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 rotation = The rotation value (in radians).
void TransformSetRotation(TransformPtr transform, float rotation)
{
	if (transform)
	{
		transform->rotation = rotation;
		transform->isDirty = true;
	}
}

// Set the scale of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a scale vector.
void TransformSetScale(TransformPtr transform, const Vector2D * scale)
{
	if (transform && scale)
	{
		transform->scale = *scale;
		transform->isDirty = true;
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

