/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#include "PlayerController.h"

#include "../Manager/SceneManager.h"
#include "../Manager/Time.h"
#include "../Application.h"

namespace Kross
{
	void PlayerController::OnStart()
	{
		/* Initializes the objects transform */
		transform = m_GameObject->m_Transform;
		transform->m_Position = Vector2(0.0f);

		/* Gets any avaliable controllers */
		controllerID = Input::GetAvalibleController();

		/* Assigns the rigidbody */
		rigidbody = GetComponent<Rigidbody2D>();

		/* Sets the camera */
		camera = SceneManager::GetCurrentScene()->GetCamera();

		Debug::Log("Position = ");
		Debug::Log(transform->m_Position);
		Debug::EndLine();
	}

	void PlayerController::OnUpdate()
	{
		Vector2 input = Vector2(0.0f);

		/* Checks if the player is using a controller or a mouse & keyboard */
		if (Input::ControllerConnected(controllerID))
		{
			input = Vector2(Input::GetControllerAxis(controllerID, Controller::LeftStickHorizontal, 0.2f), 0.0f);
		}
		else
		{
			controllerID = Input::GetAvalibleController();

			input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), 0.0f);
			
			if (Input::GetKeyPressed(Key::G))
			{
				SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
			}
		}

		/* Takes the player input and actions the inputs */
		PlayerMove(input, Key::Space, Key::W, Controller::A);
		
		/* Switches the gravity */
		EnableGravity(Key::Q, Controller::B);

		/* Gets the camera and player positions */
		Vector2 cameraPosition = camera->m_Transform->m_Position;
		Vector2 playerPosition = m_GameObject->m_Transform->m_Position;

		/* Moves the camera based on the players position */
		camera->m_Transform->m_Position = Math::Lerp(cameraPosition, playerPosition, Time::GetDeltaTime() * 4.0f);

		/* Clamps the mins and maxes for the camera */
		camera->m_Transform->m_Position.x = glm::clamp(camera->m_Transform->m_Position.x, -1.25f, 178.75f);
		camera->m_Transform->m_Position.y = glm::clamp(camera->m_Transform->m_Position.y, -2.0f, 1.5f);
	}

	void PlayerController::PlayerMove(Vector2 input, Key jump, Key jump2, Controller jumpC)
	{
		/* Checks the player input and players states */
		if (rigidbody->GetRigidbodyState() != RigidbodyState::Falling &&
			Input::GetKeyPressed(jump) || Input::GetKeyPressed(jump2) || Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, jumpC))
		{
			if (jumpCount < 1)
			{
				/* Applys a jump impulse */
				rigidbody->OnApplyImpulse(Vector2(0.0f, 1.0f) * m_JumpStrength);
				jumpCount++;
			}
		}

		if (jumpCount == 0)
		{
			/* Applys force when on the ground*/
			if (input.x < 0 && rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxGroundSpeed)
			{
				rigidbody->OnApplyForce(input);
			}
			else if (input.x > 0 && rigidbody->GetBody()->GetLinearVelocity().x < m_MaxGroundSpeed)
			{
				rigidbody->OnApplyForce(input);
			}
			else
			{
				rigidbody->OnApplyForce(input * 0.1f);
			}
		}
		else
		{
			/* Applys force while the player is in the air */
			if (input.x < 0 && rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxAirSpeed)
			{
				rigidbody->OnApplyForce(input * 0.65f);
			}
			else if (input.x > 0 && rigidbody->GetBody()->GetLinearVelocity().x < m_MaxAirSpeed)
			{
				rigidbody->OnApplyForce(input * 0.65f);
			}
			else
			{
				rigidbody->OnApplyForce(input * 0.1f);
			}
		}
	}

	void PlayerController::EnableGravity(Key key, Controller button)
	{
		/* Checks the input to turn on gravity */
		if (Input::GetKeyPressed(key) || (Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, button)))
		{
			SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
		}
	}

	void PlayerController::OnCollisionEnter(Object* other)
	{
		/* Sets the jump count if they land on the ground or an enemy */
		if (other->GetLayer() == Layer::Ground ||
			other->GetLayer() == Layer::Player)
		{
			jumpCount = 0;
		}

		Debug::LogLine("Entered collision with " + other->GetName());
	}

	void PlayerController::OnCollisionStay(Object* other)
	{
		/* Sets the jump count if they stay on the ground or an enemy */
		if (other->GetLayer() == Layer::Ground ||
			other->GetLayer() == Layer::Player)
		{
			jumpCount = 0;
		}
	}

	void PlayerController::OnCollisionExit(Object* other)
	{
		/* Sets the jump count if they leave the ground or an enemy */
		if (other->GetLayer() == Layer::Ground ||
			other->GetLayer() == Layer::Player)
		{
			if (jumpCount == 0)
			{
				jumpCount++;
			}
		}

		Debug::LogLine((std::string)"Exited collision with " + other->GetName());
	}

}