/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "AssetPanel.h"

#include "../Editor.h"

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

        ImGui::Begin(m_Title.c_str(), NULL, m_WindowFlags);

        ImGui::SetWindowPos(position);
        ImGui::SetWindowSize(size);

        ImGui::End();
    }
}