/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

namespace Kross
{
	enum class KROSS_API AssetType
	{
		None,
		Sprite,
		Texture,
		Material,
		Font,
		Animation,
		AudioSource,
		TileMap,
		TileSet,

		/* Not an Asset type. */
		Count,
	};

	const struct KROSS_API AssetTypeName
	{
	private:
		List<std::string> m_Names;

	public:
		AssetTypeName()
		{
			m_Names.push_back("None");
			m_Names.push_back("Sprite");
			m_Names.push_back("Texture");
			m_Names.push_back("Material");
			m_Names.push_back("Font");
			m_Names.push_back("Animation");
			m_Names.push_back("Audio Source");
			m_Names.push_back("Tile Map");
			m_Names.push_back("Tile Set");
		}

		std::string operator[](int index)
		{
			if(index >= 0 || index < m_Names.size())
				return m_Names[index];

			return std::string();
		}
	};
}