//------------------------------------------------------------------------------
//
// File Name:	Particle.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Particle.h"
#include "AEVec2.h"
#include "Sprite.h"
#include "AEEngine.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

#define GRAVITY 175.0f

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

ParticlePtr ParticleCreateParticle(AEVec2 position, AEVec2 scale, AEVec2 velocity, AEVec2 acceleration, ParticleTemplatePtr Template)
{
	ParticlePtr particle = calloc(1, sizeof(Particle));
	if (particle != NULL)
	{
		particle->active = true;
		particle->position = position;
		particle->scale = scale;
		particle->velocity = velocity;
		particle->acceleration = acceleration;
		particle->Template = Template;
		particle->lifetime = Template->totalLifetime;
		particle->next = NULL;

		return particle;
	}

	return NULL;
}

void ParticleUpdateParticle(ParticlePtr particle, float dt)
{
	if (particle->lifetime <= 0)
	{
		particle->active = false;
		return;
	}

	particle->position.x += particle->velocity.x * dt;
	particle->position.y += particle->velocity.y * dt;
	particle->velocity.y -= GRAVITY * dt;
	particle->velocity.x += particle->acceleration.x * dt;
	particle->velocity.y += particle->acceleration.y * dt;
	AEVec2 accel = { 0.0f, 0.0f};
	particle->acceleration = accel;
	particle->lifetime -= dt;
}

void ParticleDrawParticle(ParticlePtr particle)
{
	if (particle->Template->color == cDirt)
	{
		AEGfxSetBlendColor(147.0f, 126.0f, 80.0f, 0.0f);
	}
	else if (particle->Template->color == cSpark)
	{
		AEGfxSetBlendColor(255.0f, 255.0f, 125.0f, 0.0f);
	}

	TransformPtr transform = TransformCreate(particle->position.x, particle->position.y);
	TransformSetScale(transform, &particle->scale);
	TransformSetRotation(transform, 0.0f);
	SpriteDraw(particle->Template->sprite, transform);
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

