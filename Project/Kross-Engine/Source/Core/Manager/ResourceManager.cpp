/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "ResourceManager.h"

namespace Kross
{
	ResourceManager*	ResourceManager::s_Instance =		nullptr;

	List<Geometry*>		ResourceManager::s_Geometry =		List<Geometry*>();
	List<Shader*>		ResourceManager::s_Shaders =		List<Shader*>();
	List<Sprite*>		ResourceManager::s_Sprites =		List<Sprite*>();
	List<Texture*>		ResourceManager::s_Textures =		List<Texture*>();
	List<Font*>			ResourceManager::s_Fonts =			List<Font*>();
	Atlas*				ResourceManager::s_Atlas =			nullptr;

	ResourceManager::~ResourceManager()
	{
		/* Clean up all the Geometry from memory. */
		for (int i = 0; i < s_Geometry.size(); i++)
		{
			delete s_Geometry[i];
			s_Geometry[i] = nullptr;
		}

		/* Clean up the list. */
		s_Geometry.clear();
		s_Geometry.~vector();

		/* Clean up all the Shaders from memory. */
		for (int i = 0; i < s_Shaders.size(); i++)
		{
			Shader::OnDestroy(s_Shaders[i]);
			s_Shaders[i] = nullptr;
		}

		/* Clean up the list. */
		s_Shaders.clear();
		s_Shaders.~vector();

		/* Clean up all the Sprites from memory. */
		for (int i = 0; i < s_Sprites.size(); i++)
		{
			Sprite::OnDestroy(s_Sprites[i]);
			s_Sprites[i] = nullptr;
		}

		/* Clean up the list. */
		s_Sprites.clear();
		s_Sprites.~vector();

		/* Clean up all the Textures from memory. */
		for (int i = 0; i < s_Textures.size(); i++)
		{
			Texture::OnDestroy(s_Textures[i]);
			s_Textures[i] = nullptr;
		}

		/* Clean up the list. */
		s_Textures.clear();
		s_Textures.~vector();

		/* Clean up all the Fonts from memory. */
		for (int i = 0; i < s_Fonts.size(); i++)
		{
			Font::OnDestroy(s_Fonts[i]);
			s_Fonts[i] = nullptr;
		}

		/* Clean up the list. */
		s_Fonts.clear();
		s_Fonts.~vector();

		/* Destroy the Atlas. */
		Atlas::OnDestroy(s_Atlas);
	}

	void ResourceManager::OnCreate()
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW ResourceManager();
	}

	void ResourceManager::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}