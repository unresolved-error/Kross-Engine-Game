/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Application.h"

#include "Manager/ShaderManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Manager/AudioManager.h"
#include "Manager/ScriptRegistry.h"
#include "Manager/Time.h"
#include "Physics/Physics.h"

#include "Debug.h"

#include "Renderer/Image/Atlas.h"

#include "Input.h"

#include "Editor/Editor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Kross
{
	Application*	Application::s_Instance =	nullptr;

	Application::Application(const std::string& title, int width, int height) :
		p_Window	(KROSS_NEW Window())
	{
		p_Window->SetWidth(width);
		p_Window->SetHeight(height);
		p_Window->SetTitle(title);
		p_Window->SetVSync(1);
	}

	Application::~Application()
	{}

	void Application::OnCreate(const std::string& title, int width, int height)
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW Application(title, width, height);
	}

	void Application::OnStart()
	{
		s_Instance->p_Window->OnInitialise();
		ShaderManager::OnCreate();
		ResourceManager::OnCreate();
		SceneManager::OnCreate();
		Time::OnCreate();
		Input::OnCreate();
		Input::SetWindow(s_Instance->p_Window);
		Physics::OnCreate();
		AudioManager::OnCreate();
		AudioManager::OnStart();
		Editor::OnCreate();

		/* Reads the Manifest File. */
		ResourceManager::OnReadManifest();
	}

	void Application::OnUpdate()
	{
		/* If the window was successfully Started. Run the Application. */
		if (s_Instance->p_Window->Initialised())
		{
			Debug::LogLine(std::string() + "Kross Engine Running...");

			SceneManager::OnStart();
			Debug::Log(std::string() + "Starting Main Loop...");
			Debug::EndLine();

			#ifdef KROSS_EDITOR
			Editor::AttachEditorWindow(KROSS_NEW SceneHierarchy());
			Editor::AttachEditorWindow(KROSS_NEW ObjectEditor());
			Editor::AttachEditorWindow(KROSS_NEW MainMenu());
			Editor::AttachEditorWindow(KROSS_NEW AssetDirectory());
			Editor::AttachEditorWindow(KROSS_NEW AssetPanel());

			Editor::OnStart(s_Instance->p_Window);
			#endif

			/* While the window isn't closed */
			while (!s_Instance->p_Window->Closed())
			{
				s_Instance->p_Window->OnStart();

				Time::OnUpdateDeltaTime();

				SceneManager::OnUpdateSceneCameraAspectRatio(s_Instance->p_Window->GetApsectRatio());

				SceneManager::OnUpdate();

				#ifndef KROSS_EDITOR
				SceneManager::OnPhysicsUpdate();
				#endif

				SceneManager::OnRender();

				#ifdef KROSS_EDITOR
				Editor::SetScene(SceneManager::GetCurrentScene());

				Editor::NewFrame();

				Editor::StylePush();
				Editor::OnUpdate();
				Editor::StylePop();

				Editor::OnRender();
				#endif

				Input::SetScrollValue(0.0f);
				s_Instance->p_Window->OnPollEvents();

			}
		}

		#ifdef KROSS_EDITOR
		Editor::OnShutdown();
		#endif

		return;
	}

	void Application::OnShutdown()
	{
		Editor::OnDestroy();

		s_Instance->p_Window->OnShutdown();
		AudioManager::OnShutdown();

		/* Writes the Manifest. */
		ResourceManager::OnWriteManifest();

		ResourceManager::OnDestroy();

		ScriptRegistry::OnDestroy();

		AudioManager::OnDestroy();
		ShaderManager::OnDestroy();
		SceneManager::OnDestroy();
		Time::OnDestroy();
		Input::OnDestoy();
		Physics::OnDestroy();
	}

	void Application::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}