/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"
#include "AssetType.h"

namespace Kross
{
	class KROSS_API AssetDirectory : public EditorWindow
	{
	private:
		AssetType m_Type;
		AssetTypeName m_TypeNames;
		std::string m_TypeSelected;

	protected:

	public:
		AssetDirectory() :
			m_Type			(AssetType::None),
			m_TypeNames		(AssetTypeName()),
			m_TypeSelected	("None")
		{};
		~AssetDirectory() {};

		// Sets the Asset Directory Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;


	};
}
