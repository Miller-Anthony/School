//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		GAM150
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "AEMath.h"
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

//typedef struct AEVec2 AEVec2;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct Transform Transform;
typedef Transform * TransformPtr;

typedef enum TransformVec
{
    TransformX,
    TransformY,
    TransformScale,
    TransformPos
}TransformVec;

//------------------------------------------------------------------------------
// Public Variables:
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
TransformPtr TransformCreate(float x, float y);

//zeroes out a transform
TransformPtr TransformZero(TransformPtr transform);

//copies a transform's values to anothers
void TransformCopy(TransformPtr from, TransformPtr to);

// Free the memory associated with a transform object.
// (Also, set the transform pointer to NULL.)
// Params:
//	 transform = Pointer to the transform pointer.
void TransformFree(TransformPtr * transform);

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
AEVec2 * TransformGetTranslation(const TransformPtr transform);

// Get the rotation value of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float TransformGetRotation(const TransformPtr transform);

//Gets a specified value from a transform
float TransformGetValueFromVec(const TransformPtr transform, TransformVec vector, TransformVec value);

// Get the scale of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's scale structure,
//		else return a NULL pointer.
AEVec2 * TransformGetScale(const TransformPtr transform);

// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void TransformSetTranslation(TransformPtr transform, const AEVec2 * translation);

// Set the rotation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 rotation = The rotation value (in radians).
void TransformSetRotation(TransformPtr transform, float rotation);

// Set the scale of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a scale vector.
void TransformSetScale(TransformPtr transform, const AEVec2 * scale);

// Get the transform matrix, based upon translation, rotation and scale settings.
// (HINT: If the isDirty flag is true, then recalculate the transform matrix.)
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's matrix structure,
//		else return a NULL pointer.
AEMtx33 * TransformGetMatrix(const TransformPtr transform);
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

