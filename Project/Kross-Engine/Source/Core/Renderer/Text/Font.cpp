/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Font.h"

namespace Kross
{
	Font::~Font()
	{
		/* Null out the Texture. */
		p_Texture = nullptr;

		/* Delete Original Characters. */
		for (int i = 0; i < m_Characters.size(); i++)
		{
			/* Delete the Character. */
			delete m_Characters[i];
			m_Characters[i] = nullptr;
		}

		/* Delete Sprites. */
		for (int i = 0; i < m_Sprites.size(); i++)
		{
			/* Delete the Sprite. */
			Sprite::OnDestroy(m_Sprites[i]);
			m_Sprites[i] = nullptr;
		}
	}

	Font* Font::OnCreate(Texture* texture, int width, int height, const std::string& name)
	{
		/* Create the Font. */
		Font* font = new Font;
		font->SetName(name);
		font->SetTexture(texture);

		/* Get the Character Sprites. */
		List<Sprite*> characters = Sprite::OnCreate(texture, width, height);

		/* Create Characters and Assign the Sprites. */
		for (int i = 0; i < characters.size(); i++)
		{
			/* Create a Character and Assign the Sprite. */
			Character* character = new Character();
			character->SetSprite(characters[i]);

			/* Add the Character to the Font. */
			font->AttachCharacter(character);
		}

		/* Record the Sprites used for deleting. */
		font->m_Sprites = characters;

		/* Return the new Font. */
		return font;
	}

	void Font::OnDestroy(Font* font)
	{
		/* Safe programming, not really needed but good to have. */
		if (font)
			delete font;
	}

	Character* Font::GetCharacter(unsigned char character) const
	{
		/* Create a Character Copy. */
		Character* characterCopy = new Character();
		
		/* Get the possible character index. */
		int index = (int)character;

		/* Chech if the Character is within the bounds of the Array. */
		if (index < m_Characters.size())
		{
			/* Character Creation. */
			characterCopy->SetSprite(m_Characters[index]->GetSprite());

			/* Return the Character Copy. */
			return characterCopy;
		}

		/* Return null. */
		delete characterCopy;
		return nullptr;
	}

	Character* Font::GetCharacter(const std::string& character) const
	{
		/* Create a Character Copy. */
		Character* characterCopy = new Character();

		/* Get the possible first character index. */
		int index = (int)(unsigned char)character[0];

		/* Chech if the Character is within the bounds of the Array. */
		if (index < m_Characters.size())
		{
			/* Character Creation. */
			characterCopy->SetSprite(m_Characters[index]->GetSprite());

			/* Return the Character Copy. */
			return characterCopy;
		}

		/* Return null. */
		delete characterCopy;
		return nullptr;
	}

	Character* Font::GetCharacter(int index) const
	{
		/* Create a Character Copy. */
		Character* characterCopy = new Character();

		/* Chech if the index is within the bounds of the Array. */
		if (index >= 0 && index < m_Characters.size())
		{
			/* Character Creation. */
			characterCopy->SetSprite(m_Characters[index]->GetSprite());

			/* Return the Character Copy. */
			return characterCopy;
		}

		/* Return null. */
		delete characterCopy;
		return nullptr;
	}
}