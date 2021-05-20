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
	struct KROSS_API Vertex
	{
	public:
		Vertex() :
			m_Position	(Vector2(0.0f)), 
			m_UVs		(Vector2(0.0f)),
			m_Colour	(Colour(1.0f))
		{};
		Vertex(Vector2 position, Vector2 uvs, Colour colour) :
			m_Position	(position),
			m_UVs		(uvs), 
			m_Colour	(colour)
		{};

		Vector2 m_Position, m_UVs;
		Colour m_Colour;
	};
}