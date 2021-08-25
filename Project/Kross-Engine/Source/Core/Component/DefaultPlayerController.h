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
		//SpriteRenderer* renderer;
		Window* window;
		Rigidbody2D* rigidbody;

		//AudioPlayer* audplayer = nullptr;

		//Animator* animator;

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

		float m_MaxGroundSpeed = 4.0f;
		float m_MaxAirSpeed = 5.25f;
		float m_JumpStrength = 0.4f;


	protected:
		friend class Rigidbody2D;

		void OnStart() override;

		void OnUpdate() override;

	public:
		DefaultPlayerController() :
			//renderer	(nullptr),
			window		(nullptr),
			transform	(nullptr),
			//animator	(nullptr),
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