/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Application.h"

#include "Manager/ShaderManager.h"
#include "Manager/ResourceManager.h"
#include "File-IO/Manifest.h"
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
	Application*	Application::m_Instance =	nullptr;

	Application::Application(const std::string& title, int width, int height) :
		m_Window	(KROSS_NEW Window())
	{
		m_Window->SetWidth(width);
		m_Window->SetHeight(height);
		m_Window->SetTitle(title);
		m_Window->SetVSync(1);

		#ifndef KROSS_EDITOR
		m_Window->SetFullscreen(0);
		m_Window->HideCursor();
		#endif
	}

	Application::~Application()
	{}

	void Application::OnCreate(const std::string& title, int width, int height)
	{
		if (!m_Instance)
		{
			m_Instance = KROSS_NEW Application(title, width, height);
		}
	}

	void Application::OnStart()
	{
		m_Instance->m_Window->m_Properties->SetVSync(1);
		m_Instance->m_Window->OnInitialise();
		ShaderManager::OnCreate();
		ResourceManager::OnCreate();
		SceneManager::OnCreate();
		Time::OnCreate();
		Input::OnCreate();
		Input::SetWindow(m_Instance->m_Window);
		Physics::OnCreate();
		AudioManager::OnCreate();
		AudioManager::OnStart();
		Editor::OnCreate();
		Manifest::OnCreate();

		//ResourceManager::OnReadManifest();

		/* Reads the Manifest File. */
		Manifest::Load("manifest.krs");
	}

	void Application::OnUpdate()
	{
		/* If the window was successfully Started. Run the Application. */
		if (m_Instance->m_Window->Initialised() && Manifest::SuccessfulLoad())
		{
			Debug::LogLine("Kross Engine Running...");
			SceneManager::OnStart();

			Debug::Log("Starting Main Loop...");
			Debug::EndLine();

			#ifdef KROSS_EDITOR
			Editor::LoadEditorCamera(SceneManager::GetCurrentScene()->GetCamera());
			Editor::AttachEditorWindow(KROSS_NEW SceneHierarchy());
			Editor::AttachEditorWindow(KROSS_NEW ObjectEditor());
			Editor::AttachEditorWindow(KROSS_NEW MainMenu());
			Editor::AttachEditorWindow(KROSS_NEW AssetDirectory());
			Editor::AttachEditorWindow(KROSS_NEW AssetPanel());

			Editor::OnStart(m_Instance->m_Window);
			#endif

			/* While the window isn't closed */
			while (!m_Instance->m_Window->Closed())
			{
				m_Instance->m_Window->OnStart();
				Time::OnUpdateDeltaTime();
				Input::OnUpdate();

				SceneManager::OnStart();
				SceneManager::OnUpdate(); /* Got to be looked at. */

				#ifndef KROSS_EDITOR
				SceneManager::OnPhysicsUpdate();
				#endif

				SceneManager::OnUpdateSceneCameraAspectRatio(m_Instance->m_Window->GetApsectRatio());
				
				SceneManager::OnRender();

				#ifdef KROSS_EDITOR
				Editor::SetScene(SceneManager::GetCurrentScene());

				Editor::NewFrame();

				Editor::StylePush();
				Editor::OnUpdate();
				Editor::StylePop();

				Editor::OnRender();
				#endif

				if(Scene* scn = SceneManager::GetScene()) scn->OnRemoveObjects();

				Input::SetScrollValue(0.0f);
				m_Instance->m_Window->OnPollEvents();

			}
		}

		else if (!Manifest::SuccessfulLoad())
		{
			Debug::Spacing();
			Debug::LogErrorLine("Failed to Start! Read manifest-log.txt for details.");
			Debug::Spacing();
		}

		return;
	}

	void Application::OnShutdown()
	{
		#ifdef KROSS_EDITOR
		if(Manifest::SuccessfulLoad())
		{	
			Editor::WriteEditorCamera(SceneManager::GetCurrentScene()->GetCamera());
			Editor::OnShutdown();
		}
		#endif

		Editor::OnDestroy();

		m_Instance->m_Window->OnShutdown();
		AudioManager::OnShutdown();

		/* Writes the Manifest. */
		ResourceManager::OnWriteManifest();

		ResourceManager::OnDestroy();

		Manifest::OnDestroy();

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
		if (m_Instance)
		{
			delete m_Instance;
		}
	}
}