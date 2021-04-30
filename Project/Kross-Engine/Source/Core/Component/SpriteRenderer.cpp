/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SpriteRenderer.h"

#include "../Manager/ResourceManager.h"

namespace Kross
{
	SpriteRenderer::SpriteRenderer()
		: p_Sprite(nullptr), p_Shader(nullptr), m_Colour(1.0f), m_FlipX(false), m_FlipY(false)
	{
		/* Get an already preloaded shader. */
		p_Shader = ResourceManager::GetResource<Shader>("StandardShader");
	}

	SpriteRenderer::~SpriteRenderer()
	{
		p_Shader = nullptr;
		p_Sprite = nullptr;
	}

	void SpriteRenderer::SetSprite(Sprite* sprite)
	{
		/* Set the Sprite. */
		p_Sprite = sprite;

		/* Set Shader Values. */
		p_Shader->SetUniform("u_UVRatio", p_Sprite->GetUVRatio());
		p_Shader->SetUniform("u_UVOffset", p_Sprite->GetUVOffset());
	}

	void SpriteRenderer::SetColour(Colour colour)
	{
		/* Set the Colour. */
		m_Colour = colour;

		/* Set Shader Values. */
		p_Shader->SetUniform("u_Colour", m_Colour);
	}

	void SpriteRenderer::SetFlipX(bool value)
	{
		/* Set the X Flip. */
		m_FlipX = value;

		/* Set Shader Values. */
		p_Shader->SetUniform("u_FlipX", m_FlipX);
	}

	void SpriteRenderer::SetFlipY(bool value)
	{
		/* Set the Y Flip. */
		m_FlipY = value;

		/* Set Shader Values. */
		p_Shader->SetUniform("u_FlipY", m_FlipY);
	}

	void SpriteRenderer::OnStart()
	{
		/* Set Shader Values. */
		p_Shader->SetUniform("u_UVRatio", p_Sprite->GetUVRatio());
		p_Shader->SetUniform("u_UVOffset", p_Sprite->GetUVOffset());
		p_Shader->SetUniform("u_Colour", m_Colour);
		p_Shader->SetUniform("u_FlipX", m_FlipX);
		p_Shader->SetUniform("u_FlipY", m_FlipY);
	}

	void SpriteRenderer::OnRender()
	{
		/* If we have a Sprite. */
		if (p_Sprite)
		{
			/* Get the Attached object Transform and update that in the Shader. */
			Transform2D* transform = GetObject()->GetTransform();
			p_Shader->SetUniform("u_Model", transform->GetModelMatrix());

			/* Set the Texture Slot. */
			Texture* spriteTexture = p_Sprite->GetTexture();

			/* Set the Shader */
			spriteTexture->SetSlot(0);
			spriteTexture->Attach();
			p_Shader->SetUniform("u_Texture", spriteTexture);

			/* Render. */
			p_Shader->Attach();
			p_Sprite->OnRender();

			/* Un Bind all Textures. */
			Texture::Detach();
		}
	}
}