/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *		- Deklyn Palmer.
 */


#pragma once

#include "../Core.h"

#include "Physics.h"

#include "Shape/Shape.h"
#include "Shape/Circle.h"
#include "Shape/Box.h"
#include "Shape/Capsule.h"
#include "Shape/Plane.h"

#include "Particles/Particle.h"

namespace Kross
{
	class KROSS_API PhysicsScene
	{
	private:
		World* p_PhysicsWorld;
		List<ParticleSystem*> m_ParticleSystem;

		List<Body*> m_bodies;

	protected:
		friend class Scene;
		friend class ParticleEmitter;
		/* Sets the Physics World */
		void SetPhysicsWorld(World* world) { p_PhysicsWorld = world; }

	public:
		PhysicsScene() :
			p_PhysicsWorld		(nullptr)
		{};
		~PhysicsScene();

		/* Sets the Particle System */
		void AddParticleSystem(ParticleSystem* particleSystem) { m_ParticleSystem.push_back(particleSystem); }

		/* Adds the Body to a list of bodies */
		void AttachBody(Body* body) { m_bodies.push_back(body); }

		/* Deletes the Body from the list of bodies */
		void DetachBody(Body* body);

		/* Returns the Physics World */
		World* GetPhysicsWorld() { return p_PhysicsWorld; }

		/* Return the Particle System */
		List<ParticleSystem*> GetParticleSystem() { return m_ParticleSystem; }

		List<Body*> GetBodyList() { return m_bodies; }

	};
}