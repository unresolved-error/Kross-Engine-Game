/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#include "Physics.h"


namespace Kross
{
	Physics*			Physics::s_Instance =				nullptr;

	Physics::~Physics()
	{
		delete p_CollisionData;
	}

	void Physics::OnCreate()
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW Physics();
	}

	void Physics::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}

	RaycastData* Physics::OnRayCast(Vector2 pos, Vector2 direction, Body* body, float max)
	{
		body->GetWorld()->RayCast(s_Instance->p_RayCallback, { pos.x, pos.y }, { pos.x + direction.x * max, pos.y + direction.y * max });

		//Vector2 vector = GetVector2(b2Vec2(1.0f, 1.0f));

		s_Instance->p_RayData = s_Instance->p_RayCallback->GetRayData();

		return s_Instance->p_RayData;
	}

	RaycastData* Physics::OnCircleCast(Vector2 pos, Vector2 direction, Body* body, float max)
	{
		direction = glm::normalize(direction);

		b2RayCastInput input;
		b2RayCastOutput output;
		input.maxFraction = max;
		input.p1 = b2Vec2(pos.x, pos.y);
		input.p2 = b2Vec2(pos.x, pos.y + 0.5f * direction.y);
		
		body->GetFixtureList()->GetShape()->CircleCast(&output, input, body->GetTransform(), 0.5f, 0);
		
		s_Instance->p_RayData = s_Instance->p_RayCallback->GetRayData();

		return s_Instance->p_RayData;
	}
}
