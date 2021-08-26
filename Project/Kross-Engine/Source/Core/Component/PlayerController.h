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
	class KROSS_API PlayerController : public Component
	{
	private:
		Transform2D* transform;
		Rigidbody2D* rigidbody;


		Object* camera;

		int jumpCount = 0;

		int controllerID = 0;

		float m_MaxGroundSpeed = 3.75f;
		float m_MaxAirSpeed = 4.75f;
		float m_JumpStrength = 0.4f;


	protected:
		friend class Rigidbody2D;

		void OnStart() override;

		void OnUpdate() override;

	public:
		PlayerController() :
			transform	(nullptr),
			camera		(nullptr),
			rigidbody	(nullptr)
		{};
		~PlayerController() {};

		void PlayerMove(Vector2 input, Key jump, Key jump2, Controller jumpC);

		void EnableGravity(Key key, Controller button);

		void OnCollisionEnter(Object* other);
		void OnCollisionStay(Object* other);
		void OnCollisionExit(Object* other);

		int GetControllerID() { return controllerID; }
	};
}