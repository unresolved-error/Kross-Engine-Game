/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"
#include "../Box2D/Box2D/Box2D.h"
#include "../Filters/ParticleType.h"
#include "../../Component/ParticleProperties.h"

namespace Kross
{

	class KROSS_API Particle
	{
	protected:
		PhysicsScene* p_PhysicsScene;
		ParticleSystem* p_ParticleSystem;

	public:
		/* The group bool is to determine where values need to be assigned */
		Particle() :
			p_PhysicsScene		(nullptr),
			p_ParticleSystem	(nullptr)
		{};
		~Particle() {};

		void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; }
		PhysicsScene* GetPhysicsScene() { return p_PhysicsScene; }

		/* Creates particle system */
		void CreateParticleSystem(ParticleProperties* properties);

		/* Creates the particle def */
		ParticleDef CreateParticleDef(ParticleProperties* properties);

		/* Creates the particle group def */
		ParticleGroupDef CreateParticleGroupDef(ParticleProperties* properties);
	};
}
