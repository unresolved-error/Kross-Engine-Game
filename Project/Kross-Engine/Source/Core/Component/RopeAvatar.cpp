/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#include "RopeAvatar.h"

namespace Kross
{
	void RopeAvatar::DetachPosition(int index)
	{
		if (index < 0 || index >= m_BasePositions.size())
			return;

		m_BasePositions.erase(m_BasePositions.begin() + index);
	}
}
