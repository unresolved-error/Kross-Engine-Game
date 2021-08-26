/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "TileMapRenderer.h"

namespace Kross
{

	void TileMapRenderer::OnStart()
	{
		CreateTiles();
	}

	TileMapRenderer::~TileMapRenderer()
	{
		for (int i = 0; i < m_Tiles.size(); i++)
		{
			delete m_Tiles[i];
			m_Tiles[i] = nullptr;
		}
		m_Tiles.clear();
	}

	void TileMapRenderer::SetTileMap(TileMap* tileMap)
	{
		p_TileMap = tileMap;
		CreateTiles();
	}

	void TileMapRenderer::SetTileSet(TileSet* tileSet)
	{
		p_TileSet = tileSet;
		CreateTiles();
	}


	Sprite* TileMapRenderer::MatchMapCell(int x, int y)
	{
		int cellVal = p_TileMap->GetCellValue(x, y);

		return p_TileSet->GetSprite(cellVal);
	}

	void TileMapRenderer::CreateTiles()
	{

		if (!p_TileMap) { return; }


		if (m_Tiles.size() > 0)
		{
			for (int i = 0; i < m_Tiles.size(); i++)
			{
				delete m_Tiles[i];
				m_Tiles[i] = nullptr;


			}
			m_Tiles.clear();
		}

		


		for (int y = p_TileMap->GetDimensions().y - 1; y >= 0; y--)
		{
			for (int x = 0; x < p_TileMap->GetDimensions().x; x++) 
			{
				if (p_TileSet && p_TileMap->GetCellValue(x,y) != -1) 
				{
					Tile* newTile = KROSS_NEW Tile();

					newTile->SetSprite(MatchMapCell(x, y));

					Vector2 geomSize = newTile->GetSprite()->GetGeometry()->GetSize();
					newTile->SetOffset(Vector2((geomSize.x) * x + geomSize.x / 2.0f, -((geomSize.y) * y) - geomSize.y / 2.0f));
					m_Tiles.push_back(newTile);
					
				}
			}

		}

	}



}
	


