/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "AssetPreview.h"

#include "../Editor.h"
#include "../../Debug.h"

namespace Kross
{
	AssetPreview::AssetPreview()
	{
		/* Has to be here for the Compiler to not have a fit. */
		m_Width =					0.0f;
		m_Height =					0.0f;
		m_PositionX =				0.0f;
		m_PositionY =				0.0f;
		m_WindowVarSet =			false;
		m_IsOpen =					true;
		m_Type =					AssetType::None;
		p_SelectedSprite =			nullptr;
		p_SelectedTexture =			nullptr;
		p_SelectedMaterial =		nullptr;
		p_SelectedFont =			nullptr;
		p_SelectedAnimation =		nullptr;
		p_SelectedAudioSource =		nullptr;
		p_SelectedTileMap =			nullptr;
		p_SelectedTileSet =			nullptr;
		p_DestinationSprite =		nullptr;
		p_DestinationTexture =		nullptr;
		p_DestinationMaterial =		nullptr;
		p_DestinationFont =			nullptr;
		p_DestinationAnimation =	nullptr;
		p_DestinationAudioSource =	nullptr;
		p_DestinationTileMap =		nullptr;
		p_DestinationTileSet =		nullptr;
	}

	void AssetPreview::SetFlags()
	{
		/* Set the Appropriate Flags. */
		m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
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
		/* Safe Guard to make sure ImGui doesn't try to render a closed window. */
		if (m_IsOpen)
		{
			ImGui::Begin(m_Title.c_str(), &m_IsOpen, m_WindowFlags);

			/* If the Window Variables for Position and Size haven't been set.*/
			if (!m_WindowVarSet)
			{
				/* Get the Position and Size. */
				ImVec2 position = ImVec2(m_PositionX, m_PositionY);
				ImVec2 size = ImVec2(m_Width, m_Height);

				/* Set them. */
				ImGui::SetWindowPos(position);
				ImGui::SetWindowSize(size);

				/* We have Set the Variables. */
				m_WindowVarSet = true;
			}

			/* See what Type to Display. */
			switch (m_Type)
			{
				case Kross::AssetType::None:
				{
					break;
				}
				case Kross::AssetType::Sprite:
				{
					/* Start the Sprite Tree. */
					if (ImGui::TreeNodeEx("Sprites"))
					{
						/* Go through all of the Sprites. */
						for (int i = 0; i < ResourceManager::m_Instance->m_Sprites.size(); i++)
						{
							/* Current Sprite being looked at. */
							Sprite* sprite = ResourceManager::m_Instance->m_Sprites[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Sprite is the Selected One. */
							if (ImGui::TreeNodeEx(sprite->GetName().c_str(), (sprite == p_SelectedSprite) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (sprite != p_SelectedSprite)
									{
										p_SelectedSprite = sprite;
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
					if (ImGui::TreeNodeEx("Textures"))
					{
						/* Go through all of the Textures. */
						for (int i = 0; i < ResourceManager::m_Instance->m_Textures.size(); i++)
						{
							/* Current Texture being looked at. */
							Texture* texture = ResourceManager::m_Instance->m_Textures[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Texture is the Selected One. */
							if (ImGui::TreeNodeEx(texture->GetName().c_str(), (texture == p_SelectedTexture) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (texture != p_SelectedTexture)
									{
										p_SelectedTexture = texture;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::Material:
				{
					if (ImGui::TreeNodeEx("Materials"))
					{
						/* Go through all of the Materials. */
						for (int i = 0; i < ResourceManager::m_Instance->m_Materials.size(); i++)
						{
							/* Current Material being looked at. */
							Material* material = ResourceManager::m_Instance->m_Materials[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Material is the Selected One. */
							if (ImGui::TreeNodeEx(material->GetName().c_str(), (material == p_SelectedMaterial) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (material != p_SelectedMaterial)
									{
										p_SelectedMaterial = material;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::Font:
				{
					if (ImGui::TreeNodeEx("Fonts"))
					{
						/* Go through all of the Fonts. */
						for (int i = 0; i < ResourceManager::m_Instance->m_Fonts.size(); i++)
						{
							/* Current Font being looked at. */
							Font* font = ResourceManager::m_Instance->m_Fonts[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Font is the Selected One. */
							if (ImGui::TreeNodeEx(font->GetName().c_str(), (font == p_SelectedFont) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (font != p_SelectedFont)
									{
										p_SelectedFont = font;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::Animation:
				{
					if (ImGui::TreeNodeEx("Animations"))
					{
						/* Go through all of the Animations. */
						for (int i = 0; i < ResourceManager::m_Instance->m_Animations.size(); i++)
						{
							/* Current Animation being looked at. */
							Animation* animation = ResourceManager::m_Instance->m_Animations[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Animation is the Selected One. */
							if (ImGui::TreeNodeEx(animation->GetName().c_str(), (animation == p_SelectedAnimation) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (animation != p_SelectedAnimation)
									{
										p_SelectedAnimation = animation;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::AudioSource:
				{
					if (ImGui::TreeNodeEx("Audio Sources"))
					{
						/* Go through all of the Audio Sources. */
						for (int i = 0; i < ResourceManager::m_Instance->m_AudioSources.size(); i++)
						{
							/* Current Audio Source being looked at. */
							AudioSource* audioSource = ResourceManager::m_Instance->m_AudioSources[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Audio Source is the Selected One. */
							if (ImGui::TreeNodeEx(audioSource->GetName().c_str(), (audioSource == p_SelectedAudioSource) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (audioSource != p_SelectedAudioSource)
									{
										p_SelectedAudioSource = audioSource;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::TileMap:
				{
					if (ImGui::TreeNodeEx("Tile Maps"))
					{
						/* Go through all of the Tile Maps. */
						for (int i = 0; i < ResourceManager::m_Instance->m_TileMaps.size(); i++)
						{
							/* Current Tile Map being looked at. */
							TileMap* tileMap = ResourceManager::m_Instance->m_TileMaps[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Tile Map is the Selected One. */
							if (ImGui::TreeNodeEx(tileMap->GetName().c_str(), (tileMap == p_SelectedTileMap) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (tileMap != p_SelectedTileMap)
									{
										p_SelectedTileMap = tileMap;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					break;
				}
				case Kross::AssetType::TileSet:
				{
					if (ImGui::TreeNodeEx("Tile Sets"))
					{
						/* Go through all of the Tile Sets. */
						for (int i = 0; i < ResourceManager::m_Instance->m_TileSets.size(); i++)
						{
							/* Current Tile Set being looked at. */
							TileSet* tileSet = ResourceManager::m_Instance->m_TileSets[i];

							/* Tree Node, sets the Leaf to be a Selected one if the Current Tile Set is the Selected One. */
							if (ImGui::TreeNodeEx(tileSet->GetName().c_str(), (tileSet == p_SelectedTileSet) ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_Leaf))
							{
								/* If we Select the Node. */
								if (SelectNode())
								{
									/* Set the Selected Node. If it's different of course. */
									if (tileSet != p_SelectedTileSet)
									{
										p_SelectedTileSet = tileSet;
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
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

	void AssetPreview::SetSpriteDestination(Sprite* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationSprite)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationSprite = destination;
		p_SelectedSprite = nullptr;
	}

	void AssetPreview::SetTextureDestination(Texture* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationTexture)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationTexture = destination;
		p_SelectedTexture = nullptr;
	}

	void AssetPreview::SetMaterialDestination(Material* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationMaterial)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationMaterial = destination;
		p_SelectedMaterial = nullptr;
	}

	void AssetPreview::SetFontDestination(Font* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationFont)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationFont = destination;
		p_SelectedFont = nullptr;
	}

	void AssetPreview::SetAnimationDestination(Animation* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationAnimation)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationAnimation = destination;
		p_SelectedAnimation = nullptr;
	}

	void AssetPreview::SetAudioSourceDestination(AudioSource* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationAudioSource)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationAudioSource = destination;
		p_SelectedAudioSource = nullptr;
	}

	void AssetPreview::SetTileMapDestination(TileMap* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationTileMap)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationTileMap = destination;
		p_SelectedTileMap = nullptr;
	}

	void AssetPreview::SetTileSetDestination(TileSet* destination)
	{
		/* Early out if the Destination Specified is already set. */
		if (destination == p_DestinationTileSet)
		{
			return;
		}

		/* Other wise set it. */
		p_DestinationTileSet = destination;
		p_SelectedTileSet = nullptr;
	}
}
