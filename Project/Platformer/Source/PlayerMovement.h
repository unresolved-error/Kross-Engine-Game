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

	Camera* camera;
	TextRenderer* textObj;

	bool followPlayer = false;

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

		if (Input::GetKeyDown(Key::Space))
			textObj->SetText("Screw AMD!");

		if (Input::GetKeyDown(Key::Backspace))
			textObj->SetText("Deklyn");

		if (Input::GetKeyDown(Key::Q))
		{
			std::cout << SceneManager::GetCurrentScene()->GetObjectCount() << std::endl;
		}

		if (Input::GetKeyPressed(Key::E))
		{
			followPlayer = !followPlayer;
		}

		if (Input::GetKeyDown(Key::Enter))
		{
			Object* newbie = OnCreateObject("Newbie", GetObject()->GetTransform()->m_Position, Random::GetRandomRange<float>(0.0f, 360.0f));
			newbie->AttachComponent<SpriteRenderer>();

			newbie->SetStaticStatus(true);

			SpriteRenderer* ren = newbie->GetComponent<SpriteRenderer>();
			ren->SetSprite(ResourceManager::GetResource<Sprite>(0));
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
			
			//if (glm::abs(cameraTransform->m_Position.x - transform->m_Position.x) > speed)
			//{
			//	if (cameraTransform->m_Position.x < transform->m_Position.x)
			//		cameraTransform->m_Position.x += speed;
			//
			//	if (cameraTransform->m_Position.x > transform->m_Position.x)
			//		cameraTransform->m_Position.x -= speed;
			//}
			//else
			//	cameraTransform->m_Position.x = transform->m_Position.x;
			//
			//if (glm::abs(cameraTransform->m_Position.y - transform->m_Position.y) > speed)
			//{
			//
			//	if (cameraTransform->m_Position.y < transform->m_Position.y)
			//		cameraTransform->m_Position.y += speed;
			//
			//	if (cameraTransform->m_Position.y > transform->m_Position.y)
			//		cameraTransform->m_Position.y -= speed;
			//}
			//else
			//	cameraTransform->m_Position.y = transform->m_Position.y;

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

};