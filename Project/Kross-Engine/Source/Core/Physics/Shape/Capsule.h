/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../../Core.h"

#include "Shape.h"

namespace Kross
{
	class KROSS_API Capsule : public Shape
	{
	private:
		float m_height;
		float m_width;
		std::vector<FixtureDef*> m_Fixtures;

	public:
		/* Creates a new box using the dimensions and body */
		Capsule(Vector2 dimensions, Vector2 offset, std::vector<FixtureDef*> fixtures) :
			m_width	(dimensions.x),
			m_height(dimensions.y)
		{
			for (int i = 0; i < fixtures.size(); i++)
			{
				m_Fixtures.push_back(fixtures[i]);
			}
		};

		/* Returns the shape type */
		ShapeType GetShapeType() const { return ShapeType::Capsule; }

		/* Returns the height */
		float GetHeight() { return m_height; }

		/* Returns the width */
		float GetWidth() const { return m_width; }

		std::vector<FixtureDef*> GetFixtures() const { return m_Fixtures; }
	};
}