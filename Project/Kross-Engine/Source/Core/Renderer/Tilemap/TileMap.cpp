#include "TileMap.h"


namespace Kross 
{


	void Kross::TileMap::SetMapIndexes(List<List<int>> mapIndexs)
	{
		m_MapSpriteIndexs = mapIndexs;
	}


	void TileMap::SetName(std::string name)
	{
		m_Name = name;
	}

	TileMap* TileMap::OnCreate(const std::string& name)
	{
		TileMap* map = KROSS_ALLOCATION_REPORT(TileMap());
		map->SetName(name);


		return map;
	}

	void TileMap::OnDestroy(TileMap* toDestruct)
	{
		//Not required, but safe code.
		if (toDestruct) { delete toDestruct; }
	}
	int TileMap::GetCellValue(const int x, const int y)
	{
		return m_MapSpriteIndexs[y][x];
	}
	
	const Vector2 TileMap::GetDimensions() const
	{
		return Vector2(m_MapSpriteIndexs[0].size(), m_MapSpriteIndexs.size());
	}
}