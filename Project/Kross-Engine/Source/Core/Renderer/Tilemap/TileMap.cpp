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