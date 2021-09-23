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
		static Editor* m_Instance;
		std::vector<EditorWindow*> m_EditorWindows;
		ObjectEditor* m_ObjectEditor;
		MainMenu* m_MainMenu;
		AssetPanel* m_AssetPanel;

		bool m_IsUpdating;

		ImGuiViewport* m_Viewport;

		float m_CameraMoveSpeedMultiplier = 1.0f;
		float m_CameraMoveSpeedMultiplierMax = 10.0f;
		float m_CameraMoveSpeedMultiplierResetTimer = 0.0f;
		float m_CameraMoveSpeedMultiplierResetTimerMax = 3.0f;

		Editor() :
			m_EditorWindows	(std::vector<EditorWindow*>()),
			m_ObjectEditor	(nullptr),
			m_MainMenu		(nullptr),
			m_AssetPanel	(nullptr),
			m_IsUpdating	(false),
			m_Viewport		(nullptr)
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

		static void LoadEditorCamera(Object* editorCamera);
		static void WriteEditorCamera(Object* editorCamera);


		static void SetScene(Scene* scene);

		static void OnShutdown();

		static void StylePush();
		static void StylePop();

		static void NewFrame();

	public:
		static void SetObjectEditorObject(Object* object) { m_Instance->m_ObjectEditor->p_SelectedObject = object; };
		static void SetMainMenuObject(Object* object) { m_Instance->m_MainMenu->SetSelectedObject(object); };
		static void SetAssetPanelAssetType(AssetType type) { m_Instance->m_AssetPanel->SetAssetType(type); }
		static void AttachEditorWindow(EditorWindow* window); 
		static void DetachEditorWindow(EditorWindow* window);

		static void MoveEditorCamera(Object* editorCamera);

		static bool AnyWindowIsHovered() { return ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow); };
		static bool AnyWindowIsActive() { return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow); };

		static Vector2 GetViewportPosition();
		static Vector2 GetViewportSize();
	};
}