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
	struct KROSS_API BatchVertex
	{
	public:
		BatchVertex() : 
			m_Position	(Vector4(0.0f)),
			m_UVs		(Vector2(0.0f)),
			m_Colour	(Colour(1.0f))
		{};
		BatchVertex(Vector4 position, Vector2 uvs, Colour colour) : 
			m_Position	(position), 
			m_UVs		(uvs), 
			m_Colour	(colour)
		{};

		Vector4 m_Position;
		Vector2 m_UVs;
		Colour m_Colour;
	};
}