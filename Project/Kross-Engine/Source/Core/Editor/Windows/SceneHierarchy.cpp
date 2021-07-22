/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SceneHierarchy.h"

#include "../../Input.h"
#include "../Editor.h"

namespace Kross
{
	void SceneHierarchy::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_NoCollapse;// | ImGuiWindowFlags_NoTitleBar;
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
		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

			ImGui::BeginTabBar("Scene Tab Bar");

				if (ImGui::BeginTabItem("Object Hierarchy"))
				{
					/* If we have a scene. (Should always exist) */
					if (p_Scene)
					{
						if (ImGui::TreeNodeEx(p_Scene->GetName().c_str()))
						{
							for (int i = 0; i < p_Scene->m_ActualObjects.size(); i++)
							{
								Object* object = p_Scene->m_ActualObjects[i];

								if (ImGui::TreeNodeEx(object->GetName().c_str(), (object == p_SelectedObject) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf));
								{
									if (ImGui::IsItemHovered() && Input::GetMouseButtonPressed(Mouse::Left))
									{
										if (object != p_SelectedObject)
										{
											p_SelectedObject = object;
											Editor::SetObjectEditorObject(p_SelectedObject);
										}
									}

									ImGui::TreePop();
								}
							}
							ImGui::TreePop();
						}	
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Scene Properties"))
				{
					ImGui::EndTabItem();
				}

				if (p_SelectedObject && Input::GetKeyPressed(Key::Delete))
				{
					if (p_Scene)
					{
						p_Scene->DetachObject(p_SelectedObject);
						p_SelectedObject = nullptr;
						Editor::SetObjectEditorObject(nullptr);
					}
				}

			ImGui::EndTabBar();

		ImGui::End();
	}
}