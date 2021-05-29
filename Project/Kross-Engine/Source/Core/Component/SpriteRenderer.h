/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

#include "../Renderer/Material.h"
#include "../Math/Math.h"

#include "Camera.h"

namespace Kross
{
	//class KROSS_API Renderer;

	class KROSS_API SpriteRenderer : public Renderer
	{
	private:
		Material* p_Material;
		Colour m_Colour;

		bool m_FlipX, m_FlipY;

	protected:

	public:
		SpriteRenderer();
		~SpriteRenderer();

		// Sets the Material.
		void SetMaterial(Material* material) { p_Material = material; };

		// Sets the Sprite.
		void SetMaterialTextureSprite(Sprite* sprite) { p_Material->p_Sprite = sprite; };

		// Sets the Sprite.
		void SetMaterialNormalMap(Sprite* sprite) { p_Material->p_NormalMap = sprite; };

		// Sets the Sprite.
		void SetMaterialSpecularMap(Sprite* sprite) { p_Material->p_SpecularMap = sprite; };

		// Sets the Tint Colour.
		void SetColour(Colour colour) { m_Colour = colour; };

		// Sets the X Flip.
		void SetFlipX(bool value) { m_FlipX = value; };

		// Sets the Y Flip.
		void SetFlipY(bool value) { m_FlipY = value; };

		// Gets the Material.
		Material* GetMaterial() const { return p_Material; };

		// Gets the Texture Sprite.
		Sprite* GetTextureSprite() const { return p_Material->p_Sprite; };

		// Gets the Normal Map.
		Sprite* GetNormalMap() const { return p_Material->p_NormalMap; };

		// Gets the Specular Map.
		Sprite* GetSpecularMap() const { return p_Material->p_SpecularMap; };

		// Gets the Tint Colour.
		Colour GetColour() const { return m_Colour; };

		// Gets the X Flip.
		inline bool GetFlipX() const { return m_FlipX; };

		// Gets the Y Flip.
		inline bool GetFlipY() const { return m_FlipY; };

	};
}
