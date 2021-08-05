#pragma once

#include <Kross.h>

using namespace Kross;

class PlayerMovement : public Script
{
public:
	PlayerMovement() :
		transform(nullptr),
		renderer(nullptr),
		window(nullptr),
		rigidBody(nullptr),
		animator(nullptr),
		camera(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "PlayerMovement";
	};
	~PlayerMovement() {};

	Transform2D* transform;
	SpriteRenderer* renderer;
	Window* window;
	Rigidbody2D* rigidBody;

	AudioPlayer* audplayer = nullptr;

	Animator* animator;

	Object* camera;
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
	float m_MaxAirSpeed = 5.5f;
	float m_JumpStrength = 0.55f;

	Script* Duplicate() override
	{
		return KROSS_NEW PlayerMovement();
	}

	void Start() override
	{
		transform = c_Object->GetTransform();
		transform->m_Position = Vector2(0.0f);
		renderer = GetComponent<SpriteRenderer>();
		window = Application::GetWindow();

		controllerID = Input::GetAvalibleController();

		rigidBody = GetComponent<Rigidbody2D>();

		animator = GetComponent<Animator>();

		text = SceneManager::GetCurrentScene()->FindObject("Text");

		Material* defaultMaterial = Material::OnCreate("Default");
		defaultMaterial->SetDiffuse(ResourceManager::GetResource<Sprite>(0));

		audplayer = GetComponent<AudioPlayer>();
		audplayer->SetAudioSource(ResourceManager::GetResource<AudioSource>("Bullet-Proof"));
		audplayer->SetLoop(true);
		audplayer->Play();

		camera = SceneManager::GetCurrentScene()->GetCamera();

		Debug::Log(((Object*)c_Object)->GetName() + " Position =");
		Debug::Log(transform->m_Position);
		Debug::EndLine();
	}

	void Update() override
	{
		Vector2 input = Vector2(0.0f);

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

			pan += (float)((int)Input::GetKeyDown(Key::E) - (int)Input::GetKeyDown(Key::Q)) / 100.0f;
			volume += (float)((int)Input::GetKeyDown(Key::UpArrow) - (int)Input::GetKeyDown(Key::DownArrow)) / 1000.0f;
			audplayer->SetPan(pan);

			if (Input::GetKeyPressed(Key::P))
			{
				if (audplayer->IsPlaying())
					audplayer->Pause();

				else
					audplayer->Play();
			}

			if (Input::GetKeyPressed(Key::S))
			{
				if (audplayer->IsPlaying())
					audplayer->Stop();
			}

			if (Input::GetKeyPressed(Key::G))
			{
				SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
			}
		}

		PlayerMove(input, Key::Space, Controller::A);
		EnableGravity(Key::Q, Controller::B);

		Vector2 cameraPosition = camera->GetTransform()->m_Position;
		Vector2 playerPosition = c_Object->GetTransform()->m_Position;

		

		camera->GetTransform()->m_Position.x = Math::Lerp(cameraPosition.x, playerPosition.x, Time::GetDeltaTime() * 4.0f);
		camera->GetTransform()->m_Position.y = Math::Lerp(cameraPosition.y, playerPosition.y, Time::GetDeltaTime() * 4.0f);


		//camera->GetTransform()->m_Position.x = glm::clamp(camera->GetTransform()->m_Position.x, m_MinX, m_MaxX);
		camera->GetTransform()->m_Position.y = glm::clamp(camera->GetTransform()->m_Position.y, -2.0f, 1.5f);

		if (timeElapsed < 1.0f)
		{
			timeElapsed += Time::GetDeltaTime();
			frameCount++;
		}

		if (text)
		{
			text->GetTransform()->m_Position = c_Object->GetTransform()->m_Position + Vector2(0.0f, 1.5f);
			text->GetComponent<TextRenderer>()->SetText("");
		}

		if (timeElapsed >= 1.0f)
		{
			timeElapsed = 0.0f;
			//if(text)
			//	text->GetComponent<TextRenderer>()->SetText(std::to_string(frameCount));
			frameCount = 0;
		}

	}

	void PlayerMove(Vector2 input, Key jump, Controller jumpC)
	{
		if (rigidBody->GetBody()->GetLinearVelocity().y <= 0.05f && rigidBody->GetBody()->GetLinearVelocity().y >= -0.05f)
		{
			if (rigidBody->GetBody()->GetLinearVelocity().x <= 0.05f && rigidBody->GetBody()->GetLinearVelocity().x >= -0.05f)
			{
				animator->SetCurrentAnimation(0);
			}
			else
			{
				animator->SetCurrentAnimation(1);
			}
		}
		else
		{
			if (rigidBody->GetBody()->GetLinearVelocity().y >= 0.05f)
			{
				animator->SetCurrentAnimation(2);
			}

			else if(rigidBody->GetBody()->GetLinearVelocity().y <= -0.05f)
			{
				animator->SetCurrentAnimation(3);
			}
		}

		if ((rigidBody->GetPlayerState() != PlayerState::Jumping && rigidBody->GetPlayerState() != PlayerState::Falling) &&
			(Input::GetKeyPressed(jump) || (Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, jumpC))))
		{
			if (jumpCount < 1)
			{
				rigidBody->OnApplyImpulse(Vector2(0.0f, 1.0f) * m_JumpStrength);
				jumpCount++;
			}
		}

		if (jumpCount == 0)
		{
			if (rigidBody->GetBody()->GetLinearVelocity().x < m_MaxGroundSpeed && rigidBody->GetBody()->GetLinearVelocity().x > -m_MaxGroundSpeed)
			{
				rigidBody->OnApplyForce(input);
			}
		}
		else
		{
			if (rigidBody->GetBody()->GetLinearVelocity().x < m_MaxAirSpeed && rigidBody->GetBody()->GetLinearVelocity().x > -m_MaxAirSpeed)
			{
				rigidBody->OnApplyForce(input * 3.0f);
			}
		}

		if (input.x > 0)
		{
			renderer->SetFlipX(false);
		}
		else if (input.x < 0)
		{
			renderer->SetFlipX(true);
		}
	}

	void EnableGravity(Key key, Controller button)
	{
		if (Input::GetKeyPressed(key) || (Input::ControllerConnected(controllerID) &&
			Input::GetControllerButtonPressed(controllerID, button)))
		{
			SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
		}
	}

	void OnCollisionEnter(Object* other)
	{
		if (other->GetLayer() == Layer::Ground)
		{
			jumpCount = 0;
		}

		Debug::LogLine("Entered collision with " + other->GetName());
	}

	void OnCollisionStay(Object* other)
	{
		if (other->GetLayer() == Layer::Ground)
		{
			jumpCount = 0;
		}
		//std::cout << "Continued colliding with " << other->GetName() << std::endl;
	}

	void OnCollisionExit(Object* other)
	{
		if (other->GetLayer() == Layer::Ground)
		{
			if (jumpCount == 0)
				jumpCount++;
		}

		Debug::LogLine((std::string)"Exited collision with " + other->GetName());
	}

};