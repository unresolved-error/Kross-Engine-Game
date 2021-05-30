/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

#include "Window/Window.h"

namespace Kross
{
	class KROSS_API Application
	{
	private:
		Application(const std::string& title, int width, int height);
		~Application();

		static Application* s_Instance;
		Window* p_Window;

	protected:

	public:
		
		// Creating the Application. (CALL FIRST)
		static void OnCreate(const std::string& title = "Kross-Engine Application", int width = 1280, int height = 720);

		// Initialising the Managers and Window. (CALL AFTER CREATE AND BEFORE UPDATE)
		static void OnStart();

		// Running the Engine. (CALL AFTER START AND BEFORE SHUTDOWN)
		static void OnUpdate();

		// Cleaning up Engine and Managers. (CALL AFTER UPDATE AND BEFORE DESTROY)
		static void OnShutdown();

		// Destroying Everything. (CALL LAST)
		static void OnDestroy();

		// Gets the Window of the Application.
		static Window* GetWindow() { return s_Instance->p_Window; };
	};
}