/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#include "SceneHierarchy.h"

#include "../../Input.h"
#include "../Editor.h"

#include "../../Debug.h"

namespace Kross
{
	void SceneHierarchy::SetFlags()
	{
		m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	}

	void SceneHierarchy::OnStart()
	{
		/* Sets the Flags. */
		SetFlags();

		m_Title = "Scene Panel";
	}

	void SceneHierarchy::Attach()
	{
		Vector2 viewPosition = Editor::GetViewportPosition();
		ImVec2 position = ImVec2(viewPosition.x, viewPosition.y);

		Vector2 viewSize = Editor::GetViewportSize();
		ImVec2 size = ImVec2(viewSize.x * 0.2f, viewSize.y * 0.7f);

		ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

		ImGui::SetWindowPos(position);
		ImGui::SetWindowSize(size);

			ImGui::BeginTabBar("Scene Tab Bar");

				if (ImGui::BeginTabItem("Object Hierarchy"))
				{
					/* If we have a scene. (Should always exist) */
					if (p_Scene)
					{
						for (int i = 0; i < p_Scene->m_ActualObjects.size(); i++)
						{
							Object* object = p_Scene->m_ActualObjects[i];

							/* works. */
							if (ImGui::MenuItem(object->GetName().c_str(), "", (object == p_SelectedObject), object->Enabled()));
							{
								if (ImGui::IsItemHovered() && Input::GetMouseButtonPressed(Mouse::Left))
								{
									if (object != p_SelectedObject)
									{
										p_SelectedObject = object;
										Editor::SetObjectEditorObject(p_SelectedObject);
										Editor::SetMainMenuObject(p_SelectedObject);
									}
								}
							}
						}

						if (ImGui::BeginCombo("##AddObject", "Add Object", ImGuiComboFlags_NoArrowButton))
						{
							if (ImGui::MenuItem("Empty"))
							{
								// TODO: Blank Objects.
							}
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
						char name[50]{ '\0' };
						for (int i = 0; i < p_Scene->GetName().size(); i++)
						{
							name[i] = p_Scene->GetName()[i];
						}
						if (ImGui::InputTextEx("##Name", p_Scene->GetName().c_str(), &name[0], sizeof(name), ImVec2(0.0f, 0.0f), ImGuiInputTextFlags_EnterReturnsTrue))
						{
							p_Scene->SetName((std::string)name);
						}

						ImGui::Spacing();

						ImGui::SetWindowFontScale(1.5f);
						ImGui::Text("Gravity");
						ImGui::Spacing();
						ImGui::SetWindowFontScale(1.0f);

						ImGui::Text("Scale:");
						float gravity = p_Scene->GetGravityScalar();
						ImGui::SliderFloat("##Gravity", &gravity, 0.001f, 100.0f);

						ImGui::Spacing();

						ImGui::Text("Direction:");
						Vector2 direction = p_Scene->GetGravityDirection();
						float values[2]{ direction.x, direction.y };
						ImGui::SliderFloat2("##Gravity-Direction", &values[0], -1.0f, 1.0f);
						direction.x = values[0];
						direction.y = values[1];

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