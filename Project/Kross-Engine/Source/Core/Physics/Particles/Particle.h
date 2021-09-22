/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../PhysicsScene.h"
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
		ParticleSystem* CreateParticleSystem(ParticleProperties* properties, PhysicsScene* physicsScene);

		void SetParticleSystem(ParticleSystem* particleSystem) { p_ParticleSystem = particleSystem; }
		ParticleSystem* GetParticleSystem() { return p_ParticleSystem; }
		
		/* Creates the particle def */
		ParticleDef CreateParticleDef(ParticleProperties* properties);
		
		/* Creates the particle group def */
		ParticleGroupDef CreateParticleGroupDef(ParticleProperties* properties);
	};
}
