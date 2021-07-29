/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

namespace Kross
{
	// Used for Rendering Objects. (FIRST TO LAST. NOTE! THESE ARE ADDED ENGINE SIDE!) 
	enum class KROSS_API Layer
	{
		/* Layers. */
		Default,
		Light,
		Environment,
		Background,
		
		Wall,
		Ground,
		Player,

		/* Important Layers. (DO NOT REMOVE) */
		Fluids,
		UI,

		/* Layer Count. */
		Count,

		None,
	};
}