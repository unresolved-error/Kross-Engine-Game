#pragma once

#include <Kross.h>
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

	Object* player;
	Camera* camera;
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

	Vector2 toMouse;

	void Start() override
	{

		window =  Application::GetWindow();
		renderer = GetComponent<SpriteRenderer>();
		camera = SceneManager::GetCurrentScene()->GetCamera()->GetComponent<Camera>();
		player = SceneManager::GetCurrentScene()->FindObject("Player");


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
	}

	void Update() override 
	{
		Vector2 mousePos;

		mousePos = Input::GetMousePosition();
		float aspectRatio = Application::GetWindow()->GetApsectRatio();
		Vector2 mousePoint = Vector2(((mousePos.x / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((mousePos.y / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize();
		Vector2 mousePosition = mousePoint + camera->c_Object->GetTransform()->m_Position;
		bool flipX = false;

		
		float angle = glm::degrees(std::atan2(mousePosition.y - c_Object->GetTransform()->m_Position.y, -(mousePosition.x - c_Object->GetTransform()->m_Position.x)));
		//float angle = glm::degrees(std::atan(mousePosition.y - c_Object->GetTransform()->m_Position.y, -(mousePosition.x - c_Object->GetTransform()->m_Position.x)));
		angle += 180;

		//c_Object->GetTransform()->m_Position = mousePosition;
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
			if (angle < 270) { flipX = true; }
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

		renderer->SetFlipX(flipX);
		player->GetComponent<SpriteRenderer>()->SetFlipX(flipX);
		renderer->GetMaterial()->SetDiffuse(currentGunSprite);

		toMouse = Vector2((mousePosition.x - c_Object->GetTransform()->m_Position.x), mousePosition.y - c_Object->GetTransform()->m_Position.y);
		
		Vector2 toMouseNormd = glm::normalize(toMouse);
		Vector2 toCrosshair = toMouseNormd * 1.5f;
		Vector2 toEndOfGun = toMouseNormd * 0.3f;


		LineRenderer* endOfGunDebug = c_Object->GetDebugRenderer();
		Vector2 crossHairLocation = Vector2(toCrosshair + c_Object->GetTransform()->m_Position);
		Vector2 endOfGunLocation = Vector2(toEndOfGun + c_Object->GetTransform()->m_Position);


		endOfGunDebug->DrawCross(crossHairLocation, 0.3f);
		endOfGunDebug->DrawCross(endOfGunLocation, 0.1f, Vector3(1,0,0));

	}
};