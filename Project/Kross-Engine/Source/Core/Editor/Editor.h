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

		Editor() :
			m_EditorWindows	(List<EditorWindow*>())
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
		static void OnRender();

	public:

		static void AttachEditorWindow(EditorWindow* window) { s_Instance->m_EditorWindows.push_back(window); };
		//static void DetachEditorWindow(EditorWindow* window) { s_Instance->m_EditorWindows.push_back(window); };
	};
}