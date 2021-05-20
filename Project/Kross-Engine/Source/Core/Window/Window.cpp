/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Window.h"

#include "../Manager/ShaderManager.h"

namespace Kross
{
	Window::~Window()
	{
		delete p_Properties;
		
		if (p_GLFWWindow)
			glfwDestroyWindow(p_GLFWWindow);

		glfwTerminate();
	}

	void Window::OnStart(float r, float g, float b, float a)
	{
		float red, green, blue, alpha;

		/* Clamp the RGBA values from 1.0 to 0.0 */
		red = ((r < 0.0f) ? 0.0f : ((r > 1.0f) ? 1.0f : r));
		green = ((g < 0.0f) ? 0.0f : ((g > 1.0f) ? 1.0f : g));
		blue = ((b < 0.0f) ? 0.0f : ((b > 1.0f) ? 1.0f : b));
		alpha = ((a < 0.0f) ? 0.0f : ((a > 1.0f) ? 1.0f : a));

		/* Set Clear Colours and Refresh the window */
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::OnInitialise()
	{
		/* Assume everything will be okay. */
		m_Initialised = true;

		/* Initialise GLFW */
		if (!glfwInit())
		{
			// Failed to intialise.
			m_Initialised = false;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		p_GLFWWindow = glfwCreateWindow(p_Properties->GetWidth(), p_Properties->GetHeight(), p_Properties->GetTitle().c_str(), NULL, NULL);

		if (!p_GLFWWindow)
		{
			// Failed to Create Window.
			m_Initialised = false;
			return;
		}

		/* Set Context */
		glfwMakeContextCurrent(p_GLFWWindow);

		/* Initialise GLEW */
		if (glewInit() != GLEW_OK)
		{
			// Failed to intialise.
			m_Initialised = false;
			return;
		}

		/* Enable Pixel Blending */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Enable Front and Back Face Culling. */
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT_AND_BACK);

		/* VSync Switch */
		glfwSwapInterval(p_Properties->GetVSync());
	}

	void Window::OnPollEvents()
	{
		/* VSync Switch */
		glfwSwapInterval(p_Properties->GetVSync());

		/* Get the Current Width and Height of the Window */
		int Width, Height;
		glfwGetWindowSize(p_GLFWWindow, &Width, &Height);

		/* If the current width or height doesn't match the set width and height */
		if (Width != GetWidth() || Height != GetHeight())
		{
			/* Set Everything to the new Width and Height */
			glViewport(0, 0, Width, Height);
			SetWidth(Width);
			SetHeight(Height);
		}

		/* Retrieves the Primary Monitor */
		GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();

		/* Grab the Monitor Size */
		glfwGetMonitorWorkarea(mainMonitor, NULL, NULL, &Width, &Height);

		/* If we haven't changed the Window mode */
		if (p_Properties->GetChangedWindowModeStatus() == false)
		{
			/* Change the Window Mode based on the fullscreen flag */
			switch (GetFullscreen())
			{
				case 0:
				{
					/* Rest the Window View Port and Size. */
					glViewport(0, 0, 1280, 720);
					SetWidth(1280);
					SetHeight(720);

					/* Set the window to the middle of the screen */
					glfwSetWindowMonitor(p_GLFWWindow, NULL, (int)(((float)GetWidth() / (float)Width) * GetWidth()) - (int)(GetWidth() / 2), (int)(((float)GetHeight() / (float)Height) * GetHeight()) - (int)(GetHeight() / 2), GetWidth(), GetHeight(), GLFW_DONT_CARE);
					break;
				}

				case 1:
				{
					/* Set the window to the top left of the screen */
					glfwSetWindowMonitor(p_GLFWWindow, mainMonitor, 0, 0, Width, Height, GLFW_DONT_CARE);
					break;
				}
			}
			
			/* Initiate that we have changed the window mode */
			p_Properties->SetChangedWindowModeStatusDefault();
		}

		/* Poll the Events */
		glfwSwapBuffers(p_GLFWWindow);
		glfwPollEvents();
	}

	void Window::OnShutdown()
	{
		delete this;
	}
	const int Window::GetScreenRefreshRate() const
	{
		/* Grab the main Monitor and the Video Mode. */
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

		/* Return the Refresh Rate. */
		return videoMode->refreshRate;
	}
}