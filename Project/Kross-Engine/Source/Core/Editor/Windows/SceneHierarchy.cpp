/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SceneHierarchy.h"

#include "../../Input.h"
#include "../Editor.h"

#include "../../Debug.h"

namespace Kross
{
	void SceneHierarchy::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
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
		Vector2 viewPosition = Editor::GetViewportPosition();
		ImVec2 position = ImVec2(viewPosition.x, viewPosition.y);

		Vector2 viewSize = Editor::GetViewportSize();
		ImVec2 size = ImVec2(viewSize.x * 0.2f, viewSize.y);

		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

		ImGui::SetWindowPos(position);
		ImGui::SetWindowSize(size);

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
					if (p_Scene)
					{
						ImGui::SetWindowFontScale(1.5f);
						ImGui::Text(p_Scene->GetName().c_str());
						ImGui::Spacing();
						ImGui::SetWindowFontScale(1.0f);

						ImGui::Text("Name:");
						char name[50];
						ImGui::PushID("Name Input");
						if (ImGui::InputTextEx("", p_Scene->GetName().c_str(), &name[0], sizeof(name), ImVec2(0.0f, 0.0f), ImGuiInputTextFlags_EnterReturnsTrue))
						{
							p_Scene->SetName((std::string)name);
						}
						ImGui::PopID();

						ImGui::Spacing();

						ImGui::SetWindowFontScale(1.5f);
						ImGui::Text("Gravity");
						ImGui::Spacing();
						ImGui::SetWindowFontScale(1.0f);

						ImGui::Text("Scale:");
						ImGui::PushID("Gravity Scale");
						float gravity = p_Scene->GetGravityScalar();
						Debug::Log(gravity);
						ImGui::DragFloat("", &gravity, 0.05f, FLT_MIN, FLT_MAX);

						ImGui::PopID();

						ImGui::Spacing();

						ImGui::Text("Direction:");
						ImGui::PushID("Gravity Direction");
						Vector2 direction = p_Scene->GetGravityDirection();
						Debug::Log(direction);
						ImGui::DragFloat("", &direction.x, 0.05f, -1.0f, 1.0f);

						ImGui::PopID();

						p_Scene->SetGravity(gravity, direction);
					}

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