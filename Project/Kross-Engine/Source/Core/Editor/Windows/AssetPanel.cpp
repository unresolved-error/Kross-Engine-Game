/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "AssetPanel.h"

#include "../Editor.h"

#include "../../Manager/ResourceManager.h"

namespace Kross
{
    void AssetPanel::SetFlags()
    {
        m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    }
    void AssetPanel::OnStart()
    {
        SetFlags();

        m_Title = "Asset Panel";
    }
    void AssetPanel::Attach()
    {

        Vector2 viewPosition = Editor::GetViewportPosition();
        Vector2 viewSize = Editor::GetViewportSize();
        ImVec2 position = ImVec2(viewPosition.x + (viewSize.x * 0.2f), viewPosition.y + (viewSize.y * 0.7f));

        ImVec2 size = ImVec2(viewSize.x * 0.6f, (viewSize.y * 0.31f));

        m_Title = "Asset Panel - " + m_TypeNames[(int)m_Type];

        

        ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

        ImVec4 darkGrey = ImVec4(0.137f, 0.141f, 0.180f, 1.000f);
        ImGui::PushStyleColor(ImGuiCol_Button, darkGrey);

        Texture* texture = nullptr;
        switch (m_Type)
        {
        case Kross::AssetType::None:
            break;
        case Kross::AssetType::Sprite:
        {
            texture = ResourceManager::GetResource<Texture>("Sprite-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_Sprites.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_Sprites[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                
                Vector2 uvOffset = ResourceManager::s_Instance->m_Sprites[i]->GetUVOffset();
                Vector2 uvRatio = ResourceManager::s_Instance->m_Sprites[i]->GetUVRatio();

                ImGui::ImageButton((void*)ResourceManager::s_Instance->m_Sprites[i]->GetTexture()->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), 
                    ImVec2((0.0f * uvRatio.x) + uvOffset.x, (0.0f * uvRatio.y) + uvOffset.y), 
                    ImVec2((1.0f * uvRatio.x) + uvOffset.x, (-1.0f * uvRatio.y) + uvOffset.y));
                ImGui::Text(ResourceManager::s_Instance->m_Sprites[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::Texture:
        {
            texture = ResourceManager::GetResource<Texture>("Texture-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_Textures.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_Textures[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_Textures[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::Material:
        {
            texture = ResourceManager::GetResource<Texture>("Material-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_Materials.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_Materials[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_Materials[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::Font:
        {
            texture = ResourceManager::GetResource<Texture>("Font-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_Fonts.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_Fonts[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_Fonts[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::Animation:
        {
            texture = ResourceManager::GetResource<Texture>("Animation-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_Animations.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_Animations[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_Animations[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::AudioSource:
        {
            texture = ResourceManager::GetResource<Texture>("Audio-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_AudioSources.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_AudioSources[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_AudioSources[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::TileMap:
        {
            texture = ResourceManager::GetResource<Texture>("Tile-Map-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_TileMaps.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_TileMaps[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_TileMaps[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        case Kross::AssetType::TileSet:
        {
            texture = ResourceManager::GetResource<Texture>("Tile-Set-Icon");
            ImGui::Text("");

            int moveOver = 0;
            int moveOverMax = (int)(size.x / (texture->GetWidth() * 1.5f)) - 2;
            for (int i = 0; i < ResourceManager::s_Instance->m_TileSets.size(); i++)
            {
                ImGui::BeginChild(ResourceManager::s_Instance->m_TileSets[i]->GetName().c_str(), ImVec2(texture->GetWidth() * 1.5f, texture->GetHeight() + 32.0f), false, ImGuiWindowFlags_ChildWindow);
                ImGui::ImageButton((void*)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(0.0f, 0.0f), ImVec2(1.0f, -1.0f));
                ImGui::Text(ResourceManager::s_Instance->m_TileSets[i]->GetName().c_str());
                ImGui::EndChild();

                if (moveOver != moveOverMax)
                {
                    if (moveOver == 0)
                        ImGui::Indent();

                    ImGui::SameLine();
                    moveOver++;
                }

                else if (moveOver == moveOverMax)
                {
                    moveOver = 0;
                    ImGui::Unindent();
                }

            }
            break;
        }
        default:
            break;
        }

        ImGui::PopStyleColor();

        ImGui::SetWindowPos(position);
        ImGui::SetWindowSize(size);

        ImGui::End();
    }
}