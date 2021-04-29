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
		/* set the world and the particle system */
		p_World = p_PhysicsScene->GetPhysicsWorld();
		p_ParticleSystem = p_PhysicsScene->GetParticleSystem();

		/* Creates the particle system */
		OnCreateParticleSystem();

		/* Creates all of the particles */
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				p_Particle->SetPosition(Vector2(-7.9f + 0.03f * i, 3.0f - 0.02f * j));
				OnCreateParticle();
			}
		}

		/* Sets the shader */
		p_DebugShader = ResourceManager::GetResource<Shader>("LineShader");

		/* Initialise the line renderer */
		p_Lines->Initialise();

		
		SetRadius(0.1f);

		b2ParticleColor* particleColor = p_ParticleSystem->GetColorBuffer();
		p_Lines->SetColour({ particleColor[0].r, particleColor[0].g, particleColor[0].b });
		Component::OnStart();
	}

	void ParticleEmitter::OnUpdate()
	{
		Component::OnUpdate();
	}

	void ParticleEmitter::OnRender()
	{
		b2Vec2* particlePositions = p_ParticleSystem->GetPositionBuffer();
		for (int i = 0; i < p_ParticleSystem->GetParticleCount(); i++)
		{
			p_Lines->DrawCircle({ particlePositions[i].x, particlePositions[i].y }, p_ParticleSystem->GetRadius(), 8);
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
		p_ParticleSystem = p_World->CreateParticleSystem(&m_ParticleSystemDef);
	}

	void ParticleEmitter::OnCreateParticle()
	{
		p_ParticleSystem->CreateParticle(p_Particle->CreateParticle());
	}

}