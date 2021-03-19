#pragma once

#include "../Core.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowProperties.h"

namespace Kross
{
	class KROSS_API Window
	{
	private:
		~Window();

		WindowProperties* p_Properties;
		GLFWwindow* p_GLFWWindow;

		bool m_Initialised;

	protected:
		friend class Application;

		// Returns the success of the Start Method.
		bool GetInitialiseStatus() const { return m_Initialised; };

		// Returns the Window close status.
		bool GetClosedStatus() const { return glfwWindowShouldClose(p_GLFWWindow); };

		// Sets the Title.
		void SetTitle(const std::string& title) { p_Properties->SetTitle(title); };

		// Sets the Width.
		void SetWidth(int width) { p_Properties->SetWidth(width); };

		// Sets the Height.
		void SetHeight(int height) { p_Properties->SetHeight(height); };

		// Sets the VSync.
		void SetVSync(int vSync) { p_Properties->SetVSync(vSync); };

		// The Initialise of the window. For creating OpenGL Contexts.
		void OnInitialise();

		// Start of the Window.
		void OnStart(float r = 0.5f, float g = 0.5f, float b = 0.5f, float a = 0.5f);

		// Polling Window Events.
		void OnPollEvents();

		// Destroys Contexts and other window information.
		void OnShutdown();

	public:
		Window()
			: p_Properties(new WindowProperties()), p_GLFWWindow(nullptr), m_Initialised(false)
		{};
		
		// Gets the Title of the Window.
		const std::string& GetTitle() const { return p_Properties->GetTitle(); };

		// Gets the Width of the Window.
		const int GetWidth() const { return p_Properties->GetWidth(); };

		// Gets the Height of the Window.
		const int GetHeight() const { return p_Properties->GetHeight(); };

		// Gets the VSync of the Window.
		const int GetVSync() const { return p_Properties->GetVSync(); };

		// Gets the Aspect Ratio of the Window.
		float GetApsectRatio() const { return (float)p_Properties->GetWidth() / (float)p_Properties->GetHeight(); };

		// Grabs the OpenGL Window. (USE IF YOU KNOW WHAT YOUR DOING WITH IT)
		GLFWwindow* GetGLFWWindow() const { return p_GLFWWindow; };
	};
}
