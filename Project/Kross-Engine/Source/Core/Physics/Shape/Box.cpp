/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "Box.h"

namespace Kross
{
	Box::Box(Vector2 dimensions) : m_width(dimensions.x), m_height(dimensions.y)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(m_RigidBody->GetPosition().x, m_RigidBody->GetPosition().y);

		b2Body* body = worldPointer->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.6f;

		body->CreateFixture(&fixtureDef);

		m_RigidBody->AttatchBody(body);
	}
}