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
//#include "Matrix2D.h"
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

// Dynamically allocate a new transform object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Failing to initialize the scale values to non-zero values will result in invisible sprites.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Transform::Transform(void) : Component(TransformType)
{
	scale.x = 1;
	scale.y = 1;
	isDirty = true;
}

// Dynamically allocate a clone of an existing transform.
// (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
ComponentPtr Transform::Clone(void) const
{
	TransformPtr holder = new Transform;
	if (holder)
	{
		*holder = *this;
	}
	return holder;
}

// Free the memory associated with a transform object.
// (Also, set the transform pointer to NULL.)
// Params:
//	 transform = Pointer to the transform pointer.
Transform::~Transform(void)
{
	
}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// [NOTE: Read the rotation value using StreamReadFloat.]
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Transform component.
//	 stream = Pointer to the data stream used for reading.
void Transform::Read(Stream stream)
{
	if (stream)
	{
		Vector2D holdVec; // vector to hold the translation and scale
		float holdRotation;

		//Read in and set the translation
		StreamReadVector2D(stream, &holdVec);
		SetTranslation(&holdVec);

		//Read in and set the rotation
		holdRotation = StreamReadFloat(stream);
		SetRotation(holdRotation);

		//read in and set the scale
		StreamReadVector2D(stream, &holdVec);
		SetScale(&holdVec);
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
Matrix2D * Transform::GetMatrix()
{
	if (isDirty)
	{
		//matrix holders
		Matrix2D scaleHolder;
		Matrix2D rotationHolder;
		Matrix2D translateHolder;
		Matrix2D middleHolder;
		
		//calculate the matrixes based off transforms stats
		Matrix2DScale(&scaleHolder, scale.x, scale.y);
		Matrix2DRotRad(&rotationHolder, rotation);
		Matrix2DTranslate(&translateHolder, translation.x, translation.y);

		//concatinate the matrixes
		Matrix2DConcat(&middleHolder, &rotationHolder, &scaleHolder);
		Matrix2DConcat(&matrix, &translateHolder, &middleHolder);

		isDirty = false;
	}
	return &matrix;
}

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
const Vector2D * Transform::GetTranslation(void)
{
	return &translation;
}

// Get the rotation value of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float Transform::GetRotation(void)
{
	return rotation;
}

// Get the scale of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's scale structure,
//		else return a NULL pointer.
const Vector2D * Transform::GetScale(void)
{
	return &scale;
}

// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void Transform::SetTranslation(const Vector2D * newTranslation)
{
	if (newTranslation)
	{
		translation = *newTranslation;
		isDirty = true;
	}
}

// Set the rotation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 rotation = The rotation value (in radians).
void Transform::SetRotation(float newRotation)
{
	rotation = newRotation;
	isDirty = true;
}

// Set the scale of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a scale vector.
void Transform::SetScale(const Vector2D * newScale)
{
	if (newScale)
	{
		scale = *newScale;
		isDirty = true;
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

