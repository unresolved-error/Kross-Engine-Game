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
#include "Shape/Plane.h"

#include "Particles/Particle.h"

namespace Kross
{
	class KROSS_API PhysicsScene
	{
	private:
		World* p_PhysicsWorld;
		ParticleSystem* p_ParticleSystem;

		List<Body*> m_bodies;

	protected:
		friend class Scene;
		void SetPhysicsWorld(World* world) { p_PhysicsWorld = world; }
		void SetParticleSystem(ParticleSystem* particleSystem) { p_ParticleSystem = particleSystem; }

	public:
		Circle* CreateCircleBody(float radius, Body* body);
		Box* CreateBoxBody(Vector2 dimensions, Body* body);
		void CreatePlane(Vector2 normal, float distance, Body* body);

		void AttachBody(Body* body) { m_bodies.push_back(body); }

		PhysicsScene() : p_PhysicsWorld(nullptr), p_ParticleSystem(nullptr) {};
		~PhysicsScene();

		World* GetPhysicsWorld() { return p_PhysicsWorld; }
		ParticleSystem* GetParticleSystem() { return p_ParticleSystem; }

	};
}