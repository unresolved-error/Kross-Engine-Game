/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"

namespace Kross
{
	class KROSS_API SceneHierarchy : public EditorWindow
	{
	private:
		Object* p_SelectedObject;

	protected:
		// Sets the Scene Hierarchy Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;

	public:
		SceneHierarchy() :
			p_SelectedObject(nullptr)
		{};

		~SceneHierarchy() {};
	};
}