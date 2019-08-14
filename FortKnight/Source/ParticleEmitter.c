//------------------------------------------------------------------------------
//
// File Name:	ParticleEmitter.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "Sprite.h"
#include "Mesh.h"
#include "AEEngine.h"
#include "time.h"
#include "Utils.h"
#include "Objects.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ParticleEmitter
{
	ParticleTemplatePtr Template;
	ObjectPtr parent;
	float particlePerSecond;
	float lifetime;
	AEVec2 position;
	float directionMin;
	float directionMax;
	float timer;
	bool active;
} ParticleEmitter;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

const static int ParticleSpeedMinimum = 100;
const static int ParticleSpeedMaximum = 125;
static ParticleEmitterPtr emitters[100];
static ParticleTemplatePtr templates[10];

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ParticleEmitterCreateEmitter(bool active, float lifetime, AEVec2 position, float directionMin, float directionMax, float particlePerSecond, Templates templateType, ObjectPtr parent)
{
	ParticleEmitterPtr emitter = calloc(1, sizeof(ParticleEmitter));
	if (emitter != NULL)
	{
		emitter->lifetime = lifetime;
		emitter->active = active;
		emitter->particlePerSecond = particlePerSecond;
		emitter->directionMin = directionMin;
		emitter->position = position;
		emitter->directionMax = directionMax;
		emitter->Template = templates[templateType];
		emitter->timer = (float)(1.8 * ((.03 * emitter->particlePerSecond) / 1.8));
		emitter->parent = parent;

		for (int i = 0; i < 20; i++)
		{
			if (emitters[i] == NULL)
			{
				emitters[i] = emitter;
				break;
			}
		}
	}
}

void ParticleEmitterCreateBurstEmitter(AEVec2 position, float directionMin, float directionMax, int numberOfParticles, Templates templateType)
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		if (templateType == cTemplateSpark)
		{
			AEVec2 scale = { 30.0f, 30.0f };
			AEVec2 acceleration = { 0.0f, 0.0f };
			AEVec2 velocity;
			
			srand(RandomRange(0, 999999) * i);
			float random = RandomRangeFloat(directionMin, directionMax);
			AEVec2FromAngle(&velocity, random);
			float speed = 200.0f;
			AEVec2Scale(&velocity, &velocity, speed);

			ParticlePtr newParticle = ParticleCreateParticle(position, scale, velocity, acceleration, templates[cTemplateSpark]);
			ParticleManagerAddParticle(newParticle);
		}
	}
}

void ParticleEmitterCreateTemplate(Templates templateType, float lifetime)
{
	ParticleTemplatePtr Template = calloc(1, sizeof(ParticleTemplate));
	if (Template == NULL)
	{
		return;
	}
	
	AEGfxVertexList* pMesh = MeshCreateQuad(.5f, .5f, 1.0f, 1.0f, "Mesh1x1");
	AEGfxTexture* dirtPNG = AEGfxTextureLoad("./Assets/DirtParticle.png");
	AEGfxTexture* sparkPNG = AEGfxTextureLoad("./Assets/Spark.png");

	if (templateType == cTemplateDirt)
	{
		Template->color = cTemplateDirt;
		Template->sprite = SpriteCreate("Particle Dirt Sprite");
		SpriteSetMesh(Template->sprite, pMesh);
		SpriteSetSpriteSource(Template->sprite, SpriteSourceCreate(1, 1, dirtPNG));
		Template->totalLifetime = lifetime;
		templates[cTemplateDirt] = Template;
	}
	else if(templateType == cTemplateSpark)
	{
		Template->color = cTemplateSpark;
		Template->sprite = SpriteCreate("Particle Spark Sprite");
		SpriteSetMesh(Template->sprite, pMesh);
		SpriteSetSpriteSource(Template->sprite, SpriteSourceCreate(1, 1, sparkPNG));
		Template->totalLifetime = lifetime;
		templates[cTemplateSpark] = Template;
	}
}

void ParticleEmitterUpdateEmitter(float dt)
{
	for (int i = 0; i < 100; i++)
	{
		if (emitters[i] == NULL)
		{
			continue;
		}

		if (emitters[i]->lifetime > 0 && emitters[i]->active == true)
		{
			if (emitters[i]->parent != NULL)
			{
				emitters[i]->position.x = TransformGetTranslation(ObjectGetTransform(emitters[i]->parent))->x;
				emitters[i]->position.y = TransformGetTranslation(ObjectGetTransform(emitters[i]->parent))->y - 50;
			}
			emitters[i]->timer += dt; 
			if (emitters[i]->timer >= 1.8 * ((dt * emitters[i]->particlePerSecond) / 1.8))
			{
				emitters[i]->timer = 0;
				AEVec2 velocity;
				float random = RandomRangeFloat(emitters[i]->directionMin, emitters[i]->directionMax);
				AEVec2FromAngle(&velocity, random);
				/*Source: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rand*/
				srand((unsigned)time(NULL));
				float randPercent = (float)rand() / (float)(RAND_MAX + 1);
				float range = (float)(ParticleSpeedMaximum - ParticleSpeedMinimum);
				float randomSpeed = randPercent * range + ParticleSpeedMinimum;
				/*end source*/
				AEVec2Scale(&velocity, &velocity, randomSpeed);

				AEVec2 scale = { 30.0f, 30.0f};
				AEVec2 acceleration = { 0.0f, 0.0f};

				ParticlePtr newParticle = ParticleCreateParticle(emitters[i]->position, scale, velocity, acceleration, emitters[i]->Template);
				ParticleManagerAddParticle(newParticle);
			}

			emitters[i]->lifetime -= dt;
		}
		else
		{
			free(emitters[i]);
			emitters[i] = NULL;
		}
	}
}

void ParticleEmitterClear()
{
	for (int i = 0; i < 100; i++)
	{
		if (emitters[i] != NULL)
		{
			free(emitters[i]);
			emitters[i] = NULL;
		}
	}

	for (int i = 10; i < 10; i++)
	{
		if (templates[i] != NULL)
		{
			free(templates[i]);
			templates[i] = NULL;
		}
	}
}

void ParticleEmitterSetActive(ObjectPtr object, bool active)
{
	for (int i = 0; i < 100; i++)
	{
		if (emitters[i] == NULL)
		{
			continue;
		}

		if (emitters[i]->parent == object)
		{
			emitters[i]->active = active;
		}
	}
}

/*
void ParticleEmitterSetPosition(Templates template, AEVec2 position)
{
	for (int i = 0; i < 20; i++)
	{
		if (emitters[i] == NULL)
		{
			continue;
		}

		if (emitters[i]->Template == template)
		{
			emitters[i]->position.x = position.x;
			emitters[i]->position.y = position.y;
		}
	}
}
*/
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

