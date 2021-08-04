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
	List<Object*> furthestScenery; //Not used yet. For non repeating items.
	float furthestOffset = 15.0f;
	float furthestScrollOffset = 0.0f;
	//DO NOT USE DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float furthestFollowSpeed = 5;

	//2ndFURTHEST BACKGROUND MANAGEMENT.
	Object* secondFurthestPrimary;
	Object* secondFurthestSecondary;
	List<Object*> SecondFurthestScenery; //Not used yet. For non repeating items.
	float secondFurthestOffset = 15.0f;
	float secondFurthestScrollOffset = 0.0f;
	//DO NOT USE DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float secondFurthestFollowSpeed = 3;

	//CLOSE BACKGROUND MANAGEMENT.
	Object* closePrimary;
	Object* closeSecondary;
	List<Object*> closeScenery; //Not used yet. For non repeating items.
	float closeOffset = 15.0f;
	float closeScrollOffset = 0.0f;
	//DO NOT USE DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float closeFollowSpeed = 2;


	Script* Duplicate() override
	{
		return  KROSS_ALLOCATION_REPORT(BackgroundManager());
	}

	void Start() override
	{
		sceneCam = SceneManager::GetCurrentScene()->GetCamera();
		furthestPrimary = SceneManager::GetCurrentScene()->FindObject("Furthest-A");
		furthestSecondary = SceneManager::GetCurrentScene()->FindObject("Furthest-B");
		
		secondFurthestPrimary = SceneManager::GetCurrentScene()->FindObject("Mountains-A");
		secondFurthestSecondary = SceneManager::GetCurrentScene()->FindObject("Mountains-B");

		closePrimary = SceneManager::GetCurrentScene()->FindObject("Close-A");
		closeSecondary = SceneManager::GetCurrentScene()->FindObject("Close-B");

		if (furthestPrimary != nullptr && furthestSecondary != nullptr) {
			furthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			furthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + furthestOffset;
		}
		if (secondFurthestPrimary != nullptr && secondFurthestSecondary != nullptr) {
			secondFurthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			secondFurthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + secondFurthestOffset;
		}
		if (closePrimary != nullptr && closeSecondary != nullptr) {
			closePrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			closeSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + closeOffset;
		}



	}


	void Update() override 
	{
		if (furthestPrimary != nullptr && furthestSecondary != nullptr) 
		{
			ManageLayer(furthestPrimary, furthestSecondary, furthestFollowSpeed, furthestOffset, furthestScrollOffset);
		}

		if (secondFurthestPrimary != nullptr && secondFurthestSecondary != nullptr)
		{
			ManageLayer(secondFurthestPrimary, secondFurthestSecondary, secondFurthestFollowSpeed, secondFurthestOffset, secondFurthestScrollOffset);
		}

		
		if (closePrimary != nullptr && closeSecondary != nullptr)
		{
			ManageLayer(closePrimary, closeSecondary, closeFollowSpeed, closeOffset, closeScrollOffset);
		}

	}

	void ManageLayer(Object* primary, Object* secondary, float followSpeed, float offset, float &scrollOffset) 
	{
		Transform2D* primaryTransform = primary->GetTransform();
		Transform2D* secondaryTransform = secondary->GetTransform();
		Transform2D* cameraTransform = sceneCam->GetTransform();


		scrollOffset = fmod(cameraTransform->m_Position.x, (offset * followSpeed));
		primaryTransform->m_Position.x = cameraTransform->m_Position.x - scrollOffset / followSpeed;
		secondaryTransform->m_Position.x = primaryTransform->m_Position.x + offset;


		//IF ITS WAY OUTTA RANGE, MOVE IT BACK IN.
		if (primaryTransform->m_Position.x < cameraTransform->m_Position.x - offset)
		{
			primaryTransform->m_Position.x += (2 * offset);
		}
		if (secondaryTransform->m_Position.x < cameraTransform->m_Position.x - offset)
		{
			secondaryTransform->m_Position.x += (2 * offset);
		}
		if (primaryTransform->m_Position.x > cameraTransform->m_Position.x + offset)
		{
			primaryTransform->m_Position.x -= (2 * offset);
		}
		if (secondaryTransform->m_Position.x > cameraTransform->m_Position.x + offset)
		{
			secondaryTransform->m_Position.x -= (2 * offset);
		}
	}


};