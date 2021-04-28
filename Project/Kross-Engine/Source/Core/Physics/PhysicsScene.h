/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *		- Deklyn Palmer.
 */


#pragma once

#include "../Core.h"

#include "Shape/Shape.h"
#include "Shape/Circle.h"
#include "Shape/Box.h"
#include "Shape/Plane.h"

namespace Kross
{
	class KROSS_API PhysicsScene
	{
	private:
		b2World* p_PhysicsWorld;

		List<b2Body*> m_bodies;

	protected:
		friend class Scene;
		void SetPhysicsWorld(b2World* world) { p_PhysicsWorld = world; }

	public:
		Circle* CreateCircleBody(float radius, b2Body* body);
		Box* CreateBoxBody(Vector2 dimensions, b2Body* body);
		void CreatePlane(Vector2 normal, float distance, b2Body* body);

		void AttachBody(b2Body* body) { m_bodies.push_back(body); }

		PhysicsScene() { p_PhysicsWorld = nullptr; }
		~PhysicsScene();

		b2World* GetPhysicsWorld() { return p_PhysicsWorld; }

	};
}