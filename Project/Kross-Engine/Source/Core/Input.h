/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

#include "Math/Math.h"
#include "Window/Window.h"

#include "Debug.h"

#include "GLFW/glfw3.h"

namespace Kross
{
	enum class KROSS_API Axis
	{
		None,
		KeyboardHorizontal,
		KeyboardVertical,
	};

	enum class KROSS_API Mouse
	{
		None,
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Middle = GLFW_MOUSE_BUTTON_MIDDLE,
		Right = GLFW_MOUSE_BUTTON_RIGHT,
	};

	enum class KROSS_API Key
	{
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,

		Zero = GLFW_KEY_0,
		One = GLFW_KEY_1,
		Two = GLFW_KEY_2,
		Three = GLFW_KEY_3,
		Four = GLFW_KEY_4,
		Five = GLFW_KEY_5,
		Six = GLFW_KEY_6,
		Seven = GLFW_KEY_7,
		Eight = GLFW_KEY_8,
		Nine = GLFW_KEY_9,

		Tab = GLFW_KEY_TAB,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		Space = GLFW_KEY_SPACE,
		Enter = GLFW_KEY_ENTER,
		Backspace = GLFW_KEY_BACKSPACE,
		Escape = GLFW_KEY_ESCAPE,
		UpArrow = GLFW_KEY_UP,
		DownArrow = GLFW_KEY_DOWN,
		LeftArrow = GLFW_KEY_LEFT,
		RightArrow = GLFW_KEY_RIGHT,
		Insert = GLFW_KEY_INSERT,
		Delete = GLFW_KEY_DELETE,
		End = GLFW_KEY_END,
		Home = GLFW_KEY_HOME,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,

		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12
	};

	enum class KROSS_API Controller
	{
		A = GLFW_GAMEPAD_BUTTON_A,
		B = GLFW_GAMEPAD_BUTTON_B,
		X = GLFW_GAMEPAD_BUTTON_X,
		Y = GLFW_GAMEPAD_BUTTON_Y,

		Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,
		Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,
		Square = GLFW_GAMEPAD_BUTTON_SQUARE,
		Cross = GLFW_GAMEPAD_BUTTON_CROSS,

		Start = GLFW_GAMEPAD_BUTTON_START,
		Select = GLFW_GAMEPAD_BUTTON_BACK,
		Home = GLFW_GAMEPAD_BUTTON_GUIDE,

		LeftStickHorizontal = GLFW_GAMEPAD_AXIS_LEFT_X,
		LeftStickVertical = GLFW_GAMEPAD_AXIS_LEFT_Y,
		RightStickHorizontal = GLFW_GAMEPAD_AXIS_RIGHT_X,
		RightStickVertical = GLFW_GAMEPAD_AXIS_RIGHT_Y,

		LeftStick = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		RightStick = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

		DPadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
		DPadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
		DPadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
		DPadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,

		LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		LeftShoulder = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
		RightShoulder = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
	};

	class KROSS_API Input
	{
	private:
		Input() {}
		~Input() {}

		static Input* s_Instance;
		static Window* s_Window;

		static float s_Scroll;

		static std::unordered_map<Key, int> s_KeyStateCache;
		static std::unordered_map<Controller, int> s_ControllerStateCache;
		static std::unordered_map<Mouse, int> s_MouseStateCache;

	protected:
		friend class Application;

		friend void ScrollCallback(GLFWwindow* window, double x, double y);

		// Creates an Instance of the Input Manager.
		static void OnCreate();

		// Destroys the Instance of the Input Manager.
		static void OnDestoy();

		// Sets the Input Window, to grab events from the Window.
		static void SetWindow(Window* window);

		// Sets the Scroll Wheel Value.
		static void SetScrollValue(float value) { s_Scroll = value; };

	public:
		/* ---- AXIS ---- */

		// Gets the Input Read from the Axis.
		static float GetAxis(Axis axis);

		// Gets the Input Read from the Controller Axis.
		static float GetControllerAxis(int controllerID, Controller axis, float deadZone);

		/* -------------- */

		/* ---- KEYS ---- */

		// Gets whether or not the Key is Down. 
		static inline bool GetKeyDown(Key key);

		// Gets whether or not the Key is Pressed.
		static inline bool GetKeyPressed(Key key);

		// Gets whether or not the Key is Released.
		static inline bool GetKeyReleased(Key key);

		/* -------------- */

		/* --- MOUSE ---- */

		// Gets whether or not the Mouse Button is Down.
		static inline bool GetMouseButtonDown(Mouse mouse);

		// Gets whether or not the Mouse Button is Pressed.
		static inline bool GetMouseButtonPressed(Mouse mouse);

		// Gets whether or not the Mouse Button is Released.
		static inline bool GetMouseButtonReleased(Mouse mouse);

		// gets the Scroll of the Mouse Input.
		static inline float GetMouseScroll();

		// Gets the Mouse Position.
		static Vector2 GetMousePosition();

		/* -------------- */

		/* - CONTROLLER - */

		// Gets whether or not the Controller Button is Down.
		static inline bool GetControllerButtonDown(int controllerID, Controller button);

		// Gets whether or not the Controller Button is Pressed.
		static inline bool GetControllerButtonPressed(int controllerID, Controller button);

		// Gets whether or not the Controller Button is Released.
		static inline bool GetControllerButtonReleased(int controllerID, Controller button);

		// Gets if the  Controller Slot is Connected.
		static inline bool ControllerConnected(int controllerID) { return (bool)glfwJoystickIsGamepad(controllerID); };

		// Gets an Active Controller Slot.
		static inline int GetAvalibleController();

		// Gets the Max Number of Controller Slots.
		static inline int MaxControllerSlots() { return GLFW_JOYSTICK_16 + 1; };

		/* -------------- */
	};


	void ScrollCallback(GLFWwindow* window, double x, double y);
}