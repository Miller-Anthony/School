//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Brayan Lopez
// Project:		KnightMare
// Course:		CS230S19
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Transform
{
    // The translation (or world position) of a game object.
    AEVec2	translation;

    // The rotation (or orientation) of a game object.
    float	rotation;

    // The scale (or size) of a game object.
    // (Hint: this should be initialized to (1, 1).)
    AEVec2	scale;

    // The transformation matrix resulting from concatenating the 
    //	 matrix = Translation*Rotation*Scale matrices.
    AEMtx33 matrix;

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
// Params:
//	 x = Initial world position on the x-axis.
//	 y = Initial world position on the y-axis.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
TransformPtr TransformCreate(float x, float y)
{
	TransformPtr newTform = (TransformPtr)calloc(1, sizeof(Transform));
	if(newTform)
	{
		newTform->scale.x = 1.0f;
		newTform->scale.y = 1.0f;
		newTform->translation.x = x;
		newTform->translation.y = y;
    newTform->isDirty = true;
	}
	return newTform;
}

//zeroes out a transform and returns it
TransformPtr TransformZero(TransformPtr transform)
{
    transform->isDirty = false;
    AEMtx33BuildFullTransform(&transform->matrix, 0, 0, 0, 1, 1);
    transform->rotation = 0;
    AEVec2Zero(&transform->translation);
    return transform;
}

//copies a transform's values to anothers
void TransformCopy(TransformPtr from, TransformPtr to)
{
    if(from && to)
        *to = *from;
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

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
AEVec2 * TransformGetTranslation(const TransformPtr transform)
{
	if (transform)
	{
		return &transform->translation;
	}
	else
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
		return transform->rotation;
	else
		return 0.0f;
}

//Gets a specified value from a transform
float TransformGetValueFromVec(const TransformPtr transform, TransformVec vector, TransformVec value)
{
    if (transform)
    {
        switch (vector)
        {
        case TransformScale:
            switch (value)
            {
            case TransformX:
                return transform->scale.x;
            case TransformY:
                return transform->scale.y;
            }
            break;
        case TransformPos:
            switch (value)
            {
            case TransformX:
                return transform->translation.x;
            case TransformY:
                return transform->translation.y;
            }
            break;
        }
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
AEVec2 * TransformGetScale(const TransformPtr transform)
{
	if (transform)
		return &transform->scale;
	else
		return NULL;
}

// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void TransformSetTranslation(TransformPtr transform, const AEVec2 * translation)
{
	if (transform)
	{
		transform->translation.x = translation->x;
		transform->translation.y = translation->y;
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
void TransformSetScale(TransformPtr transform, const AEVec2 * scale)
{
	if (transform)
	{
		transform->scale.x = scale->x;
		transform->scale.y = scale->y;
    transform->isDirty = true;
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
AEMtx33 * TransformGetMatrix(const TransformPtr transform)
{
    if (transform)
    {
        if (transform->isDirty)
        {
            AEMtx33 newScale;
            AEMtx33 newRot;
            AEMtx33 newTran;

            AEMtx33Scale(&newScale, transform->scale.x, transform->scale.y);
            AEMtx33Rot(&newRot, transform->rotation);
            AEMtx33Trans(&newTran, transform->translation.x, transform->translation.y);

            AEMtx33Concat(&transform->matrix, &newRot, &newScale);
            AEMtx33Concat(&transform->matrix, &newTran, &transform->matrix);

            transform->isDirty = false;
        }
        return &transform->matrix;
    }

    return NULL;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

