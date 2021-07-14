/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"
#include "../Physics.h"

namespace Kross
{
	struct KROSS_API RaycastData
	{	
		bool hit = false;
		float closestFraction = 1.0f;
		float maxFraction = 1.0f;

		Vector2 pos = Vector2(0, 0);
		Vector2 direction = Vector2(0, 0);

		Vector2 intersectionPoint = pos + maxFraction * direction;
		Vector2 intersectionNormal = Vector2(0, 0);

		b2Fixture* fixture = nullptr;
		b2Body* body = nullptr;
	};
}