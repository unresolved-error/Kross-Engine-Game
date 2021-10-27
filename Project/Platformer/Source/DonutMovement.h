#pragma once

#include <Kross.h>

using namespace Kross;

class DonutMovement : public Script
{
public:
	DonutMovement() :
		renderer(nullptr),
		rigidBody(nullptr),
		animator(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "DonutMovement";
	};
	~DonutMovement() {};

	SpriteRenderer* renderer;
	Rigidbody2D* rigidBody;

	Animator* animator;

	Sprite* hitSprite;

	Object* player;

	float moveSpeed = 2.0f;
	float previousY = 0.0f;

	float agroRange = 8.0f;

	Vector2 movementVector = Vector2(0.0f);

	float elapsedWaitingTime = 0.0f;
	float maxWaitingTime = 3.0f;

	float hitTimer = 0.1f;
	float hitTimerMax = 0.1f;

	bool grounded = true;
	bool hit = false;

	float m_MaxGroundSpeed = 1.5f;

	float m_Health = 5.0f;

	Script* Duplicate() override
	{
		return KROSS_NEW DonutMovement();
	}

	void Start() override
	{
		renderer = GetComponent<SpriteRenderer>();

		rigidBody = GetComponent<Rigidbody2D>();

		animator = GetComponent<Animator>();

		player = SceneManager::GetCurrentScene()->FindObject("Player");

		if (m_GameObject->GetName() == "Puzzle2Enemy1")
		{
			moveSpeed = 3.0f;
		}

		hitSprite = ResourceManager::GetResource<Sprite>("Donut0-1");
	}

	void Update() override
	{
		Transform2D* playerTransform = player->m_Transform;

		if (glm::length(m_GameObject->m_Transform->m_Position - playerTransform->m_Position) <= agroRange)
		{
			if (playerTransform->m_Position.x > m_GameObject->m_Transform->m_Position.x)
			{
				movementVector.x = moveSpeed;
			}
			else
			{
				movementVector.x = -moveSpeed;
			}
		}
		else
		{
			if (elapsedWaitingTime < maxWaitingTime)
			{
				elapsedWaitingTime += Time::GetDeltaTime();
			}
			else
			{
				elapsedWaitingTime = 0.0f;
				movementVector.x = (float)Random::GetRandomRange<int>(-1, 1);
			}
		}

		Move(movementVector);

		previousY = m_GameObject->m_Transform->m_Position.y;

		if (hit)
		{
			if (hitTimer > 0.0f)
			{
				hitTimer -= Time::GetDeltaTime();
			}

			if (hitTimer <= hitTimerMax / 2.0f)
			{
				hitTimer -= Time::GetDeltaTime();
				hit = false;
			}
		}

		

		else
		{
			if (hitTimer <= hitTimerMax / 2.0f && hitTimer > 0.0f)
			{
				hitTimer -= Time::GetDeltaTime();
				hit = false;
			}
			else
			{
				hitTimer = hitTimerMax;
			}
		}
	}

	void Move(Vector2 input)
	{
		Transform2D* playerTransform = player->m_Transform;

		if (!hit)
		{
			if (!animator->GetCurrentAnimation()->IsPlaying())
			{
				animator->Play();
			}

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

			if (rigidBody->GetBody()->GetLinearVelocity() == b2Vec2(0.0f, 0.0f))
			{
				for (b2ContactEdge* contact = rigidBody->GetBody()->GetContactList(); contact; contact = contact->next)
				{
					if (contact->contact->IsTouching())
					{
						Body* currentBody = contact->other;
						Body* gameObjectBody = rigidBody->GetBody();

						Vector2 normal = Physics::GetCollisionNormal(contact->contact);

						if (contact->contact->GetFixtureA()->GetBody() == gameObjectBody)
						{
							/* This is the Enemy. */
							if (-normal.y > 0.9f)
							{
								//Debug::LogLine((std::string)"Touching the Ground");
								rigidBody->OnApplyImpulse(Vector2(0.0f, 0.7f));
								break;
							}
						}

						else if (contact->contact->GetFixtureB()->GetBody() == gameObjectBody)
						{
							/* This is Not. */
							if (normal.y > 0.9f)
							{
								//Debug::LogLine((std::string)"Touching the Ground");
								rigidBody->OnApplyImpulse(Vector2(0.0f, 0.7f));
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			animator->Pause();
			renderer->GetMaterial()->SetDiffuse(hitSprite);
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