//------------------------------------------------------------------------------
//
// File Name:	Camera.c
// Author(s):	Brayan Lopez
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Camera.h"
#include "AEEngine.h"
#include "DT.h"
#include "Utils.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

#pragma region PUBLIC_VARIABLES


#pragma endregion

#pragma region PRIVATE_VARIABLES

static CameraState state = cameraDefault;
static float xBounds[2] = { 0 };     //min, max
static float yBounds[2] = { 0 };     //min, max
static float position[2] = { 0 };    //x, y
static float target[2] = { 0 };      //target x, target y
static float smoothAmount = 0.0f;    //smoothing magnitude (should be between 0 and 1)
static float shakeAmount = 0.0f;     //shaking magnitude
static float shakeDuration = 0.0f;   //shake duration
static bool boundsSet = false;       //if bounds were set
static bool smoothOverriden = false; //camera smoothing calls are ignored unless called by CameraOverrideSmoothing()

#pragma endregion

#pragma region PRIVATE_FUNCTION_DECLARATIONS

static void Shake();
static void Smooth();
static void SmoothShake();

#pragma endregion

#pragma region PUBLIC_FUNCTION_DEFINITIONS

#pragma region GETTERS

void CameraGetPosition(float* outX, float* outY)
{
    AEGfxGetCamPosition(outX, outY);
}

//outs camera target position (position camera is smoothing to)
//returns if camera is smoothing or not
bool CameraGetTargetPosition(float* outX, float* outY)
{
    if (outX)
        *outX = target[0];
    if(outY)
        *outY = target[1];

    return CameraGetSmoothing();
}

//returns if camera is shaking or not
bool CameraGetShaking()
{
    switch (state)
    {
    case cameraShaking:
        //fallthrough
    case cameraSmoothShaking:
        return true;
    default:
        return false;
    }
}

//returns if camera is smoothing to a position or not
bool CameraGetSmoothing()
{
    switch (state)
    {
    case cameraSmoothing:
        //fallthrough
    case cameraSmoothShaking:
        return true;
    default:
        return false;
    }
}

//outs camera bounds and returns if bounds have been set or not
bool CameraGetPosBounds(float* minX, float* maxX, float* minY, float* maxY)
{
    if (minX)
        *minX = xBounds[0];
    if (maxX)
        *maxX = xBounds[1];
    if (minY)
        *minY = yBounds[0];
    if (maxY)
        *maxY = yBounds[1];
    return boundsSet;
}

#pragma endregion

#pragma region SETTERS

//sets the position of the camera and specify if you want current smoothing or shaking interrupted
void CameraSetPosition(float x, float y, bool interruptSmoothing, bool interruptShaking, bool ignoreBounds)
{
    if(ignoreBounds || !boundsSet)
        AEGfxSetCamPosition(x, y);
    else
        AEGfxSetCamPosition(AEClamp(x, xBounds[0], xBounds[1]), AEClamp(y, yBounds[0], yBounds[1]));
    if (interruptShaking && interruptSmoothing)
    {
        state = cameraStatic;
        return;
    }
    if (interruptShaking)
    {
        switch (state)
        {
        case cameraShaking:
            state = cameraStatic;
            return;
        case cameraSmoothShaking:
            state = cameraSmoothing;
            return;
        default:
            return;
        }
    }
    if (interruptSmoothing)
    {
        switch (state)
        {
        case cameraSmoothing:
            state = cameraStatic;
            return;
        case cameraSmoothShaking:
            state = cameraShaking;
            return;
        default:
            return;
        }
    }
}

//shake camera horizontally and vertically by magnitude for time seconds
//does not ignore camera bounds
void CameraShake(float magnitude, float seconds, bool interruptSmoothing)
{
    //if (shakeForcedOff)
    //    return;
    shakeAmount = magnitude;
    shakeDuration = seconds;
    if (!interruptSmoothing)
    {
        switch (state)
        {
        case cameraSmoothing:
            //fallthrough
        case cameraSmoothShaking:
            state = cameraSmoothShaking;
            break;
        default:
            state = cameraShaking;
            break;
        }
    }
    else
        state = cameraShaking;

}

//smoothly shake camera horizontally and vertically by magnitude for time seconds
//does not ignore camera bounds
//CameraUpdate() must be called this frame to see changes
void CameraSmoothShake(float shakeMagnitude, float smoothMagnitude, float seconds)
{
    shakeAmount = shakeMagnitude;
    shakeDuration = seconds;

    if (!smoothOverriden)
    {
        smoothAmount = smoothMagnitude;
        state = cameraSmoothShaking;
    }

}

//smooths camera to position by magnitude over time
void CameraSmoothToPosition(float x, float y, float magnitude, bool interruptShaking)
{
    if (smoothOverriden)
        return;
    target[0] = x;
    target[1] = y;
    smoothAmount = magnitude;
    if (!interruptShaking)
    {
        switch (state)
        {
        case cameraShaking:
            //fallthrough
        case cameraSmoothShaking:
            state = cameraSmoothShaking;
            break;
        default:
            state = cameraSmoothing;
            break;
        }
    }
    else
        state = cameraSmoothing;
}

//overrides camera smoothing so all other camera smoothing calls get ignored
void CameraOverrideSmoothing(float targetX, float targetY, float smoothMagnitude, bool interruptShaking)
{
    target[0] = targetX;
    target[1] = targetY;
    smoothAmount = smoothMagnitude;
    smoothOverriden = true;
    if (interruptShaking)
    {
        switch (state)
        {
        case cameraShaking:
            state = cameraStatic;
            return;
        //case cameraSmoothShaking:
        //    state = cameraSmoothing;
        //    return;
        default:
            state = cameraSmoothing;
            return;
        }
    }
    else
    {
        switch (state)
        {
        case cameraShaking:
            //fallthrough
        case cameraSmoothShaking:
            state = cameraSmoothShaking;
            return;
        default:
            state = cameraSmoothing;
            return;
        }
    }
}


//sets bounds of camera, CameraSetPosition() will be ignored if 
//setting position out of bounds and CameraSmoothToPosition()
//will smooth to edge of camera bounds if smoothing out of bounds
void CameraSetPosBounds(float minX, float maxX, float minY, float maxY)
{
    boundsSet = true;
    xBounds[0] = minX;
    xBounds[1] = maxX;
    yBounds[0] = minY;
    yBounds[1] = maxY;
}

//resets state of camera to default
void CameraReset()
{
    state = cameraDefault;
    boundsSet = false;
    smoothOverriden = false;
    target[0] = 0.0f;
    target[1] = 0.0f;
    AEGfxSetCamPosition(0.0f, 0.0f);
    smoothAmount = 0.0f; 
    shakeAmount = 0.0f;  
    shakeDuration = 0.0f;
}

#pragma endregion

//updates state of camera, should be called once per frame
void CameraUpdate()
{
    AEGfxGetCamPosition(&position[0], &position[1]);
    if (boundsSet)
    {
        target[0] = AEClamp(target[0], xBounds[0], xBounds[1]);
        target[1] = AEClamp(target[1], yBounds[0], yBounds[1]);
    }
    switch (state)
    {
    case cameraSmoothing:
        Smooth();
        break;
    case cameraShaking:
        Shake();
        shakeDuration -= dt;
        break;
    case cameraSmoothShaking:
        SmoothShake();
        shakeDuration -= dt;
        break;
    default:
        break;
    }
}

#pragma endregion

#pragma region PRIVATE_FUNCTION_DEFINITIONS

//perform shake
static void Shake()
{
    if (shakeDuration <= 0.0f)
    {
        shakeDuration = 0.0f;
        switch (state)
        {
        case cameraShaking:
            state = cameraStatic;
            break;
        case cameraSmoothShaking:
            state = cameraSmoothing;
            break;
        default:
            break;
        }
        
    }
    if (boundsSet)
    {
        bool canShakeRight = position[0] + shakeAmount < xBounds[1];
        bool canShakeLeft = position[0] - shakeAmount > xBounds[0];
        bool canShakeUp = position[1] + shakeAmount < yBounds[1];
        bool canShakeDown = position[1] - shakeAmount > yBounds[0];
        float xMin = xBounds[0];
        float xMax = xBounds[1];
        float yMin = yBounds[0];
        float yMax = yBounds[1];
        if (canShakeRight)
            xMax = position[0] + shakeAmount;
        if (canShakeLeft)
            xMin = position[0] - shakeAmount;
        if (canShakeUp)
            yMax = position[1] + shakeAmount;
        if (canShakeDown)
            yMin = position[1] - shakeAmount;

        AEGfxSetCamPosition(RandomRangeFloat(xMin, xMax), RandomRangeFloat(yMin, yMax));
    }
    else
        AEGfxSetCamPosition(RandomRangeFloat(position[0] - shakeAmount, position[0] + shakeAmount), RandomRangeFloat(position[1] - shakeAmount, position[1] + shakeAmount));

}

//perform smoothing
static void Smooth()
{
    float epsilon = 1.0f;

    if (fabsf(position[0] - target[0]) <= epsilon && fabsf(position[1] - target[1]) <= epsilon)
    {
        switch (state)
        {
        case cameraSmoothing:
            state = cameraStatic;
            break;
        case cameraSmoothShaking:
            state = cameraShaking;
            break;
        default:
            break;
        }
        return;
    }

    AEVec2 dirVec;
    dirVec.x = target[0] - position[0];
    dirVec.y = target[1] - position[1];

    AEGfxSetCamPosition(position[0] + (dirVec.x * smoothAmount*dt), position[1] + (dirVec.y * smoothAmount*dt));
}

//perform smooth shaking (or smoothing and shaking)
static void SmoothShake()
{
    Smooth();
    AEGfxGetCamPosition(&position[0], &position[1]);
    Shake();
}

#pragma endregion