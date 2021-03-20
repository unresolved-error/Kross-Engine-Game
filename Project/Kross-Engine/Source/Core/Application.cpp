#include "Application.h"

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

			/* While the window isn't closed */
			while (s_Window->GetClosedStatus() == false)
			{
				s_Window->OnStart();

				// Do other Stuff...

				s_Window->OnPollEvents();
			}
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