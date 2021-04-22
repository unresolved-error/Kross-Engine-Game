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

		Box(Vector2 dimensions);

		ShapeType GetShapeType() const override { return ShapeType::Box; }

		Vector2 GetCenter() const { return m_RigidBody->GetPosition(); }
		float GetHeight() const { return m_height; }
		float GetWidth() const { return m_width; }

	};
}