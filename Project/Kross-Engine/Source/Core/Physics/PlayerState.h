/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	/* Enum class for player states */
	enum class KROSS_API PlayerState
	{
		Idle,
		Walking,
		Running,
		Jumping,
		Falling,
		Swimming,
		Count
	};
}