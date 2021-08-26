/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	enum KROSS_API KeyframeDataFlags
	{
		Empty = 0,
		PositionData = 1 << 0,
		RotationData = 1 << 1,
		ScaleData = 1 << 2,
		SpriteData = 1 << 3,
	};
}