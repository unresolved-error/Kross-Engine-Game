/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../../Core.h"
#include "../EditorWindow.h"

namespace Kross
{
	class KROSS_API MainMenu : public EditorWindow
	{
	public:

		MainMenu() :
			p_SelectedObject (nullptr)
		{};

		~MainMenu() {};

		void SetSelectedObject(Object* object) { p_SelectedObject = object; };

	private:
		Object* p_SelectedObject;

	protected:
		friend class SceneHierarchy;
		friend class Editor;

		void Attach() override;

		void SetFlags() override;

		void OnStart() override;
	};
}
