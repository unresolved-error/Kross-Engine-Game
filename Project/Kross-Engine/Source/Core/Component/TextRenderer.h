/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

#include "../Renderer/Text/Text.h"

namespace Kross
{
	/* Forward Declaration. */
	class KROSS_API Text;

	class KROSS_API TextRenderer : public Renderer
	{
	private:
		Text m_Text;

	protected:
		friend class Batch;

		// Text Renderer Update Method.
		void OnUpdate() override;

		// Text Renderer Render Method.
		void OnRender() override;

	public:
		TextRenderer() :
			m_Text(Text())
		{
			m_Text.SetTextRenderer(this);
		};
		~TextRenderer() {};

		// Gets the Current Text.
		const std::string GetText() const { return m_Text.GetText(); };

		// Gets the Text Font.
		Font* GetFont() const { return m_Text.GetFont(); };

		// Gets the Text's Text Alignment.
		TextAlignment GetTextAlignment() const { return m_Text.GetTextAlignment(); };

		// Gets the Text Colour.
		Colour GetColour() const { return m_Text.GetColour(); };

		// Gets the Text Size. (SIZE OF CHARACTERS IN TERMS OF WIDTH AND HEIGHT)
		const float GetTextSize() const { return m_Text.GetTextSize(); };

		// Sets the Text's Text to Render.
		void SetText(const std::string& text) { m_Text.SetText(text); };

		// Sets the Text Font.
		void SetFont(Font* font) { m_Text.SetFont(font); };

		// Sets the Text's Text Alignment.
		void SetTextAlignment(TextAlignment alignment) { m_Text.SetTextAlignment(alignment); };

		// Sets the Text Colour.
		void SetColour(Colour colour) { m_Text.SetColour(colour); };

		// Sets the Text Size. (SIZE OF CHARACTERS IN TERMS OF WIDTH AND HEIGHT)
		void SetTextSize(float size) { m_Text.SetTextSize(size); };
	};
}