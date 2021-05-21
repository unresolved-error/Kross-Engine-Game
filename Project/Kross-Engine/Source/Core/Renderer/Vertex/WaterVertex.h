/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"

namespace Kross
{
	struct KROSS_API WaterVertex
	{
	public:
		WaterVertex()
			: m_Position(Vector2(0.0f)), m_Velocity(Vector2(0.0f)), m_Colour(Colour(1.0f))
		{};
		WaterVertex(Vector2 position, Vector2 velocity, Colour colour)
			: m_Position(position), m_Velocity(velocity), m_Colour(colour)
		{};

		Vector2 m_Position;
		Vector2 m_Velocity;
		Colour m_Colour;
	};
}