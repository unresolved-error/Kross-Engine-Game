/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

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

		WindowProperties* m_Properties;
		GLFWwindow* m_GLFWWindow;

		bool m_Initialised;

	protected:
		friend class Application;

		// Returns the success of the Start Method.
		bool Initialised() const { return m_Initialised; };

		// Returns the Window close status.
		bool Closed() const { return glfwWindowShouldClose(m_GLFWWindow); };

		// Sets the Title.
		void SetTitle(const std::string& title) { m_Properties->SetTitle(title); };

		// Sets the Width.
		void SetWidth(int width) { m_Properties->SetWidth(width); };

		// Sets the Height.
		void SetHeight(int height) { m_Properties->SetHeight(height); };

		// The Initialise of the window. For creating OpenGL Contexts.
		void OnInitialise();

		// Hides the Cursor.
		void HideCursor() { glfwSetInputMode(m_GLFWWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); };

		// UnHides the Cursor.
		void UnHideCursor() { glfwSetInputMode(m_GLFWWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); };

		// Start of the Window.
		void OnStart(float r = 0.5f, float g = 0.5f, float b = 0.5f, float a = 0.5f);

		// Polling Window Events.
		void OnPollEvents();

		// Destroys Contexts and other window information.
		void OnShutdown();

	public:
		Window() :
			m_Properties	(KROSS_NEW WindowProperties()), 
			m_GLFWWindow	(nullptr), 
			m_Initialised	(false)
		{};
		
		// Gets the Title of the Window.
		const std::string& GetTitle() const { return m_Properties->GetTitle(); };

		// Gets the Width of the Window.
		const int GetWidth() const { return m_Properties->GetWidth(); };

		// Gets the Height of the Window.
		const int GetHeight() const { return m_Properties->GetHeight(); };

		// Gets the VSync of the Window.
		const int GetVSync() const { return m_Properties->GetVSync(); };

		// Gets the Fullscreen Mode of the Window.
		const int GetFullscreen() const { return m_Properties->GetFullscreen(); };

		// Gets the Aspect Ratio of the Window.
		float GetApsectRatio() const { return (float)m_Properties->GetWidth() / (float)m_Properties->GetHeight(); };
		
		// Gets the Refresh Rate of the Screen.
		const int GetScreenRefreshRate() const;

		// Sets the VSync.
		void SetVSync(int vSync) { m_Properties->SetVSync(vSync); };

		// Set the window to fullscreen borderless.
		void SetFullscreen(int fullscreen) { m_Properties->SetFullscreen(fullscreen); };

		// Grabs the OpenGL Window. (USE IF YOU KNOW WHAT YOUR DOING WITH IT)
		GLFWwindow* GetGLFWWindow() const { return m_GLFWWindow; };

		// Close the Window.
		void CloseWindow() { glfwSetWindowShouldClose(m_GLFWWindow, 1); };
	};
}
