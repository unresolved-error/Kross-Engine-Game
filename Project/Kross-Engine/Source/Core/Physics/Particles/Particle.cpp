#include "Particle.h"

#include "../../Core.h"

namespace Kross
{
	ParticleDef Particle::CreateParticle()
	{
		ParticleDef particleDef;
		particleDef.flags = m_Flags;

		particleDef.position.Set(m_Position.x, m_Position.y);
		particleDef.color.Set(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

		return particleDef;
	}

	ParticleGroupDef Particle::CreateParticleGroup()
	{
		ParticleGroupDef particleDef;
		particleDef.flags = m_Flags;
		particleDef.groupFlags = m_GroupFlags;

		particleDef.shape = m_Shape;

		particleDef.position.Set(m_Position.x, m_Position.y);
		particleDef.color.Set(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

		return particleDef;
	}
}