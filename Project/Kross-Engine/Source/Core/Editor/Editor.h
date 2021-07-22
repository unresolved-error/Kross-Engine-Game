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
		List<EditorWindow*> m_EditorWindows;
		ObjectEditor* p_ObjectEditor;

		ImGuiViewport* p_Viewport;

		Editor() :
			m_EditorWindows	(List<EditorWindow*>()),
			p_ObjectEditor	(nullptr)
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
		static void AttachEditorWindow(EditorWindow* window); 

		static Vector2 GetViewportPosition();
		static Vector2 GetViewportSize();
		//static void DetachEditorWindow(EditorWindow* window) { s_Instance->m_EditorWindows.push_back(window); };
	};
}