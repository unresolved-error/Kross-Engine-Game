#pragma once

#include <Kross.h>

#include "PlayerMovement.h"

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
	PlayerController* m_PlayerMovement = KROSS_NEW PlayerController();
	Camera* camera;
	Window* window;

	bool flipX = false;
	float angle = 0.0f;
		
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

	Vector2 toMouse;

	void Start() override
	{

		window =  Application::GetWindow();
		renderer = GetComponent<SpriteRenderer>();
		camera = SceneManager::GetCurrentScene()->GetCamera()->GetComponent<Camera>();
		player = SceneManager::GetCurrentScene()->FindObject("Player");
		//m_PlayerMovement = GetComponent<PlayerController>();

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
		Vector2 crossHairPos;
		
		if (angle != NAN)
		{
			crossHairPos = PlaceCrossHairOnInput(angle);
			//angle = glm::degrees(std::atan2(crossHairPos.y, -crossHairPos.x));
			//float angle = glm::degrees(std::atan(mousePosition.y - c_Object->GetTransform()->m_Position.y, -(mousePosition.x - c_Object->GetTransform()->m_Position.x)));
			angle += 180;
			SetSpriteAngle(angle, flipX);

		}

		if (m_PlayerMovement->GetControllerID() != -1 && Input::GetControllerAxis(m_PlayerMovement->GetControllerID(), Controller::RightStickHorizontal, 0.2f) == 0.0f && Input::GetControllerAxis(m_PlayerMovement->GetControllerID(), Controller::RightStickVertical, 0.2f) == 0.0f)
		{
			float velX = player->GetComponent<Rigidbody2D>()->GetBody()->GetLinearVelocity().x;

			int value = glm::sign(velX);

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
		else {
			//renderer->SetFlipX(player->GetComponent<SpriteRenderer>()->GetFlipX());
		}
		renderer->GetMaterial()->SetDiffuse(currentGunSprite);

		toMouse = Vector2((crossHairPos.x - c_Object->GetTransform()->m_Position.x), crossHairPos.y - c_Object->GetTransform()->m_Position.y);
		
		Vector2 toMouseNormd = glm::normalize(toMouse);
		Vector2 toCrosshair = toMouseNormd * 1.5f;
		Vector2 toEndOfGun = toMouseNormd * 0.3f;


		LineRenderer* endOfGunDebug = c_Object->GetDebugRenderer();
		Vector2 crossHairLocation = Vector2(toCrosshair + c_Object->GetTransform()->m_Position);
		Vector2 endOfGunLocation = Vector2(toEndOfGun + c_Object->GetTransform()->m_Position);

		m_CrossHair->GetTransform()->m_Position = crossHairPos; //toCrosshair + c_Object->GetTransform()->m_Position;


		//endOfGunDebug->DrawCross(crossHairLocation, 0.3f);
		endOfGunDebug->DrawCross(endOfGunLocation, 0.1f, Vector3(1,0,0));

	}

	Vector2 PlaceCrossHairOnInput(float &returnAngle)
	{
		Vector2 crossHairPos = Vector2(0.0f);

		Vector2 mousePos = Input::GetMousePosition();
		float aspectRatio = Application::GetWindow()->GetApsectRatio();
		
		Vector2 mousePoint = Vector2(((mousePos.x / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((mousePos.y / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize();

		if (m_PlayerMovement->GetControllerID() != -1)
		{
			mousePoint = Vector2(Input::GetControllerAxis(m_PlayerMovement->GetControllerID(), Controller::RightStickHorizontal, 0.2f), Input::GetControllerAxis(m_PlayerMovement->GetControllerID(), Controller::RightStickVertical, 0.2f));
			crossHairPos = mousePoint + c_Object->GetTransform()->m_Position;

			if (mousePoint != Vector2(0.0f))
			{
				returnAngle = glm::degrees(glm::atan(crossHairPos.y - c_Object->GetTransform()->m_Position.y, -(crossHairPos.x - c_Object->GetTransform()->m_Position.x)));
			}
			else
			{
				returnAngle = NAN;
			}
		
			Vector2 controllerInputNormalised = glm::normalize(mousePoint);

			crossHairPos = controllerInputNormalised + c_Object->GetTransform()->m_Position;
		
		}

		else
		{
			crossHairPos = mousePoint + camera->c_Object->GetTransform()->m_Position;

			returnAngle = glm::degrees(std::atan2(crossHairPos.y - c_Object->GetTransform()->m_Position.y, -(crossHairPos.x - c_Object->GetTransform()->m_Position.x)));
		}

		return crossHairPos;
	}

	void SetSpriteAngle(float angle, bool &flipX)
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