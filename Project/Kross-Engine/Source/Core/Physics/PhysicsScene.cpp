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
		delete p_PhysicsWorld;
	}

	Circle* PhysicsScene::CreateCircleBody(float radius, b2Body* body)
	{
		Circle* circle = new Circle(radius, body, 0.0f);
		AttachBody(body);

		return circle;
	}

	Box* PhysicsScene::CreateBoxBody(Vector2 dimensions, b2Body* body)
	{
		Box* box = new Box(dimensions, body, 0.0f);
		AttachBody(body);
		
		return box;
	}

	void PhysicsScene::CreatePlane(Vector2 normal, float distance, b2Body* body)
	{
		/* Not a real thing yet */
		/* Plane(normal, distance); */
	}

}
