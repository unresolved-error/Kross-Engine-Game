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


		p_PhysicsScene = GetPhysicsScene();
		
		/* Creates the particle system */
		OnCreateParticleSystem();
		
		/* Good blue */
		/* Vector3(13.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f) */

	}

	ParticleEmitter::~ParticleEmitter()
	{
		delete p_Filter;
	}

	void ParticleEmitter::AttachParticle(Particle* particle)
	{
		m_ParticleList.push_back(particle);
		p_Particle = particle;
		p_Particle->SetParticleID(m_ParticleList.size());
	}

	List<Particle*> ParticleEmitter::GetParticles()
	{
		return m_ParticleList;
	}

	void ParticleEmitter::OnCreateParticleSystem()
	{
		ParticleSystemDef particleSystemDef;
		p_ParticleSystem = p_PhysicsScene->GetPhysicsWorld()->CreateParticleSystem(&particleSystemDef);
		p_PhysicsScene->AddParticleSystem(p_ParticleSystem);
		m_ParticleSystemList.push_back(p_ParticleSystem);
	}

	void ParticleEmitter::OnCreateParticle(ParticleSystem* particleSystem, Particle* particle)
	{
		ParticleDef particleDef = particle->CreateParticleDef();
		particleSystem->CreateParticle(particleDef);
	}

	void ParticleEmitter::OnCreateParticleGroup(ParticleSystem* particleSystem, Particle* particle)
	{
		ParticleGroupDef groupDef = particle->CreateParticleGroupDef();
		particleSystem->CreateParticleGroup(groupDef);
	}

	void ParticleEmitter::SpawnParticles()
	{
		p_PhysicsScene = GetPhysicsScene();
		
		/* Gets the particle system */
		m_ParticleSystemList = p_PhysicsScene->GetParticleSystem();
		


		/* Goes through all of the particle systems */
		for (int x = 0; x < m_ParticleSystemList.size(); x++)
		{
			p_ParticleSystem = m_ParticleSystemList[x];
			SetRadius(0.025f);
			
			/* Goes through all particles within the system */
			for (int y = 0; y < m_ParticleList.size(); y++)
			{
				m_ParticleList[y]->SetCollisionFilter(p_Filter);

				if (!m_ParticleList[y]->GetParticleGroupType())
				{
					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 20; j++)
						{
							m_ParticleList[y]->SetPosition(Vector2(GetPosition().x + 0.05f * i,
								GetPosition().y - 0.045f * j));

							OnCreateParticle(p_ParticleSystem, m_ParticleList[y]);
						}
					}
				}
				else if (m_ParticleList[y]->GetParticleGroupType())
				{
					for (int i = 0; i < GetGroupCount(); i++)
					{
						m_ParticleList[y]->SetPosition(Vector2(GetPosition().x + 0.005f * i, GetPosition().y));

						OnCreateParticleGroup(p_ParticleSystem, m_ParticleList[y]);
					}
				}
			}
		}
	}

	void ParticleEmitter::SpawnParticleGrid(float width, float height)
	{
		p_PhysicsScene = GetPhysicsScene();

		/* Gets the particle system */
		m_ParticleSystemList = p_PhysicsScene->GetParticleSystem();


		/* Goes through all of the particle systems */
		for (int x = 0; x < m_ParticleSystemList.size(); x++)
		{
			p_ParticleSystem = m_ParticleSystemList[x];
			SetRadius(0.025f);


			/* Goes through all particles within the system */
			for (int y = 0; y < m_ParticleList.size(); y++)
			{
				m_ParticleList[y]->SetCollisionFilter(p_Filter);

				if (!m_ParticleList[y]->GetParticleGroupType())
				{
					for (int i = 0; i < width; i++)
					{
						for (int j = 0; j < height; j++)
						{
							m_ParticleList[y]->SetPosition(Vector2(GetPosition().x + 0.005f * i,
								GetPosition().y - 0.0045f * j));

							OnCreateParticle(p_ParticleSystem, m_ParticleList[y]);
						}
					}
				}
			}
		}
	}

}