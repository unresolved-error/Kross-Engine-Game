/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "ResourceManager.h"
#include "../File-IO/FileSystem.h"

namespace Kross
{
	ResourceManager*	ResourceManager::s_Instance =		nullptr;

	ResourceManager::~ResourceManager()
	{
		/* Clean up all the Geometry from memory. */
		for (int i = 0; i < m_Geometry.size(); i++)
		{
			delete m_Geometry[i];
			m_Geometry[i] = nullptr;
		}

		/* Clean up the list. */
		m_Geometry.clear();
		m_Geometry.~vector();

		/* Clean up all the Shaders from memory. */
		for (int i = 0; i < m_Shaders.size(); i++)
		{
			Shader::OnDestroy(m_Shaders[i]);
			m_Shaders[i] = nullptr;
		}

		/* Clean up the list. */
		m_Shaders.clear();
		m_Shaders.~vector();

		/* Clean up all the Sprites from memory. */
		for (int i = 0; i < m_Sprites.size(); i++)
		{
			Sprite::OnDestroy(m_Sprites[i]);
			m_Sprites[i] = nullptr;
		}

		/* Clean up the list. */
		m_Sprites.clear();
		m_Sprites.~vector();

		/* Clean up all the Textures from memory. */
		for (int i = 0; i < m_Textures.size(); i++)
		{
			Texture::OnDestroy(m_Textures[i]);
			m_Textures[i] = nullptr;
		}

		/* Clean up the list. */
		m_Textures.clear();
		m_Textures.~vector();

		/* Clean up all the Materials from memory. */
		for (int i = 0; i < m_Materials.size(); i++)
		{
			Material::OnDestroy(m_Materials[i]);
			m_Materials[i] = nullptr;
		}

		/* Clean up the list. */
		m_Materials.clear();
		m_Materials.~vector();

		/* Clean up all the Fonts from memory. */
		for (int i = 0; i < m_Fonts.size(); i++)
		{
			Font::OnDestroy(m_Fonts[i]);
			m_Fonts[i] = nullptr;
		}

		/* Clean up the list. */
		m_Fonts.clear();
		m_Fonts.~vector();

		/* Clean up all the Animations from memory. */
		for (int i = 0; i < m_Animations.size(); i++)
		{
			Animation::OnDestroy(m_Animations[i]);
			m_Animations[i] = nullptr;
		}

		/* Clean up the list. */
		m_Animations.clear();
		m_Animations.~vector();

		/* Clean up all the Audio Sources from memory. */
		for (int i = 0; i < m_AudioSources.size(); i++)
		{
			AudioSource::OnDestroy(m_AudioSources[i]);
			m_AudioSources[i] = nullptr;
		}

		/* Clean up the list. */
		m_AudioSources.clear();
		m_AudioSources.~vector();

		/* Clean up all the Tile Maps from memory. */
		for (int i = 0; i < m_TileMaps.size(); i++)
		{
			TileMap::OnDestroy(m_TileMaps[i]);
			m_TileMaps[i] = nullptr;
		}

		/* Clean up the list. */
		m_TileMaps.clear();
		m_TileMaps.~vector();

		/* Clean up all the Tile Sets from memory. */
		for (int i = 0; i < m_TileSets.size(); i++)
		{
			TileSet::OnDestroy(m_TileSets[i]);
			m_TileSets[i] = nullptr;
		}

		/* Clean up the list. */
		m_TileSets.clear();
		m_TileSets.~vector();

		/* Destroy the Atlas. */
		Atlas::OnDestroy(p_Atlas);
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

	void ResourceManager::OnReadManifest()
	{
		/* Load the Manifest File. */
		FileSystem::OnReadManifestFile();
	}

	void ResourceManager::OnWriteManifest()
	{
		// Seeing if it writes things properly.
		FileSystem::OnWriteAtlasData(s_Instance->p_Atlas);
	}
}