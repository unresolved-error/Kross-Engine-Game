/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */


#pragma once

#include "../Core.h"

#include "Rigidbody2D.h"
#include "../Physics/Shape/Shape.h"
#include "../Physics/Shape/Circle.h"
#include "../Physics/Shape/Box.h"
#include "../Physics/Shape/Plane.h"

namespace Kross
{
	class KROSS_API PhysicsScene
	{
	private:
		PhysicsScene() {}
		~PhysicsScene();
	protected:

	public:
		void CreateCircleBody(float radius);
		void CreateBoxBody(Vector2 dimensions);
		void CreatePlane(Vector2 normal, float distance);

	};
}