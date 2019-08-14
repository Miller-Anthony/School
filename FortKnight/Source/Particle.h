//------------------------------------------------------------------------------
//
// File Name:	Particle.h
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

#include "AEVec2.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Particle Particle;
typedef struct Particle* ParticlePtr;
typedef struct ParticleTemplate ParticleTemplate;
typedef struct ParticleTemplate* ParticleTemplatePtr;
typedef struct Sprite* SpritePtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum
{
	cDirt,
	cSpark,
}Color;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct Particle
{
	bool active;
	AEVec2 position;
	AEVec2 scale;
	AEVec2 velocity;
	AEVec2 acceleration;
	float lifetime;
	ParticleTemplatePtr Template;

	ParticlePtr next;
} Particle;

typedef struct ParticleTemplate
{
	SpritePtr sprite;
	Color color;
	float totalLifetime;
} ParticleTemplate;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

ParticlePtr ParticleCreateParticle(AEVec2 position, AEVec2 scale, AEVec2 velocity, AEVec2 acceleration, ParticleTemplatePtr Template);
void ParticleUpdateParticle(ParticlePtr particle, float dt);
void ParticleDrawParticle(ParticlePtr particle);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

