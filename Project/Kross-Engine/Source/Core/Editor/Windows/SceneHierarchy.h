/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"
#include "../../Layer.h"

namespace Kross
{
	class KROSS_API SceneHierarchy : public EditorWindow
	{
	private:
		Object* p_SelectedObject;
		List<bool> m_ViewLayer;

	protected:
		// Sets the Scene Hierarchy Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;

	public:
		SceneHierarchy() :
			p_SelectedObject	(nullptr),
			m_ViewLayer			(List<bool>((int)Layer::Count))
		{};

		~SceneHierarchy() {};
	};
}