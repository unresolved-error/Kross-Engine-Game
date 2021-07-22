/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */
#include "ObjectEditor.h"

namespace Kross {

	void ObjectEditor::Attach()
	{
		if (p_SelectedObject)
		{
			m_Title = p_SelectedObject->GetName() + " editor panel.";
		}
		else 
		{
			m_Title = "No Object Selected.";
		};
		

		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);
		ImGui::End();
		
	}

	void ObjectEditor::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
	}

	void ObjectEditor::OnStart()
	{
		SetFlags();
		m_Title = "Object Editor."; //placeholder title for safety.

	}
}