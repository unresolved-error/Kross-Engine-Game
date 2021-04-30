/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Box.h"

namespace Kross
{

	Box::Box(Vector2 dimensions, Body* body, Vector2 offset) : m_width(dimensions.x), m_height(dimensions.y)
	{
		/* Creates the shape */
		PolygonShape dynamicBox;
		/* Sets the shape as a box */
		dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
		
		/* Creates a fixtureDef and assigns all variables */
		FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.1f;
		
		body->CreateFixture(&fixtureDef);
	}
}