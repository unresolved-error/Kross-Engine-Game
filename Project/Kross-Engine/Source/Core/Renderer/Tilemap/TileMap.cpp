#include "TileMap.h"


namespace Kross 
{

	void Kross::TileMap::SetOrigin(Vector2 origin)
	{
		m_Origin = origin;
	}

	void Kross::TileMap::SetDimension(Vector2 dimension)
	{
		m_Dimension = dimension;
	}

	void Kross::TileMap::SetMapIndexes(List<List<int>> mapIndexs)
	{
		m_MapSpriteIndexs = mapIndexs;
	}

	void Kross::TileMap::AttachSprites(List<Sprite*> sprites)
	{
		m_Sprites = sprites;
	}

	void TileMap::SetName(std::string name)
	{
		m_Name = name;
	}

	void TileMap::SetTiles(List<List<Tile*>> tiles)
	{
		m_Tiles = tiles;
	}

	TileMap* TileMap::OnCreate(const std::string& name)
	{
		TileMap* map = KROSS_NEW TileMap();
		
		
		map->SetName(name);



		return map;
	}

	void TileMap::OnDestroy(TileMap* toDestruct)
	{
		//Not required, but safe code.
		if (toDestruct) { delete toDestruct; }
	}
}