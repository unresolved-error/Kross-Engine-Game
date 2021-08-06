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


	//FURTHEST BACKGROUND MANAGEMENT. //Layer is called "background"
	Object* furthestPrimary;
	Object* furthestSecondary;
	List<Object*> furthestScenery; //Not used yet. For non repeating items.
	List<float> furthestSceneryInitXPos;
	float furthestOffset = 15.0f;
	float furthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float furthestFollowSpeed = 5.0f;

	//2ndFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background1"
	Object* secondFurthestPrimary;
	Object* secondFurthestSecondary;
	List<Object*> secondFurthestScenery; //Not used yet. For non repeating items.
	List<float> secondFurthestSceneryInitXPos;
	float secondFurthestOffset = 15.0f;
	float secondFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float secondFurthestFollowSpeed = 4.0f;

	//3ndFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background2"
	Object* thirdFurthestPrimary;
	Object* thirdFurthestSecondary;
	List<Object*> thirdFurthestScenery; //Not used yet. For non repeating items.
	List<float> thirdFurthestSceneryInitXPos;
	float thirdFurthestOffset = 15.0f;
	float thirdFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float thirdFurthestFollowSpeed = 3.5f;

	//4thFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background3"
	Object* fourthFurthestPrimary;
	Object* fourthFurthestSecondary;
	List<Object*> fourthFurthestScenery; //Not used yet. For non repeating items.
	List<float> fourthFurthestSceneryInitXPos;
	float fourthFurthestOffset = 15.0f;
	float fourthFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float fourthFurthestFollowSpeed = 3.0f;

	//3rd CLOSEST BACKGROUND MANAGEMENT.//Layer is called "background4"
	Object* thirdClosePrimary;
	Object* thirdCloseSecondary;
	List<Object*> thirdCloseScenery; //Not used yet. For non repeating items.
	List<float> thirdCloseSceneryInitXPos;
	float thirdCloseOffset = 15.0f;
	float thirdCloseScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float thirdCloseFollowSpeed = 2.5f;


	//2nd CLOSEST BACKGROUND MANAGEMENT.//Layer is called "background5"
	Object* secondClosePrimary;
	Object* secondCloseSecondary;
	List<Object*> secondCloseScenery; //Not used yet. For non repeating items.
	List<float> secondCloseSceneryInitXPos;
	float secondCloseOffset = 15.0f;
	float secondCloseScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float secondCloseFollowSpeed = 2.0f;


	//CLOSE BACKGROUND MANAGEMENT. //Layer is called "background6"
	Object* closePrimary;
	Object* closeSecondary;
	List<Object*> closeScenery; //Not used yet. For non repeating items.
	List<float> closeSceneryInitXPos;
	float closeOffset = 15.0f;
	float closeScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float closeFollowSpeed = 1.5f;
	

	//CLOSE BACKGROUND MANAGEMENT. //Layer is called "background6"
	Object* foreGroundPrimary;
	Object* foreGroundSecondary;
	List<Object*> foreGroundScenery; //Not used yet. For non repeating items.
	List<float> foreGroundSceneryInitXPos;
	float foreGroundOffset = 15.0f;
	float foreGroundScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float foreGroundFollowSpeed = 0.75f;




	Script* Duplicate() override
	{
		return KROSS_NEW BackgroundManager();
	}

	void Start() override
	{
		sceneCam = SceneManager::GetCurrentScene()->GetCamera();

		furthestPrimary = SceneManager::GetCurrentScene()->FindObject("Furthest-A");
		furthestSecondary = SceneManager::GetCurrentScene()->FindObject("Furthest-B");
		/*Add scenery Search and pushback on this line.*/
		
		secondFurthestPrimary = SceneManager::GetCurrentScene()->FindObject("SecondFurthest-A");
		secondFurthestSecondary = SceneManager::GetCurrentScene()->FindObject("SecondFurthest-B");
		/*Add scenery Search and pushback on this line.*/

		thirdFurthestPrimary = SceneManager::GetCurrentScene()->FindObject("ThirdFurthest-A");
		thirdFurthestSecondary = SceneManager::GetCurrentScene()->FindObject("ThirdFurthest-B");
		/*Add scenery check on this line.*/


		fourthFurthestPrimary = SceneManager::GetCurrentScene()->FindObject("FourthFurthest-A");
		fourthFurthestSecondary = SceneManager::GetCurrentScene()->FindObject("FourthFurthest-B");
		 /*FIX scenery Search and pushback on this line.*/
		fourthFurthestScenery.push_back(SceneManager::GetCurrentScene()->FindObject("BluePop"));

		thirdClosePrimary = SceneManager::GetCurrentScene()->FindObject("ThirdClose-A");
		thirdCloseSecondary = SceneManager::GetCurrentScene()->FindObject("ThirdClose-B");
		/*Add scenery check on this line.*/

		secondClosePrimary = SceneManager::GetCurrentScene()->FindObject("SecondClose-A");
		secondCloseSecondary = SceneManager::GetCurrentScene()->FindObject("SecondClose-B");
		/*Add scenery check on this line.*/

		closePrimary = SceneManager::GetCurrentScene()->FindObject("Close-A");
		closeSecondary = SceneManager::GetCurrentScene()->FindObject("Close-B");
		/*Add scenery check on this line.*/

		foreGroundPrimary = SceneManager::GetCurrentScene()->FindObject("Foreground-A");
		foreGroundSecondary = SceneManager::GetCurrentScene()->FindObject("Foreground-B");
		/*Add scenery check on this line.*/

		/*POPULATE THE INIT X POS*/
		furthestSceneryInitXPos = SetInitialSceneryXpos(furthestScenery);
		secondFurthestSceneryInitXPos = SetInitialSceneryXpos(secondFurthestScenery);
		thirdFurthestSceneryInitXPos = SetInitialSceneryXpos(thirdFurthestScenery);
		fourthFurthestSceneryInitXPos = SetInitialSceneryXpos(fourthFurthestScenery);
		thirdCloseSceneryInitXPos = SetInitialSceneryXpos(thirdCloseScenery);
		secondCloseSceneryInitXPos = SetInitialSceneryXpos(secondCloseScenery);
		closeSceneryInitXPos = SetInitialSceneryXpos(closeScenery);
		foreGroundSceneryInitXPos = SetInitialSceneryXpos(foreGroundScenery);


		if (furthestPrimary != nullptr && furthestSecondary != nullptr) {
			furthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			furthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + furthestOffset;
		}
		if (secondFurthestPrimary != nullptr && secondFurthestSecondary != nullptr) {
			secondFurthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			secondFurthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + secondFurthestOffset;
		}

		if (thirdFurthestPrimary != nullptr && thirdFurthestSecondary != nullptr) {
			thirdFurthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			thirdFurthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + thirdFurthestOffset;
		}

		if (fourthFurthestPrimary != nullptr && fourthFurthestSecondary != nullptr) {
			fourthFurthestPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			fourthFurthestSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + fourthFurthestOffset;
		}

		if (thirdClosePrimary != nullptr && thirdCloseSecondary != nullptr) {
			thirdClosePrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			thirdCloseSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + thirdCloseOffset;
		}

		if (secondClosePrimary != nullptr && secondCloseSecondary != nullptr) {
			secondClosePrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			secondCloseSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + secondCloseOffset;
		}

		if (closePrimary != nullptr && closeSecondary != nullptr) {
			closePrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			closeSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + closeOffset;
		}

		if (foreGroundPrimary != nullptr && closeSecondary != nullptr) {
			foreGroundPrimary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x;
			foreGroundSecondary->GetTransform()->m_Position.x = sceneCam->GetTransform()->m_Position.x + foreGroundOffset;
		}

	}


	void Update() override 
	{
		if (furthestPrimary != nullptr && furthestSecondary != nullptr) 
		{
			ManageLayer(furthestPrimary, furthestSecondary, furthestFollowSpeed, furthestOffset, furthestScrollOffset, furthestScenery, furthestSceneryInitXPos);
		}

		if (secondFurthestPrimary != nullptr && secondFurthestSecondary != nullptr)
		{
			ManageLayer(secondFurthestPrimary, secondFurthestSecondary, secondFurthestFollowSpeed, secondFurthestOffset, secondFurthestScrollOffset, secondFurthestScenery, secondFurthestSceneryInitXPos);
		}

		if (thirdFurthestPrimary != nullptr && thirdFurthestSecondary != nullptr)
		{
			ManageLayer(thirdFurthestPrimary, thirdFurthestSecondary, thirdFurthestFollowSpeed, thirdFurthestOffset, thirdFurthestScrollOffset, thirdFurthestScenery, thirdFurthestSceneryInitXPos);
		}

		if (fourthFurthestPrimary != nullptr && fourthFurthestSecondary != nullptr)
		{
			ManageLayer(fourthFurthestPrimary, fourthFurthestSecondary, fourthFurthestFollowSpeed, fourthFurthestOffset, fourthFurthestScrollOffset, fourthFurthestScenery, fourthFurthestSceneryInitXPos);
		}

		if (thirdClosePrimary != nullptr && thirdCloseSecondary != nullptr)
		{
			ManageLayer(thirdClosePrimary, thirdCloseSecondary, thirdCloseFollowSpeed, thirdCloseOffset, thirdCloseScrollOffset, thirdCloseScenery, thirdCloseSceneryInitXPos);
		}

		if (secondClosePrimary != nullptr && secondCloseSecondary != nullptr)
		{
			ManageLayer(secondClosePrimary, secondCloseSecondary, secondCloseFollowSpeed, secondCloseOffset, secondCloseScrollOffset, secondCloseScenery, secondCloseSceneryInitXPos);
		}

		if (closePrimary != nullptr && closeSecondary != nullptr)
		{
			ManageLayer(closePrimary, closeSecondary, closeFollowSpeed, closeOffset, closeScrollOffset, closeScenery, closeSceneryInitXPos);
		}

		if (foreGroundPrimary != nullptr && foreGroundSecondary != nullptr)
		{
			ManageLayer(foreGroundPrimary, foreGroundSecondary, foreGroundFollowSpeed, foreGroundOffset, foreGroundScrollOffset, foreGroundScenery, foreGroundSceneryInitXPos);
		}

	}

	
	List<float> SetInitialSceneryXpos(List<Object*> sceneryList)
	{
		if (!sceneryList.empty()) 
		{
			List<float> xPos;

			for (int i = 0; i < sceneryList.size(); i++)
			{
				xPos.push_back(sceneryList[i]->GetTransform()->m_Position.x);
			}
			return xPos;
		}
		else 
		{
			return List<float>();
		}
	
	}

	void ManageLayer(Object* primary, Object* secondary, float followSpeed, float offset, float &scrollOffset, List<Object*> sceneryList, List<float> initSceneryXPos) 
	{
		Transform2D* primaryTransform = primary->GetTransform();
		Transform2D* secondaryTransform = secondary->GetTransform();
		Transform2D* cameraTransform = sceneCam->GetTransform();
		

		scrollOffset = fmod(cameraTransform->m_Position.x, (offset * followSpeed));

		primaryTransform->m_Position.x = cameraTransform->m_Position.x - (scrollOffset / followSpeed);
		secondaryTransform->m_Position.x = primaryTransform->m_Position.x + offset;

		

		if (!sceneryList.empty()) 
		{
			for (int i = 0; i < sceneryList.size(); i++)
			{
				sceneryList[i]->GetTransform()->m_Position.x = cameraTransform->m_Position.x - (cameraTransform->m_Position.x / followSpeed) + initSceneryXPos[i];
			}
		}

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