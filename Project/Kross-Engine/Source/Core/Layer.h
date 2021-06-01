/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

namespace Kross
{
	// Used for Rendering Objects. (LAST TO FIRST. NOTE! THESE ARE ADDED ENGINE SIDE!) 
	enum class KROSS_API Layer
	{
		/* Layers. */
		None,
		Default,
		Light,
		Player,
		Environment,
		Background,
		
		Wall,
		Ground,

		/* Important Layers. (DO NOT REMOVE) */
		Fluids,
		UI,

		/* Layer Count. */
		Count,
	};
}