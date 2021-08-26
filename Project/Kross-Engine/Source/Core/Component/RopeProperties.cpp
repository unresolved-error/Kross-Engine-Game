#include "RopeProperties.h"

void Kross::RopeProperties::SetPositions(std::vector<Vector2> positionsToSet)
{
	for (int i = 0; i < positionsToSet.size - 1; i++)
	{
		positions.push_back(positionsToSet[i]);
	}
}
