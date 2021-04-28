#include "Input.h"

namespace Kross
{
	Window* Input::s_Window = nullptr;
	Input* Input::s_Instance = nullptr;

	std::unordered_map<Key, int>			Input::s_KeyStateCache =			std::unordered_map<Key, int>();
	std::unordered_map<Controller, int>		Input::s_ControllerStateCache =		std::unordered_map<Controller, int>();
	std::unordered_map<Mouse, int>			Input::s_MouseStateCache =			std::unordered_map<Mouse, int>();

	void Input::OnCreate()
	{
		if (!s_Instance)
			s_Instance = new Input();
	}

	void Input::OnDestoy()
	{
		if (s_Instance)
		{
			s_Window = nullptr;
			delete s_Instance;
		}
	}

	float Input::GetAxis(Axis axis)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Search which axis. */
		switch (axis)
		{
			/* If none has been specified. */
			case Axis::None:
			{
				// Return Zero. */
				return 0.0f;
			}

			/* The keys (A or <-) or (D or ->) */
			case Axis::KeyboardHorizontal:
			{
				/* If there is a window. */
				if (s_Window)
				{
					/* Grab the Left and Right Values. */
					float rightValue = glfwGetKey(window, (int)Key::D) + glfwGetKey(window, (int)Key::RightArrow);
					float leftValue = glfwGetKey(window, (int)Key::A) + glfwGetKey(window, (int)Key::LeftArrow);

					/* Return 1 being fully Right and -1 being fully Left. */
					return (float)(glm::sign(rightValue) - glm::sign(leftValue));
				}

				return 0.0f;
			}

			/* The keys (W or /\) or (S or \/) */
			case Axis::KeyboardVertical:
			{
				/* If there is a window. */
				if (s_Window)
				{
					/* Grab the Up and Down Values. */
					float upValue = (float)glfwGetKey(window, (int)Key::W) + (float)glfwGetKey(window, (int)Key::UpArrow);
					float downValue = (float)glfwGetKey(window, (int)Key::S) + (float)glfwGetKey(window, (int)Key::DownArrow);

					/* Return 1 being fully Up and -1 being fully Down. */
					return (float)(glm::sign(upValue) - glm::sign(downValue));
				}

				return 0.0f;
			}

			/* If something random has been specified. */
			default:
			{
				/* Return Zero. */
				return 0.0f;
			}
		}
	}

	bool Input::GetKeyDown(Key key)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Get whether or not the Key is down. */
		return (bool)glfwGetKey(window, (int)key);
	}

	bool Input::GetKeyPressed(Key key)
	{
		// Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Get the Key status. */
		int keyPress = glfwGetKey(window, (int)key);

		/* Assume the Key is not pressed. */
		bool result = false;

		/* Check if it's last state was released and its pressed. */
		if (s_KeyStateCache[key] == GLFW_RELEASE && keyPress == GLFW_PRESS)
			result = true; /* We have pressed the Key. */

		/* Update the Cache. */
		s_KeyStateCache[key] = keyPress;
		 
		/* Return the Result. */
		return result;
	}

	bool Input::GetKeyReleased(Key key)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Get the Key status. */
		int keyRelease = glfwGetKey(window, (int)key);

		/* Assume the Key is not Released. */
		bool result = false;

		/* Check if it's last state was pressed and its released. */
		if (s_KeyStateCache[key] == GLFW_PRESS && keyRelease == GLFW_RELEASE)
			result = true; /* We have released the Key. */

		/* Update the Cache. */
		s_KeyStateCache[key] = keyRelease;

		/* Return the Result. */
		return result;
	}

	bool Input::GetMouseButtonDown(Mouse mouse)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* If the Mouse specified isn't none. */
		if (mouse != Mouse::None)
			return (bool)glfwGetMouseButton(window, (int)mouse); /* Get if the Mouse is down. */

		/* If nothing specified return false. */
		return false;
	}

	bool Input::GetMouseButtonPressed(Mouse mouse)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Get the Mouse status. */
		int mousePress = glfwGetMouseButton(window, (int)mouse);

		/* Assume the Mouse Button is not Pressed. */
		bool result = false;

		/* Check if it's last state was released and its pressed. */
		if (s_MouseStateCache[mouse] == GLFW_RELEASE && mousePress == GLFW_PRESS)
			result = true; /* We have pressed the Mouse Button. */

		/* Update the Cache. */
		s_MouseStateCache[mouse] = mousePress;

		/* Return the Result. */
		return result;
	}

	bool Input::GetMouseButtonReleased(Mouse mouse)
	{
		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Get the Mouse status. */
		int mouseRelease = glfwGetMouseButton(window, (int)mouse);

		/* Assume the Mouse Button is not Released. */
		bool result = false;

		/* Check if it's last state was pressed and its released. */
		if (s_MouseStateCache[mouse] == GLFW_PRESS && mouseRelease == GLFW_RELEASE)
			result = true; /* We have released the Mouse Button. */

		/* Update the Cache. */
		s_MouseStateCache[mouse] = mouseRelease;

		/* Return the Result. */
		return result;
	}

	Vector2 Input::GetMousePosition()
	{
		/* Quick Variables for getting the mouse position. */
		double x, y;

		/* Obtain the GLFW Window. */
		GLFWwindow* window = s_Window->GetGLFWWindow();

		/* Grab the Mouse position in WINDOW PIXEL SPACE. */
		glfwGetCursorPos(window, &x, &y);

		/* Return the Position. */
		return Vector2((float)x, (float)y);
	}

	float Input::GetControllerAxis(int controllerID, Controller axis, float deadZone)
	{
		/* Ask if the Controller is Connected. */
		if (ControllerConnected(controllerID))
		{
			/* Grab the Controller State. */
			GLFWgamepadstate state;

			/* Ask for what it's state currently is. */
			glfwGetGamepadState(controllerID, &state);

			/* Search the Axis Specified. */
			switch (axis)
			{
				/* Left Stick Horizontal. */
				case Controller::LeftStickHorizontal:
				{
					/* If the Stick is moving outside of the Dead Zone return the value of the stick. */
					if (state.axes[(int)Controller::LeftStickHorizontal] >= deadZone || state.axes[(int)Controller::LeftStickHorizontal] <= -deadZone)
						return state.axes[(int)Controller::LeftStickHorizontal];

					return 0.0f;
				}

				/* Left Stick Vertical. */
				case Controller::LeftStickVertical:
				{
					/* If the Stick is moving outside of the Dead Zone return the value of the stick. */
					if (state.axes[(int)Controller::LeftStickVertical] >= deadZone || state.axes[(int)Controller::LeftStickVertical] <= -deadZone)
						return -state.axes[(int)Controller::LeftStickVertical];

					return 0.0f;
				}

				/* Right Stick Horizontal. */
				case Controller::RightStickHorizontal:
				{
					/* If the Stick is moving outside of the Dead Zone return the value of the stick. */
					if (state.axes[(int)Controller::RightStickHorizontal] >= deadZone || state.axes[(int)Controller::RightStickHorizontal] <= -deadZone)
						return state.axes[(int)Controller::RightStickHorizontal];

					return 0.0f;
				}

				/* Right Stick Vertical. */
				case Controller::RightStickVertical:
				{
					/* If the Stick is moving outside of the Dead Zone return the value of the stick. */
					if (state.axes[(int)Controller::RightStickVertical] >= deadZone || state.axes[(int)Controller::RightStickVertical] <= -deadZone)
						return -state.axes[(int)Controller::RightStickVertical];

					return 0.0f;
				}

				/* Left Trigger. */
				case Controller::LeftTrigger:
				{
					/* Get how far pushing in the trigger is. */
					return state.axes[(int)Controller::LeftTrigger];
				}

				/* Right Trigger. */
				case Controller::RightTrigger:
				{
					/* Get how far pushing in the trigger is. */
					return state.axes[(int)Controller::RightTrigger];
				}

				/* Nothing. */
				default:
				{
					/* Return Zero. */
					return 0.0f;
				}
			}
		}

		return 0.0f;
	}

	bool Input::GetControllerButtonDown(int controllerID, Controller button)
	{
		/* Grab the Controller State. */
		GLFWgamepadstate state;

		/* Ask for what it's state currently is. */
		glfwGetGamepadState(controllerID, &state);

		/* Check if the button is down or not. */
		return (bool)state.buttons[(int)button];
	}

	bool Input::GetControllerButtonPressed(int controllerID, Controller button)
	{
		/* Grab the Controller State. */
		GLFWgamepadstate state;

		/* Ask for what it's state currently is. */
		glfwGetGamepadState(controllerID, &state);

		/* Get the Controller Button status. */
		int buttonPress = state.buttons[(int)button];

		/* Assume the Controller Button is not pressed. */
		bool result = false;

		/* Check if it's last state was released and its pressed. */
		if (s_ControllerStateCache[button] == GLFW_RELEASE && buttonPress == GLFW_PRESS)
			result = true; /* We have pressed the Controller Button. */

		/* Update the Cache. */
		s_ControllerStateCache[button] = buttonPress;

		/* Return the Result. */
		return result;
	}

	bool Input::GetControllerButtonReleased(int controllerID, Controller button)
	{
		/* Grab the Controller State. */
		GLFWgamepadstate state;

		/* Ask for what it's state currently is. */
		glfwGetGamepadState(controllerID, &state);

		/* Get the Controller Button status. */
		int buttonRelease = state.buttons[(int)button];

		/* Assume the Controller Button is not Released. */
		bool result = false;

		/* Check if it's last state was Pressed and its Released. */
		if (s_ControllerStateCache[button] == GLFW_PRESS && buttonRelease == GLFW_RELEASE)
			result = true; /* We have Released the Controller Button. */

		/* Update the Cache. */
		s_ControllerStateCache[button] = buttonRelease;

		/* Return the Result. */
		return result;
	}

	int Input::GetAvalibleController()
	{
		/* Run through all Controller Slots. */
		for (int i = 0; i < MaxControllerSlots(); ++i)
		{
			/* Check if the Controler is Connected. */
			if (ControllerConnected(i))
				return i; /* Return the Slot ID. */
		}

		/* Return NULL if none are connected. */
		return -1;
	}
}