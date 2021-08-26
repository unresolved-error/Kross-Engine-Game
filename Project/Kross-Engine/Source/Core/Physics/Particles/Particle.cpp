/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Chris Deitch
 */


#include "Particle.h"

namespace Kross
{
	ParticleSystem* Particle::CreateParticleSystem(ParticleProperties* properties, PhysicsScene* physicsScene)
	{
		ParticleSystem* pSystem = physicsScene->GetPhysicsWorld()->CreateParticleSystem(properties->GetParticleSystemDef());
		physicsScene->AddParticleSystem(pSystem);
		return pSystem;
	}
	
	ParticleDef Particle::CreateParticleDef(ParticleProperties* properties)
	{
		ParticleDef particleDef;
	
		particleDef.flags = properties->GetParticleFlags();
	
		particleDef.position = Getb2Vec2(properties->m_GameObject->m_Transform->m_Position);
		particleDef.color = properties->GetColor();
	
		particleDef.velocity = properties->GetLinearVelocity();
	
		particleDef.lifetime = properties->GetLifetime();
		particleDef.userData = properties->GetUserData();
		particleDef.group = properties->GetGroup();
	
		return particleDef;
	}
	
	ParticleGroupDef Particle::CreateParticleGroupDef(ParticleProperties* properties)
	{
		return *properties->GetParticleGroupDef();
	}

}