/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Application.h"

#include "Manager/ShaderManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"

#include "Input.h"

namespace Kross
{
	Application*	Application::s_Instance =	nullptr;
	Window*			Application::s_Window =		nullptr;

	Application::Application(const std::string& title, int width, int height)
	{
		s_Window = new Window();

		s_Window->SetWidth(width);
		s_Window->SetHeight(height);
		s_Window->SetTitle(title);
	}

	Application::~Application()
	{}

	void Application::OnCreate(const std::string& title, int width, int height)
	{
		if (!s_Instance)
			s_Instance = new Application(title, width, height);
	}

	void Application::OnStart()
	{
		s_Window->OnInitialise();
		ShaderManager::OnCreate();
		ResourceManager::OnCreate();
		SceneManager::OnCreate();
		Input::OnCreate();
		Input::SetWindow(s_Window);

		/* Add the Standard Shaders. */
		Shader* standardShader = Shader::OnCreate("Resources/Shaders/standard.vert", "Resources/Shaders/standard.frag", "StandardShader");
		ResourceManager::AttachResource<Shader>(standardShader);

		Shader* textShader = Shader::OnCreate("Resources/Shaders/text.vert", "Resources/Shaders/text.frag", "TextShader");
		ResourceManager::AttachResource<Shader>(textShader);

		Texture* fontTexture = Texture::OnCreate("Resources/Font/FontSheet.png", "FontTexture");

		Font* standardFont = Font::OnCreate(fontTexture, 16, 16, "StandardFont");
		ResourceManager::AttachResource<Font>(standardFont);
	}

	void Application::OnUpdate()
	{
		/* If the window was successfully Started. Run the Application. */
		if (s_Window->GetInitialiseStatus() == true)
		{
			std::cout << "Kross Engine Running..." << std::endl;
			
			SceneManager::OnStart();

			/* While the window isn't closed */
			while (s_Window->GetClosedStatus() == false)
			{
				s_Window->OnStart();

				SceneManager::OnUpdateSceneCameraAspectRatio(s_Window->GetApsectRatio());

				SceneManager::OnUpdate();
				SceneManager::OnPhysicsUpdate();
				SceneManager::OnRender();

				s_Window->OnPollEvents();
			}
		}

		return;
	}

	void Application::OnShutdown()
	{
		s_Window->OnShutdown();
		ShaderManager::OnDestroy();
		ResourceManager::OnDestroy();
		SceneManager::OnDestroy();
		Input::OnDestoy();
	}

	void Application::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}