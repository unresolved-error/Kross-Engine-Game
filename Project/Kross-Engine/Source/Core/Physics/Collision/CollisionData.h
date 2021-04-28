/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"

#include "../../Component/Rigidbody2D.h"

namespace Kross
{
	struct KROSS_API CollisionData
	{
		Vector2 normal = { 0,0 };
		float depth = -1;

		Vector2 position = { 0,0 };
		
		Rigidbody2D* a = nullptr;
		Rigidbody2D* b = nullptr;

		void ResolveCollision();
	};
}
