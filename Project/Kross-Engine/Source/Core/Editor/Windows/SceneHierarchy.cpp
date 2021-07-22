/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SceneHierarchy.h"

namespace Kross
{
	void SceneHierarchy::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	}

	void SceneHierarchy::OnStart()
	{
		/* Sets the Flags. */
		SetFlags();

		m_Title = "Scene Panel";
		m_Width = 120;
		m_Height = 23045;
	}

	void SceneHierarchy::Attach()
	{
		ImGui::Begin(m_Title.c_str(), (bool*)true, m_WindowFlags);
		ImGui::End();
	}
}