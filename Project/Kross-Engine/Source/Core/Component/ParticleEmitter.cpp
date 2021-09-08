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

		p_ParticleSystem = p_Particle->CreateParticleSystem(properties, p_PhysicsScene);
		/* Good blue */
		/* Vector3(13.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f) */

		SpawnParticle(p_Particle->CreateParticleDef(properties), properties->GetRadius() * 2.0f, properties->GetMaxCount());

	}

	ParticleEmitter::~ParticleEmitter()
	{
		p_PhysicsScene = nullptr;
		p_ParticleSystem = nullptr;
	}

	void ParticleEmitter::SpawnParticle(ParticleDef particleDef, float particleSize, int particleCount)
	{
		int max = glm::floor(glm::sqrt(particleCount));
		Vector2 initalPosition = m_GameObject->m_Transform->m_Position;

		for (int y = 0; y < max; y++)
		{
			for (int x = 0; x < max; x++)
			{
				particleDef.position = Getb2Vec2(initalPosition) + b2Vec2(-(((float)max * particleSize) / 2.0f) + particleSize * x, -(((float)max * particleSize) / 2.0f) + particleSize * y);
				p_ParticleSystem->CreateParticle(particleDef);
			}
		}
	}
	void ParticleEmitter::SpawnParticle(ParticleGroupDef particleDef)
	{
		p_ParticleSystem->CreateParticleGroup(particleDef);
	}
}