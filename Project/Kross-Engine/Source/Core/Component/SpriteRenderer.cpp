/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SpriteRenderer.h"

#include "../Manager/ResourceManager.h"

namespace Kross
{
	SpriteRenderer::SpriteRenderer() : 
		p_Material	(nullptr),
		m_FlipX		(false),
		m_FlipY		(false),
		m_Colour	(Colour(1.0f))
	{}

	SpriteRenderer::~SpriteRenderer()
	{
		p_Material = nullptr;
	}
}