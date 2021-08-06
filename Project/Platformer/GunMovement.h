#pragma once

#include <Kross.h>
using namespace Kross;

class GunMovement : public Script
{
public:
	GunMovement() :
		renderer(nullptr),
		animator(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "GunMovement";
	};
	~GunMovement() {};

	SpriteRenderer* renderer;

	Animator* animator;

	Object* player;
	Camera* camera;
	float currentAngleAimed;
	float lockAngle;
	Vector2 directionToMouseFromPlayer;
	Vector2 playerLocation;
	Window* window;
		
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

	void Start() override
	{

		window =  Application::GetWindow();
		renderer = GetComponent<SpriteRenderer>();
		camera = (Camera*)SceneManager::GetCurrentScene()->FindObject("Camera");
		animator = GetComponent<Animator>();
		player = SceneManager::GetCurrentScene()->FindObject("Player");

		currentGunSprite = Degree0;
	}

	void Update() override 
	{

		Vector2 mousePos;
		Vector2 mousePos = Input::GetMousePosition();
		Vector2 mousePoint = Vector2((mousePos.x / window->GetWidth()) * 4.0f - 2.0f, ((mousePos.y / window->GetHeight()) * 2.0f - 1.0f)) * camera->GetSize();
		Vector2 mousePosition = mousePoint + camera->c_Object->GetTransform()->m_Position;
		bool flipX = false;

		float angle = glm::degrees(std::atan2(mousePosition.y - player->GetTransform()->m_Position.y, mousePosition.x - player->GetTransform()->m_Position.x));

		if (angle > 360 - 12.25 || angle <= 12.25) //Case right
		{
			currentGunSprite = Degree0;
		}
		else if (angle > 22.5-12.25 && angle <= 22.5+12.25) //case 22.5
		{
			currentGunSprite = Degree22pt5;
		}
		else if (angle > 45 - 12.25 && angle <= 45 + 12.25) 
		{
			currentGunSprite = Degree45; //RIGHT DOWN DIAG
		}
		else if (angle > 67.5 - 12.25 && angle <= 67.5 + 12.25) 
		{
			currentGunSprite = Degree67pt5;
		}
		else if (angle > 90 - 12.25 && angle <= 90 + 12.25) 
		{
			currentGunSprite = Degree90; //DOWN
			if (angle>90) 
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
			currentGunSprite = Degree90; //LEFT
			flipX = true;
		}
		else if (angle > 202.5 - 12.25 && angle <= 202.5 + 12.25) 
		{
			Sprite* Degree202pt5;
		}
		else if (angle > 225 - 12.25 && angle <= 225 + 12.25) 
		{
			Sprite* Degree225; //LEFT UP DIAG
		}
		else if (angle > 247.5 - 12.25 && angle <= 247.5 + 12.25) 
		{
			Sprite* Degree247pt5;
		}



		else if (angle > 270 - 12.25 && angle <= 270 + 12.25)
		{
			currentGunSprite = Degree270; //UP
		}
		else if (angle > 292.5 - 12.25 && angle <= 292.5 + 12.25) 
		{
			currentGunSprite = Degree292pt5;
		}
		else if (angle > 315 - 12.25 && angle <= 315 + 12.25) 
		{
			currentGunSprite = Degree315; //UP RIGHT DIAG
		}
		else if (angle > 337.5 - 12.25 && angle <= 337.5 + 12.25)
		{
			currentGunSprite = Degree337pt5;
		}





	}



};