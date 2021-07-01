#include "TileMap.h"

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
