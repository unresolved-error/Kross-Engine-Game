/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Math.h"

namespace Kross
{
	float Math::Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
}