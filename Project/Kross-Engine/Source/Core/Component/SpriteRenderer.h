/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

#include "../Renderer/Image/Sprite.h"
#include "../Renderer/Shader/Shader.h"
#include "../Math/Math.h"

#include "Camera.h"

namespace Kross
{
	//class KROSS_API Renderer;

	class KROSS_API SpriteRenderer : public Renderer
	{
	private:
		Sprite* p_Sprite;
		Shader* p_Shader;

		Colour m_Colour;

		bool m_FlipX, m_FlipY;

	protected:
		// Sprite Renderer Start Method.
		void OnStart() override;

		// Sprite Renderer Render Method.
		void OnRender() override;

	public:
		SpriteRenderer();
		~SpriteRenderer();

		// Sets the Sprite.
		void SetSprite(Sprite* sprite);

		// Sets the Tint Colour.
		void SetColour(Colour colour);

		// Sets the X Flip.
		void SetFlipX(bool value);

		// Sets the Y Flip.
		void SetFlipY(bool value);

		// Gets the Current Sprite.
		Sprite* GetSprite() const { return p_Sprite; };

		// Gets the Tint Colour.
		Colour GetColour() const { return m_Colour; };

		// Gets the X Flip.
		inline bool GetFlipX() const { return m_FlipX; };

		// Gets the Y Flip.
		inline bool GetFlipY() const { return m_FlipY; };

	};
}
