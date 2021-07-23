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
		camera(nullptr),
		textObj(nullptr)
	{};
	~PlayerMovement() {};

	Transform2D* transform;
	SpriteRenderer* renderer;
	Window* window;
	Rigidbody2D* rigidBody;

	AudioPlayer* audplayer = nullptr;

	Animator* animator;

	Camera* camera;
	TextRenderer* textObj;

	bool followPlayer = false;

	bool isGrounded = false;
	int jumpCount = 0;

	float moveSpeed = 10;

	int controllerID = 0;

	float pan = 0.0f;

	float timeElapsed = 0.0f;

	int frameCount = 0;

	float m_MaxGroundSpeed = 4.0f;
	float m_MaxAirSpeed = 5.5f;
	float m_JumpStrength = 0.4f;

	void Start() override
	{
		transform = GetLinkObject()->GetTransform();
		transform->m_Position = Vector2(0.0f);
		renderer = GetLinkObject()->GetComponent<SpriteRenderer>();
		window = Application::GetWindow();

		controllerID = Input::GetAvalibleController();

		animator = GetLinkObject()->GetComponent<Animator>();

		Material* defaultMaterial = Material::OnCreate("Default");
		defaultMaterial->p_Diffuse = ResourceManager::GetResource<Sprite>(0);

		audplayer = GetLinkObject()->GetComponent<AudioPlayer>();

		Debug::Log(GetLinkObject()->GetName() + " Position =");
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
		}

		PlayerMove(input, Key::Space, Controller::A);
		EnableGravity(Key::Q, Controller::B);

		camera->GetLinkObject()->GetTransform()->m_Position = GetLinkObject()->GetTransform()->m_Position;

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

	void PlayerMove(Vector2 input, Key jump, Controller jumpC)
	{
		audplayer->SetVolume(0.33f);

		if (rigidBody->GetBody()->GetLinearVelocity().x == 0.0f)
		{
			animator->SetCurrentAnimation(0);
		}
		else
		{
			animator->SetCurrentAnimation(1);
		}

		animator->OnStop();

		if (Input::GetKeyPressed(jump) || (Input::ControllerConnected(controllerID) && Input::GetControllerButtonPressed(controllerID, jumpC)))
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
				rigidBody->OnApplyForce(input);
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
		if (Input::GetKeyPressed(key) || (Input::ControllerConnected(controllerID) && Input::GetControllerButtonPressed(controllerID, button)))
		{
			SceneManager::GetCurrentScene()->SetGravity(9.81f, Vector2(0.0f, -1.0f));
		}
	}
};