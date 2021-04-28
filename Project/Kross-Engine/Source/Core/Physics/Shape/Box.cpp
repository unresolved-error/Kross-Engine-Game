/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Box.h"

namespace Kross
{
	Box::Box(Vector2 dimensions, b2Body* body, float offset) : m_width(dimensions.x), m_height(dimensions.y)
	{
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.6f;
		
		body->CreateFixture(&fixtureDef);

	}
}