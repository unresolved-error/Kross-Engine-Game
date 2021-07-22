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
		ImVec2 viewsize = ImVec2(viewSize.x * 0.2f, viewSize.y);

		Vector2 viewPos = Editor::GetViewportPosition();
		ImVec2 viewposition = ImVec2(viewPos.x + (viewSize.x - viewsize.x), viewPos.y);

		
		if (p_SelectedObject)
		{
			m_Title = p_SelectedObject->GetName() + " editor panel.";
		}
		else 
		{
			m_Title = "No Object Selected.";
		};
		

		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

		ImGui::SetWindowPos(viewposition);
		ImGui::SetWindowSize(viewsize);
		
		ImGui::BeginTabBar("Object Tab Bar");
		if (ImGui::BeginTabItem("Component Hierarchy"))
		{
			if (p_SelectedObject) {
				for (int i = 0; i < p_SelectedObject->m_Components.size(); i++)
				{

					if (typeid(*p_SelectedObject->m_Components[i]) == typeid(Transform2D))
					{
						Transform2D* transform = p_SelectedObject->GetComponent<Transform2D>();
						Vector2 pos = transform->m_Position;

						if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
						{
							ImGui::PushID("Position");
							ImGui::Columns(2);
							ImGui::SetColumnWidth(0, 70.0f);
							ImGui::Text("Position");
							ImGui::NextColumn();

							ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
							if (ImGui::Button("X"))
								pos.x = 0.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##X", &pos.x, 0.1f, FLT_MIN, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::SameLine();

							if (ImGui::Button("Y"))
								pos.y = 0.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##Y", &pos.y, 0.1f, FLT_MIN, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::SameLine();
							ImGui::PopID();


							transform->m_Position = pos;

						}
					}
					//else if component is type.... else if component is...


				}
			}
		}
		ImGui::EndTabItem();

		ImGui::EndTabBar();


		ImGui::End();
		
	}

	void ObjectEditor::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_::ImGuiWindowFlags_NoMove;
	}

	void ObjectEditor::OnStart()
	{
		SetFlags();
		m_Title = "Object Editor."; //placeholder title for safety.

	}
}