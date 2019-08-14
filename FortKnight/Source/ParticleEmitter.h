//------------------------------------------------------------------------------
//
// File Name:	ParticleEmitter.h
// Author(s):	Dieter Voegels
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

typedef struct ParticleEmitter* ParticleEmitterPtr;
typedef struct AEVec2 AEVec2;
typedef struct ParticleTemplate ParticleTemplate;
typedef struct ParticleTemplate* ParticleTemplatePtr;
typedef struct Object Object;
typedef struct Object* ObjectPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum Templates
{
	cTemplateDirt,
    cTemplateSpark
} Templates;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


//void ParticleEmitterSetPosition(Templates template, AEVec2 position);
void ParticleEmitterSetActive(ObjectPtr object, bool active);
void ParticleEmitterCreateEmitter(bool active, float lifetime, AEVec2 position, float directionMin, float directionMax, float particlePerSecond, Templates templateType, ObjectPtr parent);
void ParticleEmitterCreateBurstEmitter(AEVec2 position, float directionMin, float directionMax, int numberOfParticles, Templates templateType);
void ParticleEmitterUpdateEmitter(float dt);
void ParticleEmitterClear();
void ParticleEmitterCreateTemplate(Templates templateType, float lifetime);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

