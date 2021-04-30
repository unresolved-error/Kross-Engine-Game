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
		/* Creates the cirlce */
		CircleShape circleShape;
		/* Sets the circles radius */
		circleShape.m_radius = radius;

		/* Creates a fixtureDef and assigns the variables */
		FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 0.5f;
		fixtureDef.friction = 0.6f;

		body->CreateFixture(&fixtureDef);
	}
}