/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

namespace Kross
{
	enum class KROSS_API TextureType
	{
		TextureMap,
		NormalMap,
		SpecularMap,

		PerlinMap,

		// Font Texture.
		FontMap
	};
}