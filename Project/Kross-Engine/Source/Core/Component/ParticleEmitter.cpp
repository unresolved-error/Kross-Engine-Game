/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "ParticleEmitter.h"

namespace Kross
{
	void ParticleEmitter::OnStart()
	{
		p_PhysicsScene = GetPhysicsScene();

		/* set the world and the particle system */
		p_World = p_PhysicsScene->GetPhysicsWorld();
		//p_ParticleSystem = p_PhysicsScene->GetParticleSystem();

		/* Creates the particle system */
		OnCreateParticleSystem();

		p_ParticleSystem;

		/* Creates all of the particles */
		for (int i = 0; i < m_ParticleCount; i++)
		{
			for (int j = 0; j < m_ParticleCount; j++)
			{
				p_Particle->SetPosition(Vector2(-7.9f + 0.01f * i, 3.0f - 0.002f + 0.01f * j));
				OnCreateParticle();
			}
		}

		/* Sets the shader */
		p_DebugShader = ResourceManager::GetResource<Shader>("LineShader");

		/* Initialise the line renderer */
		p_Lines->Initialise();

		SetRadius(0.025f);
		p_Lines->SetColour(Vector3(13.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f));

		Component::OnStart();
	}

	void ParticleEmitter::OnUpdate()
	{
		Component::OnUpdate();
	}

	void ParticleEmitter::OnRender()
	{
		//b2ParticleColor* particleColor = p_ParticleSystem->GetColorBuffer();
		b2Vec2* particlePositions = p_ParticleSystem->GetPositionBuffer();
		for (int i = 0; i < p_ParticleSystem->GetParticleCount(); i++)
		{
			//p_Lines->SetColour({ particleColor[i].r, particleColor[i].g, particleColor[i].b });
			p_Lines->DrawCross({ particlePositions[i].x, particlePositions[i].y }, p_ParticleSystem->GetRadius());
		}
		
		p_DebugShader->Attach();
		p_Lines->UpdateFrame();

		Component::OnRender();
	}

	ParticleEmitter::~ParticleEmitter()
	{
		delete p_Particle;
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
		GetParticleSystem()->CreateParticle(p_Particle->CreateParticleDef());
	}

	void ParticleEmitter::OnCreateParticleGroup()
	{
		if (!p_World)
		{
			p_PhysicsScene = GetPhysicsScene();
			p_PhysicsScene->GetPhysicsWorld();
			OnCreateParticleSystem();
			p_ParticleSystem->CreateParticleGroup(p_Particle->CreateParticleGroupDef());
		}
		p_ParticleSystem->CreateParticleGroup(p_Particle->CreateParticleGroupDef());
	}

}