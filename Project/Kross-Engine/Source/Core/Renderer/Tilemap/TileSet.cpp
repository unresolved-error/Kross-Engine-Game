/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */


#include "TileSet.h"

namespace Kross {

	TileSet::~TileSet()
	{
		for (int i = 0; i < m_Sprites.size(); i++)
		{
			m_Sprites[i] = nullptr;
		}
	}


	Sprite* TileSet::GetSprite(int index)
	{
		if (index >= 0 && index < m_Sprites.size()) {

			return m_Sprites[index];
		}
		return nullptr;
	}

	TileSet* TileSet::OnCreate(const std::string& name)
	{
		TileSet* tileset = KROSS_NEW TileSet();
		tileset->SetName(name);

		return tileset;

	}

	void TileSet::OnDestroy(TileSet* tileSet)
	{
		if (tileSet) { delete tileSet; }
	}



}