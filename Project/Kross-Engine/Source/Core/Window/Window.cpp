#include "Window.h"

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

		if (Width != GetWidth() || Height != GetHeight())
		{
			/* Set Everything to the new Width and Height */
			glViewport(0, 0, Width, Height);
			SetWidth(Width);
			SetHeight(Height);
		}

		/* Poll the Events */
		glfwSwapBuffers(p_GLFWWindow);
		glfwPollEvents();
	}

	void Window::OnShutdown()
	{
		this->~Window();
	}
}