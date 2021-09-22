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
	class KROSS_API Plane : public Shape
	{
	private:
		Vector2 m_Normal;
		float m_DistanceToOrigin;

	public:
		Plane() :
			m_Normal			(Vector2(0.0f)),
			m_DistanceToOrigin	(0.0f)
		{};
		//Plane(Vector2 normal, float distanceToOrigin);

		ShapeType GetShapeType() const { return ShapeType::Plane; }

		float GetDistanceToOrigin() const { return m_DistanceToOrigin; }
	};
}