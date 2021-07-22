/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */
#include "ObjectEditor.h"

#include "../Editor.h"

namespace Kross {

	void ObjectEditor::Attach()
	{
		Vector2 viewSize = Editor::GetViewportSize();
		ImVec2 size = ImVec2(viewSize.x * 0.2f, viewSize.y);

		Vector2 viewPos = Editor::GetViewportPosition();
		ImVec2 position = ImVec2(viewPos.x + (viewSize.x - size.x), viewPos.y);

		


		

		if (p_SelectedObject)
		{
			m_Title = p_SelectedObject->GetName() + " editor panel.";
		}
		else 
		{
			m_Title = "No Object Selected.";
		};
		

		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);
		ImGui::SetWindowPos(position);
		ImGui::SetWindowSize(size);
		ImGui::End();
		
	}

	void ObjectEditor::SetFlags()
	{
		//m_WindowFlags = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
	}

	void ObjectEditor::OnStart()
	{
		SetFlags();
		m_Title = "Object Editor."; //placeholder title for safety.

	}
}