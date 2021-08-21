#pragma once

#include <Kross.h>

using namespace Kross;

class EnemyMovement : public Script
{
public:
	EnemyMovement() :
		renderer(nullptr),
		rigidBody(nullptr),
		animator(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "EnemyMovement";
	};
	~EnemyMovement() {};

	SpriteRenderer* renderer;
	Rigidbody2D* rigidBody;

	Animator* animator;

	Object* player;

	float moveSpeed = 2.0f;
	float previousY = 0.0f;

	float agroRange = 8.0f;

	Vector2 movementVector = Vector2(0.0f);

	float elapsedWaitingTime = 0.0f;
	float maxWaitingTime = 3.0f;

	bool grounded = true;

	float m_MaxGroundSpeed = 1.5f;

	Script* Duplicate() override
	{
		return KROSS_NEW EnemyMovement();
	}

	void Start() override
	{
		renderer = GetComponent<SpriteRenderer>();

		rigidBody = GetComponent<Rigidbody2D>();

		animator = GetComponent<Animator>();

		player = SceneManager::GetCurrentScene()->FindObject("Player");
	}

	void Update() override
	{
		

		Transform2D* playerTransform = player->m_Transform;

		if (glm::length(m_GameObject->m_Transform->m_Position - playerTransform->m_Position) <= agroRange)
		{
			if (playerTransform->m_Position.x > m_GameObject->m_Transform->m_Position.x)
			{
				movementVector.x = 1.0f;
			}

			else
			{
				movementVector.x = -1.0f;
			}
		}
		else
		{
			if (elapsedWaitingTime < maxWaitingTime)
				elapsedWaitingTime += Time::GetDeltaTime();

			else
			{
				elapsedWaitingTime = 0.0f;
				movementVector.x = (float)Random::GetRandomRange<int>(-1, 1);
			}
		}

		Move(movementVector);

		previousY = m_GameObject->m_Transform->m_Position.y;

	}

	void Move(Vector2 input)
	{
		Transform2D* playerTransform = player->m_Transform;

		if (rigidBody->GetBody()->GetLinearVelocity().x <= 0.05f && rigidBody->GetBody()->GetLinearVelocity().x >= -0.05f)
		{
			animator->SetCurrentAnimation(0);
		}
		else
		{
			animator->SetCurrentAnimation(1);
		}

		if (rigidBody->GetBody()->GetLinearVelocity().x < m_MaxGroundSpeed && rigidBody->GetBody()->GetLinearVelocity().x > -m_MaxGroundSpeed)
		{
			rigidBody->OnApplyForce(input);
		}

		if ((rigidBody->GetBody()->GetLinearVelocity().x == 0.0f && rigidBody->GetBody()->GetLinearVelocity().y == 0.0f))
		{
			rigidBody->OnApplyImpulse(Vector2(0.0f, 0.75f));
			grounded = false;
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

	void OnCollisionStay(Object* other) override
	{
		if (other->GetLayer() == Layer::Ground && other != m_GameObject)
		{
			grounded = true;
		}
	}

	void OnCollisionExit(Object* other) override
	{
		grounded = false;
	}
};