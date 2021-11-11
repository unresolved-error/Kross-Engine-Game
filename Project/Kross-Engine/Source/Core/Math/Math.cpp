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

	Vector2 Math::Lerp(Vector2 a, Vector2 b, float t)
	{
		return Vector2(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
	}
	Vector4 Math::Lerp(Vector4 a, Vector4 b, float t)
	{
		return Vector4(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z), a.w + t * (b.w - a.w));
	}
}