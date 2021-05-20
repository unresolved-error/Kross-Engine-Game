/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Font.h"

namespace Kross
{
	/* Forward Declaration. */
	class KROSS_API TextRenderer;

	/* For Text Alignment. */
	enum class KROSS_API TextAlignment
	{
		Left,
		Center,
		Right,
	};

	class KROSS_API Text
	{
	private:
		std::string m_Text, m_PreviousText;

		Font* p_Font;
		Font* p_PreviousFont;
		List<Character*> m_TextCharacters;

		TextRenderer* p_TextRenderer;

		TextAlignment m_Alignment;

		Colour m_Colour;
		float m_Size;

	protected:
		friend class TextRenderer;

		// Sets the Text Renderer that the Text is attached to.
		void SetTextRenderer(TextRenderer* renderer) { p_TextRenderer = renderer; };

		// Updates the Text.
		void OnUpdate();

		// Renders the Text.
		void OnRender();

	public:
		Text()
			: m_Text(std::string()), m_PreviousText(std::string()), p_Font(nullptr), p_PreviousFont(nullptr), m_TextCharacters(List<Character*>()), p_TextRenderer(nullptr), m_Alignment(TextAlignment::Center), m_Colour(Colour(1.0f)), m_Size(1.0f)
		{};
		~Text();

		// Gets the Current Text.
		const std::string GetText() const { return m_Text; };

		// Gets the Text Font.
		Font* GetFont() const { return p_Font; };

		// Gets the Text's Text Alignment.
		TextAlignment GetTextAlignment() const { return m_Alignment; };

		// Gets the Text Colour.
		Colour GetColour() const { return m_Colour; };

		// Gets the Text Size. (SIZE OF CHARACTERS IN TERMS OF WIDTH AND HEIGHT)
		const float GetTextSize() const { return m_Size; };

		// Sets the Text's Text to Render.
		void SetText(const std::string& text) { m_Text = text; };

		// Sets the Text Font.
		void SetFont(Font* font) { p_Font = font; };

		// Sets the Text's Text Alignment.
		void SetTextAlignment(TextAlignment alignment) { m_Alignment = alignment; };

		// Sets the Text Colour.
		void SetColour(Colour colour) { m_Colour = colour; };

		// Sets the Text Size. (SIZE OF CHARACTERS IN TERMS OF WIDTH AND HEIGHT)
		void SetTextSize(float size) { m_Size = size; };
	};
}