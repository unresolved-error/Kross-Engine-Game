/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"

#include "Vertex.h"

namespace Kross
{
	struct KROSS_API LineVertex : public Vertex
	{
	public:
		LineVertex() :
			m_Position	(Vector2(0.0f)),
			m_Colour	(Colour(1.0f))
		{};
		LineVertex(Vector2 position, Colour colour) :
			m_Position	(position),
			m_Colour	(colour)
		{};

		Vector2 m_Position;
		Colour m_Colour;
	};
}