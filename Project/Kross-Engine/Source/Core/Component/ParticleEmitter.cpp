/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *		- Deklyn Palmer.
 */

#include "ParticleEmitter.h"

namespace Kross
{
	void ParticleEmitter::OnStart()
	{
		ParticleProperties* properties = GetComponent<ParticleProperties>();

		GetPhysicsScene();

		p_ParticleSystem = p_Particle->CreateParticleSystem(properties, p_PhysicsScene);
		/* Good blue */
		/* Vector3(13.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f) */

		SpawnParticle(p_Particle->CreateParticleDef(properties));

	}

	ParticleEmitter::~ParticleEmitter()
	{
		p_PhysicsScene = nullptr;
		p_ParticleSystem = nullptr;
	}

	void ParticleEmitter::SpawnParticle(ParticleDef particleDef)
	{
		for (int i = 0; i < 75; i++)
		{
			for (int j = 0; j < 75; j++)
			{
				particleDef.position = b2Vec2(5.0f + 0.05f * i, -2.0f + 0.05f * j);
				p_ParticleSystem->CreateParticle(particleDef);
			}
		}
	}
	void ParticleEmitter::SpawnParticle(ParticleGroupDef particleDef)
	{
		p_ParticleSystem->CreateParticleGroup(particleDef);
	}
}