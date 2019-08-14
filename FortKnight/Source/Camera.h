//------------------------------------------------------------------------------
//
// File Name:	Camera.h
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

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

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

#pragma region PUBLIC_ENUMERATIONS

typedef enum CameraState
{
    cameraDefault,
    cameraStatic,
    cameraShaking,
    cameraSmoothShaking,
    cameraSmoothing,
    cameraStateMax
}CameraState;

#pragma endregion

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

#pragma region GETTERS

    //gets camera position
    void CameraGetPosition(float* outX, float* outY);

    //outs camera target position (position camera is smoothing to)
    //returns if camera is smoothing or not
    bool CameraGetTargetPosition(float* outX, float* outY);

    //returns if camera is shaking or not
    bool CameraGetShaking();

    //returns if camera is smoothing to a position or not
    bool CameraGetSmoothing();

    //outs camera bounds and returns if bounds have been set or not
    bool CameraGetPosBounds(float* minX, float* maxX, float* minY, float* maxY);

#pragma endregion

#pragma region SETTERS

    //sets the position of the camera and specify if you want current smoothing or shaking interrupted
    //or bounds ignored
    void CameraSetPosition(float x, float y, bool interruptSmoothing, bool interruptShaking, bool ignoreBounds);

    //shake camera horizontally and vertically by magnitude for time seconds
    //does not ignore camera bounds
    //CameraUpdate() must be called this frame to see changes
    void CameraShake(float magnitude, float seconds, bool interruptSmoothing);

    //smoothly shake camera horizontally and vertically by magnitude for time seconds
    //does not ignore camera bounds
    //CameraUpdate() must be called this frame to see changes
    void CameraSmoothShake(float shakeMagnitude, float smoothMagnitude, float seconds);

    //smooths camera to position by magnitude over time
    //CameraUpdate() must be called this frame to see changes
    void CameraSmoothToPosition(float x, float y, float magnitude, bool interruptShaking);

    //overrides camera smoothing so all other camera smoothing calls get ignored
    void CameraOverrideSmoothing(float targetX, float targetY, float smoothMagnitude, bool interruptShaking);

    //sets bounds of camera, CameraSetPosition() will be ignored if 
    //setting position out of bounds and CameraSmoothToPosition()
    //will smooth to edge of camera bounds if smoothing out of bounds
    void CameraSetPosBounds(float minX, float maxX, float minY, float maxY);

    //resets state of camera to default
    void CameraReset();

    //updates state of camera, should be called once per frame
    void CameraUpdate();

#pragma endregion

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

