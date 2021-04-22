/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Circle.h"

namespace Kross
{
	Circle::Circle(float radius) : m_radius(radius)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(m_RigidBody->GetPosition().x, m_RigidBody->GetPosition().y);
		
		b2Body* body = worldPointer->CreateBody(&bodyDef);

		b2CircleShape circleShape;
		circleShape.m_radius = m_radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.6f;

		body->CreateFixture(&fixtureDef);

		m_RigidBody->AttatchBody(body);
	}
}