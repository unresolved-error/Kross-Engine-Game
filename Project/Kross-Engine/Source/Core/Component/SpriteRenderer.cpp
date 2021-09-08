/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SpriteRenderer.h"

#include "../Manager/ResourceManager.h"

namespace Kross
{
	void SpriteRenderer::OnStart()
	{
		#ifndef KROSS_EDITOR
		if (p_Material)
		{
			p_Material = KROSS_NEW Material(*p_Material);
		}
		#endif
	}

	SpriteRenderer::SpriteRenderer() :
		p_Material	(nullptr),
		m_FlipX		(false),
		m_FlipY		(false),
		m_Colour	(Colour(1.0f))
	{}

	SpriteRenderer::~SpriteRenderer()
	{
		#ifndef KROSS_EDITOR
		Material::OnDestroy(p_Material);
		#else
		p_Material = nullptr;
		#endif
	}
}