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
		m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize;
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
				//for (int l = 0; l < (int)Layer::Count; l++)
				//{
				//	LayerName names = LayerName();
				//	std::string label = "[" + names[l] + "]";
				//
				//	std::vector<Object*> layerObjects;
				//
				//	for (int i = 0; i < p_Scene->m_ActualObjects.size(); i++)
				//	{
				//		Object* object = p_Scene->m_ActualObjects[i];
				//
				//		if (object->GetLayer() == (Layer)l)
				//		{
				//			layerObjects.push_back(object);
				//		}
				//	}
				//
				//	if (ImGui::TreeNodeEx(label.c_str(), (layerObjects.size() == 0) ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_None))
				//	{
				//		ImGui::Indent();
				//		for(int i = 0; i < layerObjects.size(); i++)
				//		{
				//			Object* object = layerObjects[i];
				//			/* works. */
				//			if (ImGui::MenuItem(object->GetName().c_str(), "", (object == p_SelectedObject), object->Enabled()));
				//			{
				//				if (ImGui::IsItemHovered() && Input::GetMouseButtonPressed(Mouse::Left))
				//				{
				//					if (object != p_SelectedObject)
				//					{
				//						p_SelectedObject = object;
				//						Editor::SetObjectEditorObject(p_SelectedObject);
				//						Editor::SetMainMenuObject(p_SelectedObject);
				//					}
				//				}
				//			}
				//		}
				//		ImGui::Unindent();
				//		ImGui::TreePop();
				//
				//		if(layerObjects.size() != 0)
				//			ImGui::Spacing();
				//	}
				//}
				ImGui::BeginChild("##ObjectHierarchyMenuBar", ImVec2(0.0f, 20.0f), false, ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::MenuItem("Create"))
					{
						Folder<Object>* folder = KROSS_NEW Folder<Object>();
						folder->SetName("New Folder");
						m_Folders.push_back(folder);
					}
					ImGui::EndMenuBar();
				}
				ImGui::EndChild();
				for (int i = 0; i < p_Scene->m_ActualObjects.size(); i++)
				{
					Object* object = p_Scene->m_ActualObjects[i];
					bool isFolderless = true;
					for (int f = 0; f < m_Folders.size(); f++)
					{
						for (int c = 0; c < m_Folders[f]->m_Contents.size(); c++)
						{
							if (m_Folders[f]->m_Contents[c] == object)
								isFolderless = false;
						}
					}

					if (isFolderless)
						m_FolderlessObjects.push_back(object);
				}

				for (int f = 0; f < m_Folders.size(); f++)
				{
					std::string folderName = "[Folder] " + m_Folders[f]->GetName();

					if(ImGui::TreeNode(folderName.c_str()))
					{
						ImGui::Indent();
						for (int c = 0; c < m_Folders[f]->m_Contents.size(); c++)
						{
							if (ImGui::MenuItem(m_Folders[f]->m_Contents[c]->GetName().c_str(), "", p_SelectedObject == m_Folders[f]->m_Contents[c], m_Folders[f]->m_Contents[c]->Enabled()))
							{
							
								if (m_Folders[f]->m_Contents[c] != p_SelectedObject)
								{
									p_SelectedObject = m_Folders[f]->m_Contents[c];
									Editor::SetObjectEditorObject(p_SelectedObject);
									Editor::SetMainMenuObject(p_SelectedObject);
								}
								
							}
						}
						ImGui::Unindent();
						ImGui::TreePop();
					}

					if (ImGui::IsItemHovered())
					{
						if (Input::GetMouseButtonPressed(Mouse::Right))
						{
							m_Folder = m_Folders[f];
							ImGui::OpenPopup(m_Folder->GetName().c_str());
						}
					}

					if (m_Folder && m_Folder == m_Folders[f] && ImGui::BeginPopup(m_Folder->GetName().c_str()))
					{
						ImGui::Text((m_Folder->GetName() + " Properties").c_str());
						ImGui::Separator();

						if (!m_EditFolder)
						{
							ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
							if (ImGui::MenuItem("Rename"))
							{
								m_EditFolder = true;
							}
							ImGui::PopItemFlag();
						}
						else
						{
							char buffer[64] = { '\0' };
							for (int i = 0; i < m_Folder->GetName().length(); i++)
							{
								buffer[i] = m_Folder->GetName()[i];
							}

							if (ImGui::InputText("##FolderName", &buffer[0], 64, ImGuiInputTextFlags_EnterReturnsTrue))
							{
								m_Folder->SetName(buffer);
								m_EditFolder = false;
							}
						}

						if(ImGui::MenuItem("Remove"))
						{
							delete m_Folders[f];
							m_Folders[f] = nullptr;
							m_Folders.erase(m_Folders.begin() + f);
							m_Folder = nullptr;
						}
						ImGui::EndPopup();
					}
					else if(!m_Folder)
					{
						m_EditFolder = false;
					}
				}

				for (int i = 0; i < m_FolderlessObjects.size(); i++)
				{
					if (ImGui::MenuItem(m_FolderlessObjects[i]->GetName().c_str(), "", p_SelectedObject == m_FolderlessObjects[i], m_FolderlessObjects[i]->Enabled()))
					{
						if (m_FolderlessObjects[i] != p_SelectedObject)
						{
							p_SelectedObject = m_FolderlessObjects[i];
							Editor::SetObjectEditorObject(p_SelectedObject);
							Editor::SetMainMenuObject(p_SelectedObject);
						}
						
					}

					if (ImGui::IsItemHovered())
					{
						if (Input::GetMouseButtonPressed(Mouse::Right))
						{
							m_FolderObject = m_FolderlessObjects[i];
							ImGui::OpenPopup(m_FolderObject->GetName().c_str());
						}
					}

					if (m_FolderObject && m_FolderObject == m_FolderlessObjects[i] && ImGui::BeginPopup(m_FolderObject->GetName().c_str()))
					{
						ImGui::Text((m_FolderObject->GetName()).c_str());
						ImGui::Separator();

						if (!m_EditFolderObject)
						{
							ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
							if (ImGui::MenuItem("Rename"))
							{
								m_EditFolderObject = true;
							}
							ImGui::PopItemFlag();
						}
						else
						{
							char buffer[64] = { '\0' };
							for (int i = 0; i < m_FolderObject->GetName().length(); i++)
							{
								buffer[i] = m_FolderObject->GetName()[i];
							}

							if (ImGui::InputText("##FolderName", &buffer[0], 64, ImGuiInputTextFlags_EnterReturnsTrue))
							{
								m_FolderObject->SetName(buffer);
								m_EditFolderObject = false;
							}
						}

						if (ImGui::BeginMenu("Place in Folder.."))
						{
							for (int f = 0; f < m_Folders.size(); f++)
							{
								if (ImGui::MenuItem(m_Folders[f]->GetName().c_str()))
								{
									m_Folders[f]->Push(m_FolderObject);
									m_FolderObject = nullptr;
								}
							}
							ImGui::EndMenu();
						}
						ImGui::EndPopup();
					}
					else if (!m_Folder)
					{
						m_EditFolder = false;
					}
				}

				for (int i = 0; i < m_FolderlessObjects.size(); i++)
				{
					m_FolderlessObjects[i] = nullptr;
				}
				m_FolderlessObjects.clear();
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