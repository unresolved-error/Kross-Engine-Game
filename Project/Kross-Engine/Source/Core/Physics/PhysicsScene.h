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
		/* Sets the Physics World */
		void SetPhysicsWorld(World* world) { p_PhysicsWorld = world; }

		/* Sets the Particle System */
		void SetParticleSystem(ParticleSystem* particleSystem) { p_ParticleSystem = particleSystem; }

	public:
		PhysicsScene() : p_PhysicsWorld(nullptr), p_ParticleSystem(nullptr) {};
		~PhysicsScene();

		/* Takes the radius and body, creating a new Circle */
		Circle* CreateCircleBody(float radius, Body* body);

		/* Takes the dimensions and body, creating a new Box */
		Box* CreateBoxBody(Vector2 dimensions, Body* body);

		/* Takes a normal, distance and body, creating a new Plane */
		void CreatePlane(Vector2 normal, float distance, Body* body);

		/* Adds the Body to a list of bodies */
		void AttachBody(Body* body) { m_bodies.push_back(body); }

		/* Returns the Physics World */
		World* GetPhysicsWorld() { return p_PhysicsWorld; }

		/* Return the Particle System */
		ParticleSystem* GetParticleSystem() { return p_ParticleSystem; }

	};
}