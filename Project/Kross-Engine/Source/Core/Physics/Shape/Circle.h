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

		Circle(float radius, Body* body, Vector2 offset);
	
		ShapeType GetShapeType() const override { return ShapeType::Circle; }

		float GetRadius() const { return m_radius; }
		
};
}