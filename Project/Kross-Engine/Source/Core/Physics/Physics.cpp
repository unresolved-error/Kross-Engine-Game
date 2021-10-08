/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#include "Physics.h"


namespace Kross
{
	Physics*			Physics::m_Instance =				nullptr;

	Physics::~Physics()
	{
		delete p_CollisionData;
	}

	void Physics::OnCreate()
	{
		if (!m_Instance)
		{
			m_Instance = KROSS_NEW Physics();
		}
	}

	void Physics::OnDestroy()
	{
		if (m_Instance)
		{
			delete m_Instance;
		}
	}

	RaycastData* Physics::OnRayCast(Vector2 pos, Vector2 direction, Body* body, float max)
	{
		body->GetWorld()->RayCast(m_Instance->p_RayCallback, { pos.x, pos.y }, Getb2Vec2(pos + direction * max));

		//Vector2 vector = GetVector2(b2Vec2(1.0f, 1.0f));

		m_Instance->p_RayData = m_Instance->p_RayCallback->GetRayData();

		return m_Instance->p_RayData;
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
		
		m_Instance->p_RayData->hit = shape->CircleCast(&output,
			input, body->GetTransform(), radius, 0);
		
		m_Instance->p_RayData->closestFraction = output.fraction;
		m_Instance->p_RayData->intersectionNormal = GetVector2(output.normal);

		if (m_Instance->p_RayData->hit == true)
		{
			m_Instance->p_RayData->intersectionPoint = GetVector2(input.p1) + output.fraction * (GetVector2(input.p2) - GetVector2(input.p1));
		}
		//m_Instance->p_RayData->intersectionPoint = GetVector2(input.p1) + output.fraction * (GetVector2(input.p2) - GetVector2(input.p1));

		return m_Instance->p_RayData;
	}
	Vector2 Physics::GetCollisionNormal(b2Contact* contact)
	{
		b2WorldManifold manifold = b2WorldManifold();
		contact->GetWorldManifold(&manifold);

		return Vector2(manifold.normal.x ,manifold.normal.y);
	}
}
