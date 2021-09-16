/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"
#include "../../Layer.h"
#include "../Utility/Folder.h"

namespace Kross
{
	class KROSS_API SceneHierarchy : public EditorWindow
	{
	private:
		Object* p_SelectedObject;
		std::vector<Folder<Object>*> m_Folders;
		std::vector<Object*> m_FolderlessObjects;

		Folder<Object>* m_Folder = nullptr;
		bool m_EditFolder = false;

		Object* m_FolderObject = nullptr;
		bool m_EditFolderObject = false;

	protected:
		template<typename Type> friend class Serialiser;

		// Sets the Scene Hierarchy Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;

	public:
		SceneHierarchy() :
			p_SelectedObject	(nullptr),
			m_Folders			(std::vector<Folder<Object>*>()),
			m_FolderlessObjects	(std::vector<Object*>())
		{};

		~SceneHierarchy() {};
	};
}