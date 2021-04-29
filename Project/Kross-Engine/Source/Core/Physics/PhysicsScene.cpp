/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "PhysicsScene.h"

namespace Kross
{
	PhysicsScene::~PhysicsScene()
	{
		for (int i = 0; i < p_ParticleSystem->GetParticleCount(); i++)
		{
			p_ParticleSystem->DestroyParticle(i);
		}
		delete p_PhysicsWorld;

	}

	Circle* PhysicsScene::CreateCircleBody(float radius, Body* body)
	{
		Circle* circle = new Circle(radius, body, Vector2(0,0));
		AttachBody(body);

		return circle;
	}

	Box* PhysicsScene::CreateBoxBody(Vector2 dimensions, Body* body)
	{
		Box* box = new Box(dimensions, body, Vector2(0, 0));
		AttachBody(body);
		
		return box;
	}

	void PhysicsScene::CreatePlane(Vector2 normal, float distance, Body* body)
	{
		/* Not a real thing yet */
		/* Plane(normal, distance); */
	}

}
