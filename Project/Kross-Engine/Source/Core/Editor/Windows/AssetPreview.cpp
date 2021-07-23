#include "AssetPreview.h"

#include "../Editor.h"
#include "../../Input.h"
#include "../../Debug.h"

namespace Kross
{

	void AssetPreview::SetFlags()
	{
		/* Set the Flags Appropriate. */
		m_WindowFlags = ImGuiWindowFlags_NoCollapse;
	}

	void AssetPreview::OnStart()
	{
		/* Set the Flags. */
		SetFlags();

		/* Set Title. */
		m_Title = "Asset Selector";
	}

	void AssetPreview::Attach()
	{
		Vector2 viewPosition = Editor::GetViewportPosition();
		ImVec2 position = ImVec2(viewPosition.x, viewPosition.y);

		Vector2 viewSize = Editor::GetViewportSize();
		ImVec2 size = ImVec2(viewSize.x * 0.2f, viewSize.y);

		if (m_IsOpen)
		{
			ImGui::Begin(m_Title.c_str(), &m_IsOpen, m_WindowFlags);

			if (!m_WindowVarSet)
			{
				ImGui::SetWindowPos(position);
				ImGui::SetWindowSize(size);
				m_WindowVarSet = true;
			}

			switch (m_Type)
			{
			case Kross::AssetType::None:
			{
				break;
			}

			case Kross::AssetType::Sprite:
			{
				if (ImGui::TreeNodeEx("Sprites"))
				{
					for (int i = 0; i < ResourceManager::s_Instance->m_Sprites.size(); i++)
					{
						Sprite* sprite = ResourceManager::s_Instance->m_Sprites[i];

						if (ImGui::TreeNodeEx(sprite->GetName().c_str(), (sprite == p_SelectedSprite) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf));
						{
							if (ImGui::IsItemHovered() && Input::GetMouseButtonPressed(Mouse::Left))
							{
								if (sprite != p_SelectedSprite)
								{
									p_SelectedSprite = sprite;
									Debug::LogLine(sprite->GetName() + " is Selected!");
								}
							}

							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
				break;
			}

			case Kross::AssetType::Texture:
			{
				break;
			}

			case Kross::AssetType::Material:
			{
				break;
			}

			case Kross::AssetType::Font:
			{
				break;
			}

			case Kross::AssetType::Animation:
			{
				break;
			}

			case Kross::AssetType::AudioSource:
			{
				break;
			}

			case Kross::AssetType::TileMap:
			{
				break;
			}

			case Kross::AssetType::TileSet:
			{
				break;
			}

			default:
			{
				break;
			}
			}

			ImGui::End();
		}
	}
	void AssetPreview::SetAssetDestination(Sprite* destination)
	{
		p_DestinationSprite = destination;
		p_SelectedSprite = nullptr;
	}
}
