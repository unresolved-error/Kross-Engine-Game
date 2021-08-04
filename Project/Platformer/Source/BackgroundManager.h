#pragma once

#include <Kross.h>

using namespace Kross;

class BackgroundManager : public Script
{
public:
	BackgroundManager()
	{
		/* Every Script Must do this! */
		m_Name = "BackgroundManager";
	};
	~BackgroundManager() {};
	Object* sceneCam;
	Transform2D* transform;


	//FURTHEST BACKGROUND MANAGEMENT.
	Object* furthestPrimary;
	Object* furthestSecondary;
	float furthestOffset = 15.0f;
	float furthestScrollOffset = 0.0f;
	//DO NOT USE DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float furthestFollowSpeed = 3;


	Script* Duplicate() override
	{
		return KROSS_NEW BackgroundManager();
	}



	void Start() override
	{
		sceneCam = SceneManager::GetCurrentScene()->GetCamera();
		furthestPrimary = SceneManager::GetCurrentScene()->FindObject("Furthest-A");
		furthestSecondary = SceneManager::GetCurrentScene()->FindObject("Furthest-B");

		furthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
		furthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + furthestOffset;


	}


	void Update() override 
	{
		Transform2D* furthestPrimaryTransform = furthestPrimary->GetTransform();
		Transform2D* furthestSecondaryTransform = furthestSecondary->GetTransform();
		Transform2D* cameraTransform = sceneCam->GetTransform();
		

		furthestScrollOffset = fmod(cameraTransform->m_Position.x, (furthestOffset*furthestFollowSpeed));
		furthestPrimaryTransform->m_Position.x = cameraTransform->m_Position.x  - furthestScrollOffset/furthestFollowSpeed;
		furthestSecondaryTransform->m_Position.x = furthestPrimaryTransform->m_Position.x + furthestOffset;


		//IF ITS WAY OUTTA RANGE, REMAKE IT BACK IN. THIS IS BAD.
		if(furthestPrimaryTransform->m_Position.x < cameraTransform->m_Position.x - furthestOffset)
		{
			furthestPrimaryTransform->m_Position.x += (2 * furthestOffset);
		}
		if(furthestSecondaryTransform->m_Position.x < cameraTransform->m_Position.x - furthestOffset)
		{
			furthestSecondaryTransform->m_Position.x += (2 * furthestOffset);
		}
		if(furthestPrimaryTransform->m_Position.x > cameraTransform->m_Position.x + furthestOffset)
		{
			furthestPrimaryTransform->m_Position.x -= (2 * furthestOffset);
		}
		if(furthestSecondaryTransform->m_Position.x > cameraTransform->m_Position.x + furthestOffset)
		{
			furthestSecondaryTransform->m_Position.x -= (2 * furthestOffset);
		}

		


		
	}




};