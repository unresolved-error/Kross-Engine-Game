/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Input.h"

namespace Kross
{
	class KROSS_API DefaultPlayerController : public Component
	{
	private:
		Transform2D* transform;
		Window* window;
		Rigidbody2D* rigidbody;


		Vector2 gunOffset = Vector2(0.0f, -0.11f);

		Object* camera;
		Object* gun;
		Object* text;

		bool followPlayer = false;

		bool isGrounded = false;
		int jumpCount = 0;

		float moveSpeed = 10;

		int controllerID = 0;

		float pan = 0.0f;
		float volume = 1.0f;

		float timeElapsed = 0.0f;

		int frameCount = 0;

		float m_MaxGroundSpeed = 3.75f;
		float m_MaxAirSpeed = 4.75f;
		float m_JumpStrength = 0.4f;


	protected:
		friend class Rigidbody2D;

		void OnStart() override;

		void OnUpdate() override;

	public:
		DefaultPlayerController() :
			window		(nullptr),
			transform	(nullptr),
			camera		(nullptr),
			gun			(nullptr),
			text		(nullptr),
			rigidbody	(nullptr)
		{};
		~DefaultPlayerController() {};

		void PlayerMove(Vector2 input, Key jump, Controller jumpC);

		void EnableGravity(Key key, Controller button);

		void OnCollisionEnter(Object* other);
		void OnCollisionStay(Object* other);
		void OnCollisionExit(Object* other);

		int GetControllerID() { return controllerID; }
	};
}