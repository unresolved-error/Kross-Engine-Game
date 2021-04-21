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

	float moveSpeed;

	void Start() override
	{
		transform = GetObject()->GetTransform();
		renderer = GetObject()->GetComponent<SpriteRenderer>();
		window = Application::GetWindow();
	}

	void Update() override
	{
		Vector2 input = Vector2(Input::GetAxis(Axis::KeyboardHorizontal), Input::GetAxis(Axis::KeyboardVertical));
		transform->m_Position += input * 0.017f;

		Vector2 mousePos = Input::GetMousePosition();

		Vector2 mousePoint = Vector2((mousePos.x / window->GetWidth()) * 2.0f - 1.0f, ((mousePos.y / window->GetHeight()) * 2.0f - 1.0f));
		float aspect = window->GetApsectRatio();
		//mousePoint.x *= aspect;

		float angle = glm::degrees(std::atan2(mousePoint.y - -transform->m_Position.y, mousePoint.x - transform->m_Position.x));

		if (Input::GetKeyDown(Key::Space))
		{
			std::cout << mousePoint.x << "," << mousePoint.y << std::endl;
			std::cout << transform->m_Position.x << "," << transform->m_Position.y << std::endl;
		}

		transform->m_Rotation = -angle;

		//if (input.x > 0)
		//	renderer->SetFlipX(false);
		//else if (input.x < 0)
		//	renderer->SetFlipX(true);
	}

};