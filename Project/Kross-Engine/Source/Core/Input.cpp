#include "Input.h"

namespace Kross
{
	Window* Input::p_window = nullptr;
	Input* Input::p_instance = nullptr;

	void Input::OnCreate()
	{
		if (!p_instance)
			p_instance = new Input();
	}

	void Input::OnDestoy()
	{
		if (p_instance)
		{
			p_window = nullptr;
			delete p_instance;
		}
	}

	float Input::GetAxis(Axis axis)
	{
		GLFWwindow* window = p_window->GetGLFWWindow();
		switch (axis)
		{
			case Axis::None:
			{
				return 0.0f;
			}

			case Axis::KeyboardHorizontal:
			{

				if (p_window)
				{
					float rightValue = glfwGetKey(window, (int)Key::D) + glfwGetKey(window, (int)Key::RightArrow);
					float leftValue = glfwGetKey(window, (int)Key::A) + glfwGetKey(window, (int)Key::LeftArrow);

					return (float)(glm::sign(rightValue) - glm::sign(leftValue));
				}

				return 0.0f;
			}

			case Axis::KeyboardVertical:
			{
				if (p_window)
				{
					float upValue = (float)glfwGetKey(window, (int)Key::W) + (float)glfwGetKey(window, (int)Key::UpArrow);
					float downValue = (float)glfwGetKey(window, (int)Key::S) + (float)glfwGetKey(window, (int)Key::DownArrow);

					return (float)(glm::sign(upValue) - glm::sign(downValue));
				}

				return 0.0f;
			} 

			default:
			{
				return 0.0f;
			} 
		}
	}

	bool Input::GetKeyDown(Key key)
	{
		GLFWwindow* window = p_window->GetGLFWWindow();
		return (bool)glfwGetKey(window, (int)key);
	}

	bool Input::GetMouseButtonDown(Mouse mouse)
	{
		GLFWwindow* window = p_window->GetGLFWWindow();
		if (mouse != Mouse::None)
			return (bool)glfwGetMouseButton(window, (int)mouse);

		else
			return false;
	}

	Vector2 Input::GetMousePosition()
	{
		double x, y;

		GLFWwindow* window = p_window->GetGLFWWindow();
		glfwGetCursorPos(window, &x, &y);

		return Vector2((float)x, (float)y);
	}

	float Input::GetControllerAxis(int controllerID, Controller axis, float deadZone)
	{
		if (ControllerConnected(controllerID))
		{
			GLFWgamepadstate state;

			glfwGetGamepadState(controllerID, &state);

			switch (axis)
			{
			case Controller::LeftStickHorizontal:
			{
				if (state.axes[(int)Controller::LeftStickHorizontal] >= deadZone || state.axes[(int)Controller::LeftStickHorizontal] <= -deadZone)
					return state.axes[(int)Controller::LeftStickHorizontal];

				return 0.0f;
			}
			case Controller::LeftStickVertical:
			{
				if (state.axes[(int)Controller::LeftStickVertical] >= deadZone || state.axes[(int)Controller::LeftStickVertical] <= -deadZone)
					return -state.axes[(int)Controller::LeftStickVertical];

				return 0.0f;
			}
			case Controller::RightStickHorizontal:
			{
				if (state.axes[(int)Controller::RightStickHorizontal] >= deadZone || state.axes[(int)Controller::RightStickHorizontal] <= -deadZone)
					return state.axes[(int)Controller::RightStickHorizontal];

				return 0.0f;
			}
			case Controller::RightStickVertical:
			{
				if (state.axes[(int)Controller::RightStickVertical] >= deadZone || state.axes[(int)Controller::RightStickVertical] <= -deadZone)
					return -state.axes[(int)Controller::RightStickVertical];

				return 0.0f;
			}

			case Controller::LeftTrigger:
			{
				return state.axes[(int)Controller::LeftTrigger];
			}

			case Controller::RightTrigger:
			{
				return state.axes[(int)Controller::RightTrigger];
			}
			default:
			{
				return 0.0f;
			}
			}
		}

		return 0.0f;
	}

	bool Input::GetControllerButtonDown(int controllerID, Controller button)
	{
		GLFWgamepadstate state;

		glfwGetGamepadState(controllerID, &state);

		std::cout << state.buttons[(int)button] << std::endl;

		if (state.buttons[(int)button] == GLFW_PRESS)
			return true;

		else
			return false;
	}

	int Input::GetAvalibleController()
	{
		for (int i = 0; i < MaxControllerSlots(); ++i)
		{
			if (ControllerConnected(i))
				return i;
		}

		return -1;
	}
}