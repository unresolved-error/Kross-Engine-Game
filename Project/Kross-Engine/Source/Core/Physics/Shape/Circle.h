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
	class KROSS_API Circle : public Shape
	{
	private:
		float m_radius;

	public:
		/* Creates a circle using the radius and body */
		Circle(float radius, Vector2 offset);
	
		/* Returns the shape type */
		ShapeType GetShapeType() const override { return ShapeType::Circle; }

		/* Returns the radius */
		float GetRadius() const { return m_radius; }
		
};
}