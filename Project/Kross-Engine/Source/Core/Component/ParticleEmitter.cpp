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
		p_PhysicsScene = GetPhysicsScene();

		/* set the world and the particle system */
		p_World = p_PhysicsScene->GetPhysicsWorld();

		/* Creates the particle system */
		OnCreateParticleSystem();

		SetRadius(0.025f);

		/* Creates all of the particles */
		if (m_ParticleType == ParticleType::Particle)
		{
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					p_Particle->SetCollisionFilter(p_Filter);

					p_Particle->SetPosition(Vector2(-5.0f + 0.005f * i, 3.0f - 0.005f * j));
					OnCreateParticle();
				}
			}
		}
		else if (m_ParticleType == ParticleType::ParticleGroup)
		{
			for (int i = 0; i < GetGroupCount(); i++)
			{
				p_Particle->SetCollisionFilter(p_Filter);

				p_Particle->SetPosition(Vector2(0.0f + 1.5f * i, 1.5f));
				OnCreateParticleGroup();
			}
		}

		/* Sets the shader */
		p_DebugShader = ResourceManager::GetResource<Shader>("LineShader");

		/* Initialise the line renderer */
		p_Lines->Initialise();

		/* Good blue */
		/* Vector3(13.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f) */

	}

	void ParticleEmitter::OnRender()
	{
		b2ParticleColor* particleColor = p_ParticleSystem->GetColorBuffer();
		b2Vec2* particlePositions = p_ParticleSystem->GetPositionBuffer();
		for (int i = 0; i < p_ParticleSystem->GetParticleCount(); i++)
		{
			p_Lines->SetColour({ particleColor[i].r, particleColor[i].g, particleColor[i].b });
			p_Lines->DrawCross({ particlePositions[i].x, particlePositions[i].y }, p_ParticleSystem->GetRadius());
		}
		
		p_DebugShader->Attach();
		p_Lines->UpdateFrame();
	}

	ParticleEmitter::~ParticleEmitter()
	{
		delete p_Lines;
		delete p_Filter;
	}

	void ParticleEmitter::OnCreateParticleSystem()
	{
		ParticleSystemDef particleSystemDef;
		p_ParticleSystem = p_PhysicsScene->GetParticleSystem();
	}

	void ParticleEmitter::OnCreateParticle()
	{
		if (!p_World)
		{
			p_PhysicsScene = GetPhysicsScene();
			p_PhysicsScene->GetPhysicsWorld();
			OnCreateParticleSystem();
			GetParticleSystem()->CreateParticle(p_Particle->CreateParticleDef());
		}
		else
		{
			GetParticleSystem()->CreateParticle(p_Particle->CreateParticleDef());
		}
	}

	void ParticleEmitter::OnCreateParticleGroup()
	{
		if (!p_World)
		{
			p_PhysicsScene = GetPhysicsScene();
			p_PhysicsScene->GetPhysicsWorld();
			OnCreateParticleSystem();
			GetParticleSystem()->CreateParticleGroup(p_Particle->CreateParticleGroupDef());
		}
		else
		{
			GetParticleSystem()->CreateParticleGroup(p_Particle->CreateParticleGroupDef());
		}
	}

}