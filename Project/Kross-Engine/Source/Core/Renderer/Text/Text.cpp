/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Text.h"

#include "../../Component/TextRenderer.h"

namespace Kross
{
	Text::~Text()
	{
		/* Null out Font. */
		p_Font = nullptr;

		/* Clean up Characters. */
		for (int i = 0; i < m_TextCharacters.size(); i++)
		{
			/* Delete Character. */
			delete m_TextCharacters[i];
			m_TextCharacters[i] = nullptr;
		}
	}

	void Text::OnUpdate()
	{
		/* If we don't have a Font, early out. */
		if (!p_Font)
			return;

		/* If we don't have a any Text, early out. */
		if (m_Text.empty())
			return;

		/* We have different text so create Characters for it. */
		if (m_PreviousText != m_Text || p_PreviousFont != p_Font)
		{
			/* If there are non-existing characters in the Text. */
			if (m_TextCharacters.size() == 0)
			{
				/* Get all the new Characters. */
				for (int i = 0; i < m_Text.length(); i++)
				{
					/* Get a New One. */
					m_TextCharacters.push_back(p_Font->GetCharacter((unsigned char)m_Text[i]));
				}
			}

			/* If there are pre-existing characters in the Text. */
			else
			{
				/* Get all the new Characters. */
				for (int i = 0; i < m_TextCharacters.size(); i++)
				{
					/* Get a New One. */
					delete m_TextCharacters[i];
					m_TextCharacters[i] = nullptr;
				}

				/* Clear the List. */
				m_TextCharacters.clear();

				/* Get all the new Characters. */
				for (int i = 0; i < m_Text.length(); i++)
				{
					/* Get a New One. */
					m_TextCharacters.push_back(p_Font->GetCharacter((unsigned char)m_Text[i]));
				}
			}

			m_PreviousText = m_Text;
			p_PreviousFont = p_Font;
		}

		/* Get the Alignment and Size Variables. */
		Sprite* spriteCharacter = m_TextCharacters[0]->GetSprite();

		float xOffset = ((float)spriteCharacter->GetWidth() / (float)BASE_SPRITE_WIDTH_AND_HEIGHT) * m_Size;
		float textLength = xOffset * m_Text.length(); /* Gets the Total Length of the Text in Screen / World Space. */

		float startPoint = 0.0f;
		
		/* Object Variables. */
		Vector2 objectPosition = p_TextRenderer->GetObject()->GetTransform()->m_Position;

		/* Get the Starting location for the Text. */
		switch (m_Alignment)
		{
			case TextAlignment::Left:
			{
				startPoint = objectPosition.x;
				break;
			}

			case TextAlignment::Center:
			{
				startPoint = objectPosition.x - (textLength / 2.0f);
				break;
			}

			case TextAlignment::Right:
			{
				startPoint = objectPosition.x - textLength;
				break;
			}

			default:
			{
				/* If Something Goes Wrong, do Nothing. */
				return;
			}
		}

		float position = startPoint;

		/* Update the Characters. */
		for (int i = 0; i < m_TextCharacters.size(); i++)
		{
			/* Set Position and Scale. */
			m_TextCharacters[i]->SetPosition(Vector2(startPoint, objectPosition.y));
			m_TextCharacters[i]->SetScale(Vector2(m_Size));

			/* Move the Start Point. */
			startPoint += xOffset;
		}
	}

	void Text::OnRender()
	{
		/* If we don't have a Font, early out. */
		if (!p_Font)
			return;

		/* If we don't have a any Text, early out. */
		if (m_Text.empty())
			return;

		for (int i = 0; i < m_TextCharacters.size(); i++)
		{
			m_TextCharacters[i]->SetColour(m_Colour);
			m_TextCharacters[i]->OnRender();
		}
	}
}