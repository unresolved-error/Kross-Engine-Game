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
	}

	void PhysicsScene::CreateCircleBody(float radius)
	{
		Circle* circle = new Circle(radius);
	}

	void PhysicsScene::CreateBoxBody(Vector2 dimensions)
	{
		Box* box = new Box(dimensions);
	}

	void PhysicsScene::CreatePlane(Vector2 normal, float distance)
	{

	}

}
