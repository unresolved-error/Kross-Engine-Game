/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */
#include "ObjectEditor.h"

#include "../Editor.h"
#include "../../Debug.h"

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
						float posX = transform->m_Position.x, posY = transform->m_Position.y;

						if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
						{
							ImGui::PushID("Position");
							ImGui::Columns(2);
							ImGui::SetColumnWidth(0, 70.0f);
							ImGui::Text("Position");
							ImGui::NextColumn();

							ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
							if (ImGui::Button("X"))
								transform->m_Position.x = 0.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##X", &transform->m_Position.x, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::SameLine();

							if (ImGui::Button("Y"))
								transform->m_Position.y = 0.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##Y", &transform->m_Position.y, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::Columns(1);
							ImGui::PopID();

							ImGui::PushID("Rotation");
							ImGui::Columns(2);
							ImGui::SetColumnWidth(0, 70.0f);
							ImGui::Text("Rotation");
							ImGui::NextColumn();

							ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
							if (ImGui::Button("0"))
								transform->m_Rotation = 0.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##R", &transform->m_Rotation, 0.1f, 0.0f, 360.0f, "%.2fd");
							ImGui::PopItemWidth();
							ImGui::SameLine();

							ImGui::PopItemWidth();
							ImGui::Columns(1);
							ImGui::PopID();

							ImGui::PushID("Scale");
							ImGui::Columns(2);
							ImGui::SetColumnWidth(0, 70.0f);
							ImGui::Text("Scale");
							ImGui::NextColumn();

							ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
							if (ImGui::Button("X"))
								transform->m_Scale.x = 1.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##X", &transform->m_Scale.x, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::SameLine();

							if (ImGui::Button("Y"))
								transform->m_Scale.y = 1.0f;

							ImGui::SameLine();

							ImGui::DragFloat("##Y", &transform->m_Scale.y, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");
							ImGui::PopItemWidth();
							ImGui::Columns(1);
							ImGui::PopID();


						}
					}
					
					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(Rigidbody2D))
					{
						Rigidbody2D* rb = p_SelectedObject->GetComponent<Rigidbody2D>();
						TileMapRenderer* tm = p_SelectedObject->GetComponent<TileMapRenderer>();

						if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen))
						{
							if (tm)
							{
								if (ImGui::Button("Generate Colliders!"))
								{
									rb->DeleteTileMapColliders();
									rb->CreateTileMapColliders(tm->GetTileMap(), tm->GetTileList()[0]);
								}
							}
						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(Animator))
					{
						Animator* anim = p_SelectedObject->GetComponent<Animator>();
						if (ImGui::CollapsingHeader("Animator", ImGuiTreeNodeFlags_DefaultOpen))
						{
						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(AudioPlayer))
					{
						AudioPlayer* aplayer = p_SelectedObject->GetComponent<AudioPlayer>();
						if (ImGui::CollapsingHeader("AudioPlayer", ImGuiTreeNodeFlags_DefaultOpen)) 
						{
						
						}

					}
					
					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(Camera))
					{
						Camera* cam = p_SelectedObject->GetComponent<Camera>();
						if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
						{
							float c_size = cam->GetSize();
							float c_near = cam->GetNear();
							float c_far = cam->GetFar();

							ImGui::Text("Size");
							ImGui::SameLine();
							ImGui::DragFloat("##S", &c_size, 0.1f, 0.5f, 40.0f, "%.2fm");
							ImGui::Text("Near");
							ImGui::SameLine();
							ImGui::DragFloat("##N", &c_near, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");
							ImGui::Text("Far");
							ImGui::SameLine();
							ImGui::DragFloat("##F", &c_far, 0.1f, -FLT_MAX, FLT_MAX, "%.2fm");

							cam->SetSize(c_size);
							cam->SetFar(c_far);
							cam->SetNear(c_near);

							if (ImGui::Button("Reset Default")) {
								cam->SetSize(5.0f);
								cam->SetFar(1.0f);
								cam->SetNear(-1.0f);
							}


						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(ParticleEmitter))
					{
						ParticleEmitter* pEmit = p_SelectedObject->GetComponent<ParticleEmitter>();
						if (ImGui::CollapsingHeader("ParticleEmitter", ImGuiTreeNodeFlags_DefaultOpen))
						{
						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(SpriteRenderer))
					{
						SpriteRenderer* rend = p_SelectedObject->GetComponent<SpriteRenderer>();
						if (ImGui::CollapsingHeader("SpriteRenderer", ImGuiTreeNodeFlags_DefaultOpen))
						{
							Vector4 col = rend->GetColour();
							float s_col[4] = { col.r, col.g, col.b, col.a };
							Material* s_mat = rend->GetMaterial();
							bool s_fx = rend->GetFlipX();
							bool s_fy = rend->GetFlipY();

							ImGui::Text("Flip X/Y");
							ImGui::SameLine();
							if (ImGui::Button("X")) {
								s_fx = (!rend->GetFlipX());
							}
							ImGui::SameLine();
							if (ImGui::Button("Y")) 
							{
								s_fy = (!rend->GetFlipY());
							}
							ImGui::Text("	");
							ImGui::SameLine();

							if (ImGui::CollapsingHeader(((rend->GetMaterial()) ? (std::string)(rend->GetMaterial()->GetName() + " - Material").c_str() : "Material").c_str(), ImGuiTreeNodeFlags_DefaultOpen) && rend->GetMaterial())
							{
								
								std::string m_text = rend->GetMaterial()->GetName();
								char m_cha[1024]{ '/0' };
								strncpy_s(m_cha, m_text.c_str(), 1024);



								ImGui::Text("	");
								ImGui::SameLine();

								ImGui::Text("Name");
								
								ImGui::Text("	");
								ImGui::SameLine();

								ImGui::InputText("##T", &m_cha[0], 1024);
								std::string toSet = m_cha;
								rend->GetMaterial()->SetName(toSet);


								ImGui::Text("	");
								ImGui::SameLine();
								ImGui::Text("Diffuse");
								/*TODO ASSET HANDLER*/

								ImGui::Text("	");
								ImGui::SameLine();
								ImGui::Text("Normal");
								/*TODO ASSET HANDLER*/

								ImGui::Text("	");
								ImGui::SameLine();
								ImGui::Text("Specular");
								/*TODO ASSET HANDLER*/

							}


							ImGui::Text("Colour");
							ImGui::ColorPicker4("##C", s_col);
							col = Vector4{ s_col[0],s_col[1], s_col[2], s_col[3] };


							rend->SetColour(col);
							rend->SetFlipX(s_fx);
							rend->SetFlipY(s_fy);
						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(TextRenderer))
					{
						TextRenderer* rend = p_SelectedObject->GetComponent<TextRenderer>();
						if (ImGui::CollapsingHeader("TextRenderer", ImGuiTreeNodeFlags_DefaultOpen))
						{
							Font* t_font = rend->GetFont();
							float t_size = rend->GetTextSize();
							std::string t_text = rend->GetText();
							Vector4 col = rend->GetColour();
							float t_col[4] = { col.r, col.g, col.b, col.a };

							char t_cha[1024]{'/0'};
							strncpy_s(t_cha, t_text.c_str(),1024);
							

							ImGui::Text("Text");
							ImGui::InputText("##T", &t_cha[0], 1024);


							ImGui::Text("Font");
							/*TODO ASSET HANDLER*/

							ImGui::Text("Colour");
							ImGui::ColorPicker4("##C", t_col);

							ImGui::Text("Size");
							ImGui::SameLine();
							ImGui::DragFloat("##S", &t_size, 0.1f, 0.5f, 40.0f, "%.2fm");


							col = Vector4{t_col[0],t_col[1], t_col[2], t_col[3]};

							
							std::string toSet = t_cha;

							rend->SetText(toSet);
							rend->SetColour(col);
							rend->SetFont(t_font);
							rend->SetTextSize(t_size);


						}
					}

					else if (typeid(*p_SelectedObject->m_Components[i]) == typeid(TileMapRenderer))
					{
						TileMapRenderer* rend = p_SelectedObject->GetComponent<TileMapRenderer>();
						if (ImGui::CollapsingHeader("TileMapRenderer", ImGuiTreeNodeFlags_DefaultOpen))
						{

						}
					}

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