/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"

//#include "../../Component/Rigidbody2D.h"
#include "../Physics.h"
#include "ContactFilter.h"

namespace Kross
{
	struct KROSS_API ColliderData
	{
		Vector2 normal = { 0,0 };
		float depth = -1;

		Vector2 position = { 0,0 };
	};

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

	class KROSS_API CollisionData
	{
	private:
		ColliderData* p_ColliderData;
		RaycastData* p_RayData;

	public:
		CollisionData() : 
			p_ColliderData(KROSS_NEW ColliderData()), 
			p_RayData(KROSS_NEW RaycastData()) {}
		~CollisionData()
		{
			delete p_ColliderData;
			delete p_RayData;
		}

		ColliderData* GetCollisionData() { return p_ColliderData; }

		RaycastData* GetRayData() { return p_RayData; }
	};
}
