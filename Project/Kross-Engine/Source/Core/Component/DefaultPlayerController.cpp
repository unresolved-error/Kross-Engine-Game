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

		//audplayer = GetComponent<AudioPlayer>();
		//audplayer->SetAudioSource(ResourceManager::GetResource<AudioSource>("Bullet-Proof"));
		//audplayer->SetLoop(true);

		camera = SceneManager::GetCurrentScene()->GetCamera();

		
	}

	void DefaultPlayerController::OnUpdate()
	{
		Vector2 input = Vector2(0.0f);

		Debug::Log("Position = ");
		Debug::Log(transform->m_Position);
		Debug::EndLine();

		if (Input::ControllerConnected(controllerID))
		{
			input = Vector2(Input::GetControllerAxis(controllerID, Controller::LeftStickHorizontal, 0.2f), 0.0f);

			//if (input.x == 0.0f && input.y == 0.0f)
			//{
			//	animator->SetCurrentAnimation(0);
			//}
			//else
			//{
			//	animator->SetCurrentAnimation(1);
			//}
			//
			//if (Input::GetControllerButtonPressed(controllerID, Controller::A))
			//{
			//	if (jumpCount < 1)
			//	{
			//		rigidBody->OnApplyImpulse(Vector2(0.0f, 1.0f) * m_JumpStrength);
			//		jumpCount++;
			//	}
			//}
			//
			//if (Input::GetControllerButtonPressed(controllerID, Controller::RightStick))
			//{
			//	followPlayer = !followPlayer;
			//}
			//
			//if (Input::GetControllerAxis(controllerID, Controller::LeftTrigger, 0.9f) > 0.9f)
			//{
			//	Object* newbie = OnCreateObject("Newbie", GetLinkObject()->GetTransform()->m_Position, Random::GetRandomRange<float>(0.0f, 360.0f));
			//	newbie->SetLayer(Layer::Default);
			//	newbie->AttachComponent<SpriteRenderer>();
			//
			//	newbie->SetStaticStatus(true);
			//
			//	SpriteRenderer* ren = newbie->GetComponent<SpriteRenderer>();
			//	ren->SetMaterial(ResourceManager::GetResource<Material>("Default"));
			//	ren->SetDepth(20);
			//}
			//
			//if (Input::GetControllerButtonPressed(controllerID, Controller::DPadUp))
			//{
			//	Window* window = Application::GetWindow();
			//	if (window->GetFullscreen() == 0)
			//	{
			//		window->SetFullscreen(1);
			//	}
			//	else
			//	{
			//		window->SetFullscreen(0);
			//	}
			//}
		}
		else
		{
			controllerID = Input::GetAvalibleController();

			input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), 0.0f);

			//pan += (float)((int)Input::GetKeyDown(Key::E) - (int)Input::GetKeyDown(Key::Q)) / 100.0f;
			//volume += (float)((int)Input::GetKeyDown(Key::UpArrow) - (int)Input::GetKeyDown(Key::DownArrow)) / 1000.0f;
			//audplayer->SetPan(pan);
			
			//if (Input::GetKeyPressed(Key::P))
			//{
			//	if (audplayer->IsPlaying())
			//		audplayer->Pause();
			
			//	else
			//		audplayer->Play();
			//}
			
			//if (Input::GetKeyPressed(Key::S))
			//{
			//	if (audplayer->IsPlaying())
			//		audplayer->Stop();
			//}
			
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

		//Vector2 cameraPosition = camera->GetTransform()->m_Position;
		//Vector2 playerPosition = c_Object->GetTransform()->m_Position;

		//camera->GetTransform()->m_Position.x = Math::Lerp(cameraPosition.x, playerPosition.x, Time::GetDeltaTime() * 4.0f);
		//camera->GetTransform()->m_Position.y = Math::Lerp(cameraPosition.y, playerPosition.y, Time::GetDeltaTime() * 4.0f);

		//camera->GetTransform()->m_Position = Math::Lerp(cameraPosition, playerPosition, Time::GetDeltaTime() * 4.0f);

		//camera->GetTransform()->m_Position.x = glm::clamp(camera->GetTransform()->m_Position.x, -1.25f, 178.75f);
		//camera->GetTransform()->m_Position.y = glm::clamp(camera->GetTransform()->m_Position.y, -2.0f, 1.5f);

		//if (gun)
		//{
		//	Vector2 trueOffset;
		//	if (renderer->GetFlipX())
		//	{
		//		trueOffset = Vector2(-1.0f, 1.0f);
		//	}
		//	else
		//	{
		//		trueOffset = Vector2(1.0f, 1.0f);
		//	}
		//	gun->GetTransform()->m_Position = c_Object->GetTransform()->m_Position + (gunOffset * trueOffset);
		//}
		//
		//if (timeElapsed < 1.0f)
		//{
		//	timeElapsed += Time::GetDeltaTime();
		//	frameCount++;
		//}

		//if (text)
		//{
		//	if (playerPosition.x < 170)
		//	{
		//		Colour textcol = text->GetComponent<TextRenderer>()->GetColour();
		//		textcol.a = 0;
		//		text->GetComponent<TextRenderer>()->SetColour(textcol);
		//	}
		//	else if (playerPosition.x < 179.9)
		//	{
		//		float alph = (playerPosition.x - 170) / 10;
		//		Colour textcol = text->GetComponent<TextRenderer>()->GetColour();
		//		textcol.a = alph;
		//		text->GetComponent<TextRenderer>()->SetColour(textcol);
		//
		//	}
		//
		//	text->GetTransform()->m_Position = c_Object->GetTransform()->m_Position + Vector2(0.0f, 1.5f);
		//
		//}

		//if (timeElapsed >= 1.0f)
		//{
		//	timeElapsed = 0.0f;
		//	//if(text)
		//	//{
		//	//	text->GetComponent<TextRenderer>()->SetText(std::to_string(frameCount));
		//	//}
		//	frameCount = 0;
		//}
	}

	void DefaultPlayerController::PlayerMove(Vector2 input, Key jump, Controller jumpC)
	{
		//if (rigidbody->GetBody()->GetLinearVelocity().y <= 0.05f && rigidbody->GetBody()->GetLinearVelocity().y >= -0.05f)
		//{
		//	if (rigidbody->GetBody()->GetLinearVelocity().x <= 0.05f && rigidbody->GetBody()->GetLinearVelocity().x >= -0.05f)
		//	{
		//		animator->SetCurrentAnimation(0);
		//	}
		//	else
		//	{
		//		animator->SetCurrentAnimation(1);
		//	}
		//}
		//else
		//{
		//	if (rigidbody->GetBody()->GetLinearVelocity().y >= 0.05f)
		//	{
		//		animator->SetCurrentAnimation(2);
		//	}
		//	else if (rigidbody->GetBody()->GetLinearVelocity().y <= -0.05f)
		//	{
		//		animator->SetCurrentAnimation(3);
		//	}
		//}
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

		//if (input.x > 0)
		//{
		//	renderer->SetFlipX(false);
		//}
		//else if (input.x < 0)
		//{
		//	renderer->SetFlipX(true);
		//}
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