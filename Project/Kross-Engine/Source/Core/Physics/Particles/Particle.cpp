#include "Particle.h"

#include "../../Core.h"

namespace Kross
{
	void Particle::CreateParticle(ParticleSystem* particleSystem)
	{
		particleSystem->CreateParticle(CreateParticleDef());
	}

	ParticleDef Particle::CreateParticleDef()
	{
		/* Creates the particleDef and assigns all avaliable variables */
		ParticleDef particleDef;
		particleDef.flags = GetParticleFlag();

		particleDef.position.Set(GetPosition().x, GetPosition().y);
		particleDef.color.Set(GetColor().r, GetColor().g, GetColor().b, GetColor().a);

		return particleDef;
	}

	void Particle::CreateParticleGroup(ParticleSystem* particleSystem)
	{
		particleSystem->CreateParticleGroup(CreateParticleGroupDef());
	}

	ParticleGroupDef Particle::CreateParticleGroupDef()
	{
		/* Creates the particleGroupDef and assigns all avaliable variables */
		ParticleGroupDef particleDef;

		particleDef.flags = GetParticleFlag();
		particleDef.groupFlags = GetParticleGroupFlag();

		particleDef.strength = 0.0f;

		particleDef.shape = GetCircle();
		//particleDef.angle = GetAngle() + 0.01f;
		//particleDef.angularVelocity = GetAngularVelocity() + 0.05f;

		particleDef.position.Set(GetPosition().x, GetPosition().y);
		particleDef.color.Set(GetColor().r, GetColor().g, GetColor().b, GetColor().a);
		return particleDef;
	}
}