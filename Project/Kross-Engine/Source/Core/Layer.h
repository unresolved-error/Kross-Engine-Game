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
		/*THE HIGHER THE BACKGROUND LAYER, THE CLOSER IT IS.*/
		FurthestBackground,
		SecondFurthestBackground,
		ThirdFurthestBackground,
		FourthFurthestBackground,
		ThirdCloseBackground,
		SecondCloseBackground,
		CloseBackground,
		Wall,
		Ground,
		Player,

		/* Important Layers. (DO NOT REMOVE) */
		Fluids,
		ForeGround,
		UI,

		/* Layer Count. */
		Count,

		None,
	};

	const struct KROSS_API LayerName
	{
	private:
		List<std::string> m_Names;

	public:
		LayerName()
		{
			m_Names.push_back("Default");
			m_Names.push_back("Light");
			m_Names.push_back("Environment");
			m_Names.push_back("Furthest");
			m_Names.push_back("SecondFurthestBackground");
			m_Names.push_back("ThirdFurthestBackground");
			m_Names.push_back("FourthFurthestBackground");
			m_Names.push_back("ThirdCloseBackground");
			m_Names.push_back("SecondCloseBackground");
			m_Names.push_back("CloseBackground");

			m_Names.push_back("Wall");
			m_Names.push_back("Ground");
			m_Names.push_back("Player");
			m_Names.push_back("Fluids");

			m_Names.push_back("Foreground");
			
			m_Names.push_back("UI");

			m_Names.push_back("None");
		}

		std::string operator [](int index)
		{
			if (index < 0 && index >= m_Names.size())
				return std::string();

			return m_Names[index];
		}
	};
}