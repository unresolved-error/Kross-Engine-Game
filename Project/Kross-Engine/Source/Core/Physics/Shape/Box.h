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
	class KROSS_API Box : public Shape
	{
	private:
		float m_height;
		float m_width;

	public:

		Box(Vector2 dimensions, Body* body, Vector2 offset);

		ShapeType GetShapeType() const { return ShapeType::Box; }

		float GetHeight() const { return m_height; }
		float GetWidth() const { return m_width; }

	};
}