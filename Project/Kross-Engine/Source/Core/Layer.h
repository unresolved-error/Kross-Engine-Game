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
		Background,
		Background1,
		Background2,
		Background3,
		Background4,
		Background5,
		Background6,
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
			m_Names.push_back("Background");
			m_Names.push_back("Background1");
			m_Names.push_back("Background2");
			m_Names.push_back("Background3");
			m_Names.push_back("Background4");
			m_Names.push_back("Background5");
			m_Names.push_back("Background6");

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