/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Circle.h"

namespace Kross
{
	Circle::Circle(float radius, b2Body* body, float offset) : m_radius(radius)
	{
		b2CircleShape circleShape;
		circleShape.m_radius = radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.6f;

		body->CreateFixture(&fixtureDef);
	}
}