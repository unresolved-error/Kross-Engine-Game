/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

#include "Application.h"\

/* --- TESTING --- */
#include "Renderer/Image/Sprite.h"
#include "Renderer/Shader/Shader.h"
/* --------------- */

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
	}

	void Application::OnUpdate()
	{
		/* If the window was successfully Started. Run the Application. */
		if (s_Window->GetInitialiseStatus() == true)
		{
			std::cout << "Kross Engine Running..." << std::endl;

			Shader* shader = Shader::OnCreate("standard.vert", "standard.frag", "Shader");
			Texture* texture = Texture::OnCreate("Default.png", "Default");
			Sprite* sprite = Sprite::OnCreate(texture, 32, 32, "Default");

			shader->SetUniform("u_Texture", texture);
			shader->SetUniform("u_UVRatio", sprite->GetUVRatio());
			shader->SetUniform("u_UVOffset", sprite->GetUVOffset());

			/* While the window isn't closed */
			while (s_Window->GetClosedStatus() == false)
			{
				s_Window->OnStart();

				// Do other Stuff...
				texture->SetSlot(0);
				texture->Attach();
				shader->Attach();
				sprite->OnRender();
				texture->Detach();

				s_Window->OnPollEvents();
			}

			Shader::OnDestroy(shader);
			Sprite::OnDestroy(sprite);
		}

		return;
	}

	void Application::OnShutdown()
	{
		s_Window->OnShutdown();
	}

	void Application::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}