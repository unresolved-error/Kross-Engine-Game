#pragma once

#include <Kross.h>

using namespace Kross;

class PlayerMovement : public Script
{
public:
	PlayerMovement() {};
	~PlayerMovement() {};

	Transform2D* transform;
	SpriteRenderer* renderer;
	Window* window;
	Rigidbody2D* rigidBody;

	Camera* camera;
	TextRenderer* textObj;

	bool followPlayer = false;

	bool isGrounded = false;
	int jumpCount = 0;

	float moveSpeed = 5;

	int controllerID;

	float previousTime = 0.0f;
	float actualTime;

	int frameCount;

	void Start() override
	{
		transform = GetObject()->GetTransform();
		renderer = GetObject()->GetComponent<SpriteRenderer>();
		window = Application::GetWindow();

		controllerID = Input::GetAvalibleController();

		previousTime = Time::GetDeltaTime();
	}


	void Update() override
	{
		Vector2 input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), Input::GetAxis(Axis::KeyboardVertical));
		rigidBody->OnApplyForce(input * 0.5f);

		if (Input::GetKeyPressed(Key::Space))
		{
			if (jumpCount < 2)
			{
				rigidBody->OnApplyImpulse(Vector2(0.0f, 1.5f) * 0.35f);
				jumpCount++;
			}
		}

		if (Input::GetControllerButtonPressed(controllerID, Controller::A))
			rigidBody->OnApplyImpulse(Vector2(0.0f, 1.0f) * 0.75f);

		if (Input::GetKeyDown(Key::Backspace))
			textObj->SetText("Deklyn");

		if (Input::GetKeyDown(Key::Q))
		{
			std::cout << SceneManager::GetCurrentScene()->GetObjectCount() << std::endl;
		}

		//if (Input::GetKeyPressed(Key::E))dddddddddddddd
		//	followPlayer = !followPlayer;

		if (Input::GetControllerButtonPressed(controllerID, Controller::RightStick))
			followPlayer = !followPlayer;

		if (Input::GetControllerButtonPressed(controllerID, Controller::X))
			textObj->SetFont(ResourceManager::GetResource<Font>(0));

		else if (Input::GetControllerButtonPressed(controllerID, Controller::Y))
			textObj->SetFont(ResourceManager::GetResource<Font>(1));

		if (Input::GetKeyDown(Key::Enter))
		{
			Object* newbie = OnCreateObject("Newbie", GetObject()->GetTransform()->m_Position, Random::GetRandomRange<float>(0.0f, 360.0f));
			newbie->AttachComponent<SpriteRenderer>();

			newbie->SetStaticStatus(true);

			SpriteRenderer* ren = newbie->GetComponent<SpriteRenderer>();
			ren->SetSprite(ResourceManager::GetResource<Sprite>(0));
			ren->SetDepth(20);
		}

		textObj->GetObject()->GetTransform()->m_Position = transform->m_Position + Vector2(0.0f, 0.25f);

		if (followPlayer)
		{
			Transform2D* cameraTransform = camera->GetObject()->GetTransform();

			Vector2 direction = Vector2(0.0f);
			float speed = 0.05f;

			Vector2 distance = (cameraTransform->m_Position - transform->m_Position);
			Vector2 directionNorm = glm::normalize(transform->m_Position - cameraTransform->m_Position);
			
			float actualDistance = sqrt((distance.x * distance.x) + (distance.y * distance.y));

			if(actualDistance > speed)
				cameraTransform->m_Position += directionNorm * speed;

			else
				cameraTransform->m_Position = transform->m_Position;
		}

		if (input.x > 0)
			renderer->SetFlipX(false);
		else if (input.x < 0)
			renderer->SetFlipX(true);
	}

	void OnCollisionEnter(Object* other)
	{
		//isGrounded = true;
		
		if (other->GetLayer() == Layer::Ground)
			jumpCount = 0;

		std::cout << "Entered collision with " << other->GetName() << std::endl;
	}

	void OnCollisionStay(Object* other)
	{
		//std::cout << "Continued colliding with " << other->GetName() << std::endl;
	}
	
	void OnCollisionExit(Object* other)
	{
		if (other->GetLayer() == Layer::Ground)
		{
			if (jumpCount == 0)
				jumpCount++;
		}

		std::cout << "Exited collision with " << other->GetName() << std::endl;
	}
};