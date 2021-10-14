#pragma once

#include <Kross.h>

#include "PlayerMovement.h"
#include "HealthManager.h"

using namespace Kross;

class GunMovement : public Script
{
public:
	GunMovement() : 
		renderer(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "GunMovement";
	};
	~GunMovement() {};

	Script* Duplicate() override
	{
		return KROSS_NEW GunMovement();
	}
	
	
	SpriteRenderer* renderer;

	Object* m_CrossHair = nullptr;

	Object* player;
	Object* level;

	PlayerMovement* m_PlayerMovement = nullptr;
	HealthManager* m_HealthManager = nullptr;

	Camera* camera;
	Window* window;
	bool m_Fired = false;
	float m_RateOfFire = 0.1f;
	float m_TimeElapsed = 0.0f;
	float bulletStartForce = 0.025f;
	float bulletFriction = 0.5f;
	float bulletDecayThreshold = 0.005f;

	bool flipX = false;
	float angle = 0.0f;
	float damage = 1.0f;
	int bulletCount = 0;
		
	Sprite* Degree0; //PURE RIGHT
	Sprite* Degree22pt5;
	Sprite* Degree45; //RIGHT DOWN DIAG
	Sprite* Degree67pt5;

	Sprite* Degree90; //DOWN
	

	Sprite* Degree270; //UP
	Sprite* Degree292pt5;
	Sprite* Degree315; //UP RIGHT DIAG
	Sprite* Degree337pt5;

	Sprite* currentGunSprite;


	Sprite* bulletSprite;

	Vector2 toMouse;

	std::vector<Object*> bullets;
	std::vector<bool> bulletHits;

	void Start() override
	{
		window =  Application::GetWindow();
		renderer = GetComponent<SpriteRenderer>();
		camera = SceneManager::GetCurrentScene()->GetCamera()->GetComponent<Camera>();
		player = SceneManager::GetCurrentScene()->FindObject("Player");
		m_PlayerMovement = player->GetComponent<PlayerMovement>();

		level = SceneManager::GetCurrentScene()->FindObject("Level");
		m_HealthManager = level->GetComponent<HealthManager>();

		Degree0 = ResourceManager::GetResource<Sprite>("Gun1-1");
		Degree22pt5 = ResourceManager::GetResource<Sprite>("Gun0-1");
		Degree45 = ResourceManager::GetResource<Sprite>("Gun2-0");
		Degree67pt5 = ResourceManager::GetResource<Sprite>("Gun1-0");
		Degree90 = ResourceManager::GetResource<Sprite>("Gun0-0");
		Degree270 = ResourceManager::GetResource<Sprite>("Gun2-2"); 
		Degree292pt5 = ResourceManager::GetResource<Sprite>("Gun1-2"); 
		Degree315 = ResourceManager::GetResource<Sprite>("Gun0-2");
		Degree337pt5 = ResourceManager::GetResource<Sprite>("Gun2-1");
		currentGunSprite = Degree0;
		bulletSprite = ResourceManager::GetResource<Sprite>("Bullet");

		m_CrossHair = SceneManager::GetCurrentScene()->FindObject("CrossHair");
	}

	void Update() override 
	{
		//Vector2 mousePos;
		//
		//mousePos = Input::GetMousePosition();
		//float aspectRatio = Application::GetWindow()->GetApsectRatio();
		//Vector2 mousePoint = Vector2(((mousePos.x / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((mousePos.y / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize();
		//Vector2 mousePosition = mousePoint + camera->c_Object->GetTransform()->m_Position;
		Vector2 crossHairPos{};
		
		if (m_Fired)
		{
			if (m_TimeElapsed < m_RateOfFire)
			{
				m_TimeElapsed += Time::GetDeltaTime();
				m_PlayerMovement->m_ShakeCamera = true;
			}

			else
			{
				m_TimeElapsed = 0.0f;
				m_Fired = false;
				m_PlayerMovement->m_ShakeCamera = false;
			}
		}

		if (angle != NAN)
		{
			crossHairPos = PlaceCrossHairOnInput(angle);
			//angle = glm::degrees(std::atan2(crossHairPos.y, -crossHairPos.x));
			//float angle = glm::degrees(std::atan(mousePosition.y - c_Object->GetTransform()->m_Position.y, -(mousePosition.x - c_Object->GetTransform()->m_Position.x)));
			angle += 180;
			SetSpriteAngle(angle, flipX);

		}

		if (m_PlayerMovement->m_ControllerID != -1 && Input::GetControllerAxis(m_PlayerMovement->m_ControllerID, Controller::RightStickHorizontal, 0.2f) == 0.0f && Input::GetControllerAxis(m_PlayerMovement->m_ControllerID, Controller::RightStickVertical, 0.2f) == 0.0f)
		{
			float velX = player->GetComponent<Rigidbody2D>()->GetBody()->GetLinearVelocity().x;

			int value = static_cast<int>(glm::sign(velX));

			if (glm::abs(velX) < 0.01)
			{
				value = 0;
			}


			if (value > 0)
			{
				flipX = false;
			}
			else if (value < 0)
			{
				flipX = true;
			}
			currentGunSprite = Degree0;
		}

		if (angle != NAN)
		{
			renderer->SetFlipX(flipX);
			player->GetComponent<SpriteRenderer>()->SetFlipX(flipX);
		}

		renderer->GetMaterial()->SetDiffuse(currentGunSprite);

		toMouse = Vector2(crossHairPos.x - m_GameObject->m_Transform->m_Position.x, crossHairPos.y - m_GameObject->m_Transform->m_Position.y);

		Vector2 toMouseNormd = glm::normalize(toMouse);
		Vector2 toCrosshair = toMouseNormd * 1.5f;
		Vector2 toEndOfGun = toMouseNormd * 0.03f;

		if (m_Fired)
		{
			m_PlayerMovement->GetComponent<Rigidbody2D>()->OnApplyForce(-toMouseNormd *0.2f);
		}


		LineRenderer* endOfGunDebug = m_GameObject->GetDebugRenderer();
		Vector2 crossHairLocation = Vector2(toCrosshair + m_GameObject->m_Transform->m_Position);
		Vector2 endOfGunLocation = Vector2(toEndOfGun + m_GameObject->m_Transform->m_Position);

		m_CrossHair->m_Transform->m_Position = crossHairPos; //toCrosshair + c_Object->GetTransform()->m_Position;


		//endOfGunDebug->DrawCross(crossHairLocation, 0.3f);
		endOfGunDebug->DrawCross(endOfGunLocation, 0.1f, Vector3(1, 0, 0));

		if (!m_Fired)
		{
			if (m_PlayerMovement->m_ControllerID == -1)
			{
				if (Input::GetMouseButtonDown(Mouse::Right))
				{
					Object* bullet = Object::OnCreate("Bullet-Clone");
					Rigidbody2D* rigidbody = bullet->AttachComponent<Rigidbody2D>();
					SpriteRenderer* sprite = bullet->AttachComponent<SpriteRenderer>();
					Collider* collider = bullet->GetComponent<Collider>();
					rigidbody->SetContinuousCollision(true);

					bullet->m_Transform->m_Position = endOfGunLocation;
					bullet->m_Transform->m_Rotation = angle;
					bullet->SetLayer(Layer::Player);

					collider->GetCollisionFilters()->categoryBits = (uint16)ColliderFilters::Weapon;
					collider->GetCollisionFilters()->maskBits = (uint16)ColliderFilters::Environment | (uint16)ColliderFilters::Level |
						(uint16)ColliderFilters::Fluid | (uint16)ColliderFilters::Chain | (uint16)ColliderFilters::Enemy;

					collider->SetShapeType(ShapeType::Circle);

					collider->SetRadius(0.03125f);

					sprite->SetMaterial(ResourceManager::GetResource<Material>("Bullet"));

					Colour colour = Colour(1.0f);
					#ifndef _DEBUG
					colour.r = Random::GetRandomRange<float>(1.0f, 0.0f);
					colour.g = Random::GetRandomRange<float>(1.0f, 0.0f);
					colour.b = Random::GetRandomRange<float>(1.0f, 0.0f);
					#endif

					sprite->SetColour(colour);

					OnCreateObject(bullet);

					rigidbody->SetFriction(bulletFriction);
					rigidbody->OnApplyImpulse(toMouseNormd * bulletStartForce);
					sprite->GetMaterial()->SetDiffuse(bulletSprite);

					bullets.push_back(bullet);
					bulletHits.push_back(false);
					bulletCount++;

					sprite->GetMaterial()->SetDiffuse(bulletSprite);

					m_Fired = true;
				}
			}
			else
			{
				if (Input::GetControllerAxis(m_PlayerMovement->m_ControllerID, Controller::RightTrigger, 0.0f) > 0.5f)
				{
					Object* bullet = Object::OnCreate("Bullet-Clone");

					Rigidbody2D* rigidbody = bullet->AttachComponent<Rigidbody2D>();
					SpriteRenderer* sprite = bullet->AttachComponent<SpriteRenderer>();
					Collider* collider = bullet->GetComponent<Collider>();
					rigidbody->SetContinuousCollision(true);

					bullet->m_Transform->m_Position = endOfGunLocation;
					bullet->m_Transform->m_Rotation = angle;

					bullet->SetLayer(Layer::Player);

					collider->GetCollisionFilters()->categoryBits = (uint16)ColliderFilters::Weapon;
					collider->GetCollisionFilters()->maskBits = (uint16)ColliderFilters::Environment | (uint16)ColliderFilters::Level |
						(uint16)ColliderFilters::Fluid | (uint16)ColliderFilters::Chain | (uint16)ColliderFilters::Enemy;

					collider->SetShapeType(ShapeType::Circle);

					collider->SetRadius(0.03125f);

					sprite->SetMaterial(ResourceManager::GetResource<Material>("Bullet"));

					Colour colour = Colour(1.0f);
					#ifndef _DEBUG
					colour.r = Random::GetRandomRange<float>(1.0f, 0.0f);
					colour.g = Random::GetRandomRange<float>(1.0f, 0.0f);
					colour.b = Random::GetRandomRange<float>(1.0f, 0.0f);
					#endif

					sprite->SetColour(colour);

					OnCreateObject(bullet);

					rigidbody->SetFriction(bulletFriction);
					rigidbody->OnApplyImpulse(toMouseNormd * bulletStartForce);
					sprite->GetMaterial()->SetDiffuse(bulletSprite);

					bullets.push_back(bullet);
					bulletHits.push_back(false);
					bulletCount++;

					sprite->GetMaterial()->SetDiffuse(bulletSprite);

					m_Fired = true;
				}
			}
		}
		

		for (int i = 0; i < bullets.size(); i++)
		{
			for (b2ContactEdge* contact = bullets[i]->GetComponent<Rigidbody2D>()->GetBody()->GetContactList(); contact; contact = contact->next)
			{
				if (contact->contact->IsTouching())
				{

					Object* obj = (Object*)contact->other->GetUserData();

					if (obj != player)
					{
						if (obj->GetLayer() == Layer::Player)
						{
							Health* health = obj->GetComponent<Health>();
							EnemyMovement* em = obj->GetComponent<EnemyMovement>();

							if (health && em->hitTimer == em->hitTimerMax)
							{
								Debug::LogLine(health->GetHealth());
								health->TakeDamage(damage);

								/* For Testing Effects For now. */
								SceneManager::GetCurrentScene()->DetachObject(bullets[i]);

								bullets[i] = nullptr;
								bullets.erase(bullets.begin() + i);

								em->hit = true;
							}

							bulletHits[i] = true;

							break;
						}
					}
				}
			}
		}

		for (int i = bullets.size() - 1; i >= 0; i--)
		{
			float threashold = bulletDecayThreshold;
			Rigidbody2D* rb = bullets[i]->GetComponent<Rigidbody2D>();
			SpriteRenderer* rend = bullets[i]->GetComponent<SpriteRenderer>();

			/* Checks if the bullet is within a specific speed */
			if (rb->GetBody()->GetLinearVelocity().x >= -threashold && rb->GetBody()->GetLinearVelocity().y >= -threashold &&
				rb->GetBody()->GetLinearVelocity().x <= threashold && rb->GetBody()->GetLinearVelocity().y < threashold)
			{
				if (rend->GetColour().a > 0.0f)
				{
					Colour colour = rend->GetColour();
					colour.a -= 0.0025f;
					rend->SetColour(colour);
				}
				else
				{
					SceneManager::GetCurrentScene()->DetachObject(bullets[i]);
					bullets[i] = nullptr;
					bullets.erase(bullets.begin() + i);
					bulletCount--;

					bulletHits[i] = false;
					
					continue;
				}
			}
			
			Colour colour = rend->GetColour();
			if (colour.a < 1.0f)
			{
				colour.a -= 0.0025f;
				rend->SetColour(colour);
			}
			else if (colour.a <= 0.0f)
			{
				SceneManager::GetCurrentScene()->DetachObject(bullets[i]);
				bullets.erase(bullets.begin() + i);
				bulletCount--;

				bulletHits[i] = false;
			}
		}
	}


	Vector2 PlaceCrossHairOnInput(float &returnAngle)
	{
		Vector2 crossHairPos = Vector2(0.0f);

		Vector2 mousePos = Input::GetMousePosition();
		float aspectRatio = Application::GetWindow()->GetApsectRatio();
		
		Vector2 mousePoint = Vector2(((mousePos.x / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((mousePos.y / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize();

		if (m_PlayerMovement->m_ControllerID != -1)
		{
			mousePoint = Vector2(Input::GetControllerAxis(m_PlayerMovement->m_ControllerID, Controller::RightStickHorizontal, 0.2f), Input::GetControllerAxis(m_PlayerMovement->m_ControllerID, Controller::RightStickVertical, 0.2f));
			crossHairPos = mousePoint + m_GameObject->m_Transform->m_Position;

			if (mousePoint != Vector2(0.0f))
			{
				returnAngle = glm::degrees(glm::atan(crossHairPos.y - m_GameObject->m_Transform->m_Position.y, -(crossHairPos.x - m_GameObject->m_Transform->m_Position.x)));
				Vector2 controllerInputNormalised = glm::normalize(mousePoint);

				crossHairPos = controllerInputNormalised + m_GameObject->m_Transform->m_Position;
			}
			else
			{
				if (flipX)
				{
					returnAngle = 0;
					crossHairPos = Vector2(-1.0f, 0.0f) + m_GameObject->m_Transform->m_Position;
				}
				else
				{
					returnAngle = 180;
					crossHairPos = Vector2(1.0f, 0.0f) + m_GameObject->m_Transform->m_Position;
				}
			}
		}

		else
		{
			crossHairPos = mousePoint + camera->m_GameObject->m_Transform->m_Position;

			returnAngle = glm::degrees(std::atan2(crossHairPos.y - m_GameObject->m_Transform->m_Position.y, -(crossHairPos.x - m_GameObject->m_Transform->m_Position.x)));
		}

		return crossHairPos;
	}


	void SetSpriteAngle(float angle, bool& flipX)
	{
		if (angle > 360 - 12.25 || angle <= 12.25) //Case right
		{
			currentGunSprite = Degree0;
			flipX = false;
		}
		else if (angle > 22.5 - 12.25 && angle <= 22.5 + 12.25) //case 22.5
		{
			currentGunSprite = Degree22pt5;
			flipX = false;
		}
		else if (angle > 45 - 12.25 && angle <= 45 + 12.25)
		{
			currentGunSprite = Degree45; //RIGHT DOWN DIAG
			flipX = false;
		}
		else if (angle > 67.5 - 12.25 && angle <= 67.5 + 12.25)
		{
			currentGunSprite = Degree67pt5;
			flipX = false;
		}
		else if (angle > 90 - 12.25 && angle <= 90 + 12.25)
		{
			currentGunSprite = Degree90; //DOWN
			if (angle > 90)
			{
				flipX = true;
			}
		}
		else if (angle > 112.5 - 12.25 && angle <= 112.5 + 12.25)
		{
			currentGunSprite = Degree67pt5;
			flipX = true;
		}
		else if (angle > 135 - 12.25 && angle <= 135 + 12.25)
		{
			currentGunSprite = Degree45; //LEFT DOWN DIAG
			flipX = true;
		}
		else if (angle > 157.5 - 12.25 && angle <= 157.5 + 12.25)
		{
			currentGunSprite = Degree22pt5;
			flipX = true;
		}
		else if (angle > 180 - 12.25 && angle <= 180 + 12.25)
		{
			currentGunSprite = Degree0; //LEFT
			flipX = true;
		}
		else if (angle > 202.5 - 12.25 && angle <= 202.5 + 12.25)
		{
			currentGunSprite = Degree337pt5;
			flipX = true;
		}
		else if (angle > 225 - 12.25 && angle <= 225 + 12.25)
		{
			currentGunSprite = Degree315; //LEFT UP DIAG
			flipX = true;
		}
		else if (angle > 247.5 - 12.25 && angle <= 247.5 + 12.25)
		{
			currentGunSprite = Degree292pt5;
			flipX = true;
		}
		else if (angle > 270 - 12.25 && angle <= 270 + 12.25)
		{
			currentGunSprite = Degree270; //UP
			if (angle < 270)
			{
				flipX = true;
			}
		}
		else if (angle > 292.5 - 12.25 && angle <= 292.5 + 12.25)
		{
			currentGunSprite = Degree292pt5;
			flipX = false;
		}
		else if (angle > 315 - 12.25 && angle <= 315 + 12.25)
		{
			currentGunSprite = Degree315; //UP RIGHT DIAG
			flipX = false;
		}
		else if (angle > 337.5 - 12.25 && angle <= 337.5 + 12.25)
		{
			currentGunSprite = Degree337pt5;
			flipX = false;
		}
	}
};