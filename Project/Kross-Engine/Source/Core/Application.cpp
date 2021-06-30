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
#include "Manager/Time.h"
#include "Physics/Physics.h"

#include "Renderer/Image/Atlas.h"

#include "Input.h"

namespace Kross
{
	Application*	Application::s_Instance =	nullptr;

	Application::Application(const std::string& title, int width, int height) :
		p_Window	(KROSS_NEW Window())
	{
		p_Window->SetWidth(width);
		p_Window->SetHeight(height);
		p_Window->SetTitle(title);
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

		/* Loads the Manifest File. */
		ResourceManager::OnLoadManifest();
	}

	void Application::OnUpdate()
	{

		/* If the window was successfully Started. Run the Application. */
		if (s_Instance->p_Window->GetInitialiseStatus() == true)
		{
			std::cout << "Kross Engine Running..." << std::endl;

			std::cout << "Creating Atlas..." << std::endl;
			Atlas* atlas = Atlas::OnCreate();
			ResourceManager::AttachResource<Atlas>(atlas);

			
			SceneManager::OnStart();
			std::cout << "Starting Main Loop..." << std::endl;

			/* While the window isn't closed */
			while (s_Instance->p_Window->GetClosedStatus() == false)
			{
				s_Instance->p_Window->OnStart();

				Time::OnUpdateDeltaTime();
				SceneManager::OnUpdateSceneCameraAspectRatio(s_Instance->p_Window->GetApsectRatio());

				SceneManager::OnUpdate();
				SceneManager::OnPhysicsUpdate();

				SceneManager::OnRender();

				s_Instance->p_Window->OnPollEvents();
			}
		}

		return;
	}

	void Application::OnShutdown()
	{
		s_Instance->p_Window->OnShutdown();
		AudioManager::OnShutdown();

		AudioManager::OnDestroy();
		ShaderManager::OnDestroy();
		ResourceManager::OnDestroy();
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