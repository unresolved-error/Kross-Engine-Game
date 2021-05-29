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
	struct KROSS_API SpriteVertex
	{
	public:
		SpriteVertex() :
			m_Position		(Vector2(0.0f)), 
			m_TextureUVs	(Vector2(0.0f)),
			m_NormalUVs		(Vector2(0.0f)),
			m_SpecularUVs	(Vector2(0.0f)),
			m_WorldNormal	(Vector3(0.0f, 0.0f, 1.0f)),
			m_Colour		(Colour(1.0f))
		{};
		SpriteVertex(Vector2 position, Vector2 textureUVs, Vector2 normalUVs, Vector2 specularUVs, Vector3 worldNormal, Colour colour) :
			m_Position		(position),
			m_TextureUVs	(textureUVs),
			m_NormalUVs		(normalUVs),
			m_SpecularUVs	(specularUVs),
			m_WorldNormal   (worldNormal),
			m_Colour		(colour)
		{};

		Vector2 m_Position, m_TextureUVs, m_NormalUVs, m_SpecularUVs;
		Vector3 m_WorldNormal;
		Colour m_Colour;
	};
}