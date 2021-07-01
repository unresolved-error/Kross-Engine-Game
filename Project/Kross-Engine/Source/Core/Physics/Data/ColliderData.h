/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once


#include "../../Core.h"
#include "../Physics.h"

namespace Kross
{
	struct KROSS_API ColliderData
	{
		Vector2 normal = { 0,0 };
		float depth = -1;

		Vector2 position = { 0,0 };
	};
}