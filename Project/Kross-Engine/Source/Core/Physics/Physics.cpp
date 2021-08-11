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
		body->GetWorld()->RayCast(s_Instance->p_RayCallback, { pos.x, pos.y }, Getb2Vec2(pos + direction * max));

		//Vector2 vector = GetVector2(b2Vec2(1.0f, 1.0f));

		s_Instance->p_RayData = s_Instance->p_RayCallback->GetRayData();

		return s_Instance->p_RayData;
	}

	RaycastData* Physics::OnCircleCast(Vector2 pos, Vector2 direction, Body* body, float max, float radius)
	{
		direction = glm::normalize(direction);

		b2PolygonShape* shape = KROSS_NEW b2PolygonShape();
		for (b2Fixture* thisFixture = body->GetFixtureList(); thisFixture; thisFixture = thisFixture->GetNext())
		{
			if (thisFixture->GetShape()->m_type == b2Shape::Type::e_polygon)
			{
				shape = (b2PolygonShape*)thisFixture->GetShape();
			}
		}

		b2RayCastInput input;
		b2RayCastOutput output;
		input.maxFraction = max;
		input.p1 = Getb2Vec2(pos);
		input.p2 = input.p1 + input.maxFraction * Getb2Vec2(direction);
		
		s_Instance->p_RayData->hit = shape->CircleCast(&output,
			input, body->GetTransform(), radius, 0);
		
		s_Instance->p_RayData->closestFraction = output.fraction;
		s_Instance->p_RayData->intersectionNormal = GetVector2(output.normal);

		if (s_Instance->p_RayData->hit == true)
		{
			s_Instance->p_RayData->intersectionPoint = GetVector2(input.p1) + output.fraction * (GetVector2(input.p2) - GetVector2(input.p1));
		}
		//s_Instance->p_RayData->intersectionPoint = GetVector2(input.p1) + output.fraction * (GetVector2(input.p2) - GetVector2(input.p1));

		return s_Instance->p_RayData;
	}
}
