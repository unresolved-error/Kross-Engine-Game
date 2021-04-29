/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Circle.h"

namespace Kross
{
	Circle::Circle(float radius, Body* body, Vector2 offset) : m_radius(radius)
	{
		CircleShape circleShape;
		circleShape.m_radius = radius;

		FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 0.5f;
		fixtureDef.friction = 0.6f;

		body->CreateFixture(&fixtureDef);
	}
}