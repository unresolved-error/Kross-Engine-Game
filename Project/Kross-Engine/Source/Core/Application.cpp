#include "Application.h"

namespace Kross
{
	Application*	Application::s_Instance =	nullptr;

	Application::Application(const std::string& title, int width, int height)
	{
		// Do Something Eventually...
	}

	Application::~Application()
	{
		// Do Something Eventually...
	}

	void Application::OnCreate(const std::string& title, int width, int height)
	{
		if (!s_Instance)
			s_Instance = new Application(title, width, height);
	}

	void Application::OnStart()
	{
		// Do Something Eventually...
	}

	void Application::OnUpdate()
	{
		std::cout << "Kross Engine Running..." << std::endl;

		while (true)
		{
			// Do Something Eventually...
		}
	}

	void Application::OnShutdown()
	{
		// Do Something Eventually...
	}

	void Application::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}