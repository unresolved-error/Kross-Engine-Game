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
		Vector2 input = Vector2(0.0f);

		Transform2D* playerTransform = player->GetTransform();
		Transform2D* transform = c_Object->GetTransform();

		if (playerTransform->m_Position.x > transform->m_Position.x)
		{
			input.x = 1.0f;
		}

		else
		{
			input.x = -1.0f;
		}

		Move(input);

		previousY = transform->m_Position.y;

	}

	void Move(Vector2 input)
	{
		Transform2D* transform = c_Object->GetTransform();
		Transform2D* playerTransform = player->GetTransform();

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
		if (other->GetLayer() == Layer::Ground && other != c_Object)
		{
			grounded = true;
		}
	}

	void OnCollisionExit(Object* other) override
	{
		grounded = false;
	}
};