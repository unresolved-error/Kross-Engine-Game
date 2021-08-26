#include "DefaultPlayerController.h"
/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "../Manager/SceneManager.h"
#include "../Manager/Time.h"
#include "../Application.h"

namespace Kross
{
	void DefaultPlayerController::OnStart()
	{
		transform = c_Object->GetTransform();
		transform->m_Position = Vector2(0.0f);
		window = Application::GetWindow();

		controllerID = Input::GetAvalibleController();

		rigidbody = GetComponent<Rigidbody2D>();

		text = SceneManager::GetCurrentScene()->FindObject("Text");
		gun = SceneManager::GetCurrentScene()->FindObject("Gun");

		Material* defaultMaterial = Material::OnCreate("Default");
		defaultMaterial->SetDiffuse(ResourceManager::GetResource<Sprite>(0));

		camera = SceneManager::GetCurrentScene()->GetCamera();

		Debug::Log("Position = ");
		Debug::Log(transform->m_Position);
		Debug::EndLine();
	}

	void DefaultPlayerController::OnUpdate()
	{
		Vector2 input = Vector2(0.0f);


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

		if (transform->m_Position.x < 180)
		{
			PlayerMove(input, Key::Space, Controller::A);
		}
		EnableGravity(Key::Q, Controller::B);

		Vector2 cameraPosition = camera->GetTransform()->m_Position;
		Vector2 playerPosition = c_Object->GetTransform()->m_Position;

		//camera->GetTransform()->m_Position.x = Math::Lerp(cameraPosition.x, playerPosition.x, Time::GetDeltaTime() * 4.0f);
		//camera->GetTransform()->m_Position.y = Math::Lerp(cameraPosition.y, playerPosition.y, Time::GetDeltaTime() * 4.0f);

		camera->GetTransform()->m_Position = Math::Lerp(cameraPosition, playerPosition, Time::GetDeltaTime() * 4.0f);

		camera->GetTransform()->m_Position.x = glm::clamp(camera->GetTransform()->m_Position.x, -1.25f, 178.75f);
		camera->GetTransform()->m_Position.y = glm::clamp(camera->GetTransform()->m_Position.y, -2.0f, 1.5f);

		if (text)
		{
			if (playerPosition.x < 170)
			{
				Colour textcol = text->GetComponent<TextRenderer>()->GetColour();
				textcol.a = 0;
				text->GetComponent<TextRenderer>()->SetColour(textcol);
			}
			else if (playerPosition.x < 179.9)
			{
				float alph = (playerPosition.x - 170) / 10;
				Colour textcol = text->GetComponent<TextRenderer>()->GetColour();
				textcol.a = alph;
				text->GetComponent<TextRenderer>()->SetColour(textcol);
		
			}
		
			text->GetTransform()->m_Position = c_Object->GetTransform()->m_Position + Vector2(0.0f, 1.5f);
		
		}

	}

	void DefaultPlayerController::PlayerMove(Vector2 input, Key jump, Controller jumpC)
	{
		if (rigidbody->GetRigidbodyState() != RigidbodyState::Falling &&
			Input::GetKeyPressed(jump) || Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, jumpC))
		{
			for (b2ContactEdge* thisContact = rigidbody->GetBody()->GetContactList(); thisContact; thisContact = thisContact->next)
			{
				if (thisContact->other == rigidbody->GetRaycastData()->body)
				{
					if (jumpCount < 1)
					{
						rigidbody->OnApplyImpulse(Vector2(0.0f, 1.0f) * m_JumpStrength);
						jumpCount++;
						break;
					}
				}
			}
		}

		if (jumpCount == 0)
		{

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
			if (input.x < 0 && rigidbody->GetBody()->GetLinearVelocity().x > -m_MaxAirSpeed)
			{
				rigidbody->OnApplyForce(input);
			}
			else if (input.x > 0 && rigidbody->GetBody()->GetLinearVelocity().x < m_MaxAirSpeed)
			{
				rigidbody->OnApplyForce(input);
			}
			else
			{
				rigidbody->OnApplyForce(input * 0.1f);
			}
		}

	}

	void DefaultPlayerController::EnableGravity(Key key, Controller button)
	{
		if (Input::GetKeyPressed(key) || (Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, button)))
		{
			SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
		}
	}

	void DefaultPlayerController::OnCollisionEnter(Object* other)
	{
		if (other->GetLayer() == Layer::Ground ||
			other->GetLayer() == Layer::Player)
		{
			jumpCount = 0;
		}

		Debug::LogLine("Entered collision with " + other->GetName());
	}

	void DefaultPlayerController::OnCollisionStay(Object* other)
	{
		if (other->GetLayer() == Layer::Ground ||
			other->GetLayer() == Layer::Player)
		{
			jumpCount = 0;
		}
	}

	void DefaultPlayerController::OnCollisionExit(Object* other)
	{
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