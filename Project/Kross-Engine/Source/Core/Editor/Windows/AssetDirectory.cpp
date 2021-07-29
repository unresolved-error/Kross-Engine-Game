/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "AssetDirectory.h"

#include "../Editor.h"

namespace Kross
{
    void AssetDirectory::SetFlags()
    {
        m_WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    }
    void AssetDirectory::OnStart()
    {
        SetFlags();

        m_Title = "Asset Directory";
    }
    void AssetDirectory::Attach()
    {

        Vector2 viewPosition = Editor::GetViewportPosition();
        Vector2 viewSize = Editor::GetViewportSize();
        ImVec2 position = ImVec2(viewPosition.x, viewPosition.y + (viewSize.y * 0.7f));

        ImVec2 size = ImVec2(viewSize.x * 0.2f, (viewSize.y * 0.31f));

        ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);
        
        ImGui::SetWindowPos(position);
        ImGui::SetWindowSize(size);

        ImGui::End();
    }
}