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
			s_Instance = KROSS_ALLOCATION_REPORT(Physics());
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

	RaycastData* Physics::OnCircleCast(Vector2 pos, Vector2 direction, Body* body, float max, float radius)
	{
		direction = glm::normalize(direction);

		b2RayCastInput input;
		b2RayCastOutput output;
		input.maxFraction = max;
		input.p1 = body->GetTransform().p;
		input.p2 = Getb2Vec2(pos + max * direction);
		
		s_Instance->p_RayData->hit = body->GetFixtureList()->GetShape()->CircleCast(&output,
			input, body->GetTransform(), radius, 0);
		
		s_Instance->p_RayData->closestFraction = output.fraction;

		s_Instance->p_RayData->intersectionNormal = GetVector2(output.normal);
		s_Instance->p_RayData->intersectionPoint = GetVector2(input.p1) + output.fraction * direction;

		return s_Instance->p_RayData;
	}
}
