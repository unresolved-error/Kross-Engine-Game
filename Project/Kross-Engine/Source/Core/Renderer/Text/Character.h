/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Image/Sprite.h"

#include "../Shader/Shader.h"


namespace Kross
{
	class KROSS_API Character
	{
	private:
		Character();
		~Character();

		Shader* p_Shader;

		Sprite* p_Sprite;
		Vector2 m_Position, m_Scale;

		Matrix4 u_Model;

	protected:
		friend class Font;
		friend class Text;
		friend class Batch;

		// Sets the position in World Space or Screen Space of the Character. (TEXT USE)
		void SetPosition(Vector2 position);

		// Sets the scale in World Space or Screen Space of the Character. (TEXT USE)
		void SetScale(Vector2 scale);

		// Sets the Colour of the Character. (TEXT USE)
		void SetColour(Colour colour);

		// Sets the Sprite of the Character. (FONT USE)
		void SetSprite(Sprite* sprite);

		// Gets the Sprite of the Character. (FONT USE)
		Sprite* GetSprite() const { return p_Sprite; };

		// Renders the Character.
		void OnRender();
	public:

	};
}