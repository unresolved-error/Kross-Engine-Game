/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

namespace Kross
{
	enum class KROSS_API TileType
	{
		/* TILE KEY */
		/* 
			X = Current.
			Numerical Values = Connections.

			+---+---+---+
			| 0 | 1 | 2 |
			+---+---+---+
			| 3 | X | 4 |
			+---+---+---+
			| 5 | 6 | 7 |
			+---+---+---+
		*/

		TopLeft,
		/*	- Connections: 4, 6, 7. */

		TopCenter,
		/*	- Connections: 3, 4, 5, 6, 7. */

		TopRight,
		/*	- Connections: 3, 5, 6. */

		CenterLeft,
		/*	- Connections: 1, 2, 4, 6, 7. */

		Center,
		/*	- Connections: 0, 1, 2, 3, 4, 5, 6, 7. */

		CenterRight,
		/*	- Connections: 0, 1, 3, 5, 6. */

		BottomLeft,
		/*	- Connections: 1, 2, 4. */

		BottomCenter,
		/*	- Connections: 0, 1, 2, 3, 4. */

		BottomRight,
		/*	- Connections: 0, 1, 3. */

		TopLeftSingle,
		/*	- Connections: 4, 6. */

		TopCenterSingle,
		/*	- Connections: 3, 4. */

		Single,
		/*	- Connections: N/A. */

		CenterSingle,
		/*	- Connections: 1, 3, 4, 6. */
	};


	enum class KROSS_API TileStatus
	{
		Empty,
		Full,
	};
}