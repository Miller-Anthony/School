//------------------------------------------------------------------------------
//
// File Name:	ParticleManager.c
// Author(s):	Dieter Voegels
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ParticleManager.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "AEEngine.h"

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

static ParticlePtr head = NULL;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void linkedListAdd(ParticlePtr newParticle);
static void linkedListRemove(ParticlePtr nparticle);
static void linkedListClear();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ParticleManagerUpdateParticles(float dt)
{
	ParticlePtr current = head;

	while (current != NULL)
	{
		if (current->active == true)
		{
			ParticleUpdateParticle(current, dt);
			current = current->next;
		}
		else
		{
			ParticlePtr temp = current;
			current = current->next;
			linkedListRemove(temp);
		}
	}
}

void ParticleManagerClear()
{
	linkedListClear();
}

void ParticleManagerAddParticle(ParticlePtr newParticle)
{
	linkedListAdd(newParticle);
}

void ParticleManagerDrawParticles(Templates Template)
{
	ParticlePtr current = head;

	while (current != NULL)
	{
		if (current->Template->color == Template)
		{
			ParticleDrawParticle(current);
		}
		else if (current->Template->color == Template)
		{
			ParticleDrawParticle(current);
		}

		current = current->next;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void linkedListAdd(ParticlePtr newParticle)
{
	if (head == NULL)
	{
		head = newParticle;
	}
	else
	{
		newParticle->next = head;
		head = newParticle;
	}
}

static void linkedListRemove(ParticlePtr particle)
{
	ParticlePtr previous = head;
	ParticlePtr current = head;

	if (particle != NULL)
	{
		if (particle == head)
		{
			ParticlePtr toDelete = head;
			head = head->next;
			free(toDelete);
		}
		else
		{
			while (current != NULL)
			{
				if (current == particle)
				{
					previous->next = current->next;
					free(current);
					current = NULL;
					return;
				}

				previous = current;
				current = current->next;
			}
		}
	}
}

static void linkedListClear()
{
	ParticlePtr previous = head;
	ParticlePtr current = head;

	while (current != NULL)
	{
		previous = current;
		current = current->next;
		free(previous);
	}

	free(current);
}