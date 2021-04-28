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

	TextRenderer* rend;

	float moveSpeed = 5;
	float previousTime = 0.0f;
	float actualTime;

	int frameCount;

	void Start() override
	{
		transform = GetObject()->GetTransform();
		renderer = GetObject()->GetComponent<SpriteRenderer>();
		window = Application::GetWindow();

		previousTime = Time::GetDeltaTime();
	}

	void Update() override
	{
		Vector2 input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), Input::GetAxis(Axis::KeyboardVertical));
		rigidBody->OnApplyForce(input);


		Vector2 mousePos = Input::GetMousePosition();

		Vector2 mousePoint = Vector2((mousePos.x / window->GetWidth()) * 2.0f - 1.0f, ((mousePos.y / window->GetHeight()) * 2.0f - 1.0f));
		float aspect = window->GetApsectRatio();
		//mousePoint.x *= aspect;

		float angle = glm::degrees(std::atan2(mousePoint.y - -transform->m_Position.y, mousePoint.x - transform->m_Position.x));

		if (Input::GetKeyDown(Key::Space))
		{
			std::cout << mousePoint.x << "," << mousePoint.y << std::endl;
			std::cout << transform->m_Position.x << "," << transform->m_Position.y << std::endl;
			std::cout << "Current X pos: " << rigidBody->GetPosition().x << std::endl;
			std::cout << "Current Y pos: " << rigidBody->GetPosition().y << std::endl;
			std::cout << "Applied X force: " << input.x << std::endl;
			std::cout << "Applied Y force: " << input.y << std::endl;
		}

		actualTime += Time::GetDeltaTime();
		frameCount++;

		

		if (actualTime >= 1.0f)
		{
			rend->SetText(std::to_string(frameCount));

			frameCount = 0;
			actualTime = 0.0f;
		}

		rigidBody->GetObject()->GetTransform()->m_Rotation = -angle;
	

		//if (input.x > 0)
		//	renderer->SetFlipX(false);
		//else if (input.x < 0)
		//	renderer->SetFlipX(true);
	}

};