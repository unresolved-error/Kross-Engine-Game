/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Application.h"

#include "EditorWindow.h"

namespace Kross
{
	class KROSS_API Editor
	{
	private:
		static Editor* s_Instance;
		std::vector<EditorWindow*> m_EditorWindows;
		ObjectEditor* p_ObjectEditor;
		MainMenu* p_MainMenu;
		AssetPanel* p_AssetPanel;

		bool m_IsUpdating;

		ImGuiViewport* p_Viewport;

		Editor() :
			m_EditorWindows	(std::vector<EditorWindow*>()),
			p_ObjectEditor	(nullptr),
			p_MainMenu		(nullptr),
			p_AssetPanel	(nullptr),
			m_IsUpdating	(false),
			p_Viewport		(nullptr)
		{};

		~Editor();

	protected:
		friend class Application;
		friend class SceneManager;

		static void OnCreate();
		static void OnDestroy();

		static void OnStart(Window* window);
		static void OnUpdate();
		static void OnRender();

		static void SetScene(Scene* scene);

		static void OnShutdown();

		static void StylePush();
		static void StylePop();

		static void NewFrame();

	public:
		static void SetObjectEditorObject(Object* object) { s_Instance->p_ObjectEditor->p_SelectedObject = object; };
		static void SetMainMenuObject(Object* object) { s_Instance->p_MainMenu->SetSelectedObject(object); };
		static void SetAssetPanelAssetType(AssetType type) { s_Instance->p_AssetPanel->SetAssetType(type); }
		static void AttachEditorWindow(EditorWindow* window); 
		static void DetachEditorWindow(EditorWindow* window);

		static bool AnyWindowIsHovered() { return ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow); };
		static bool AnyWindowIsActive() { return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow); };

		static Vector2 GetViewportPosition();
		static Vector2 GetViewportSize();
		//static void DetachEditorWindow(EditorWindow* window) { s_Instance->m_EditorWindows.push_back(window); };
	};
}