#pragma once

#include <Kross.h>

using namespace Kross;

class BackgroundManager : public Script
{
public:
	Object* sceneCam;
	Transform2D* transform;

	List<Object*> furthestObjs;
	Object* furthestPrimary;
	Object* furthestSecondary;
	Object* furthestOnScreen;
	float furthestOffset = 15.0f;


	Script* Duplicate() override
	{
		return KROSS_NEW BackgroundManager();
	}



	void Start() override
	{
		sceneCam = SceneManager::GetCurrentScene()->GetCamera();
		furthestPrimary = SceneManager::GetCurrentScene()->FindObject("Furthest-A");
		furthestSecondary = SceneManager::GetCurrentScene()->FindObject("Furthest-B");

		furthestObjs.push_back(furthestPrimary);
		furthestObjs.push_back(furthestSecondary);
		furthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
		furthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + furthestOffset;
		furthestOnScreen = furthestPrimary;


	}


	void Update() override 
	{
		Transform2D* furthestPrimaryTransform = furthestPrimary->GetTransform();
		Transform2D* furthestSecondaryTransform = furthestSecondary->GetTransform();
		Transform2D* cameraTransform = sceneCam->GetTransform();

		

		if ((cameraTransform->m_Position.x - furthestPrimaryTransform->m_Position.x)<=((cameraTransform->m_Position.x - furthestSecondaryTransform->m_Position.x)))
		{
			furthestOnScreen = furthestPrimary;

			if (cameraTransform->m_Position.x >= furthestOnScreen->GetTransform()->m_Position.x)
			{
				///WE ARE CURRENTLY ON THE RIGHT SIDE OF ON SCREEN.
				furthestSecondaryTransform->m_Position.x = furthestPrimaryTransform->m_Position.x + furthestOffset;
			}
			else 
			{
				///WE ARE CURRENTLY ON THE LEFT SIDE OF ON SCREEN.
				furthestSecondaryTransform->m_Position.x = furthestPrimaryTransform->m_Position.x - furthestOffset;
			}
		}
		else 
		{
			furthestOnScreen = furthestSecondary;

			if (cameraTransform->m_Position.x >= furthestOnScreen->GetTransform()->m_Position.x)
			{
				///WE ARE CURRENTLY ON THE RIGHT SIDE OF ON SCREEN.
				furthestPrimaryTransform->m_Position.x = furthestSecondaryTransform->m_Position.x + furthestOffset;
			}
			else
			{
				///WE ARE CURRENTLY ON THE LEFT SIDE OF ON SCREEN.
				furthestPrimaryTransform->m_Position.x = furthestSecondaryTransform->m_Position.x - furthestOffset;
			}


		}
		

		
	}




};