/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Character.h"

namespace Kross
{
	class KROSS_API Font
	{
	private:
		Font() : 
			m_Name			(""), 
			p_Texture		(nullptr), 
			m_Characters	(List<Character*>()),
			m_Sprites		(List<Sprite*>())
		{};
		~Font();

		std::string m_Name;
		Texture* p_Texture;
		List<Character*> m_Characters;
		List<Sprite*> m_Sprites;

	protected:
		friend class TextRenderer;

		// Gets the Texture of the Font.
		Texture* GetTexture() const { return p_Texture; };

		// Sets the Texture of the Font.
		void SetTexture(Texture* texture) { p_Texture = texture; };

		// Adds a Character to the Font.
		void AttachCharacter(Character* character) { m_Characters.push_back(character); };

		// Gets a Character from the Font. (BY CHAR)
		Character* GetCharacter(unsigned char character) const;

		// Gets a Character from the Font. (BY STRING)
		Character* GetCharacter(const std::string& character) const;

		// Gets a Character from the Font. (BY INDEX)
		Character* GetCharacter(int index) const;

	public:
		// Creates a Font.
		static Font* OnCreate(Texture* texture, int width, int height, const std::string& name);

		// Deletes the specified Font.
		static void OnDestroy(Font* font);

		// Gets the Name of the Font.
		const std::string GetName() const { return m_Name; };

		// Sets the Name of the Font.
		void SetName(const std::string& name) { m_Name = name; };
	};
}