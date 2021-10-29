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
	std::vector<Object*> furthestScenery; //Not used yet. For non repeating items.
	std::vector<float> furthestSceneryInitXPos;
	float furthestOffset = 15.0f;
	float furthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float furthestFollowSpeed = 5.0f;

	//2ndFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background1"
	Object* secondFurthestPrimary;
	Object* secondFurthestSecondary;
	std::vector<Object*> secondFurthestScenery; //Not used yet. For non repeating items.
	std::vector<float> secondFurthestSceneryInitXPos;
	float secondFurthestOffset = 15.0f;
	float secondFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float secondFurthestFollowSpeed = 4.0f;

	//3ndFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background2"
	Object* thirdFurthestPrimary;
	Object* thirdFurthestSecondary;
	std::vector<Object*> thirdFurthestScenery; //Not used yet. For non repeating items.
	std::vector<float> thirdFurthestSceneryInitXPos;
	float thirdFurthestOffset = 15.0f;
	float thirdFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float thirdFurthestFollowSpeed = 3.5f;

	//4thFURTHEST BACKGROUND MANAGEMENT.//Layer is called "background3"
	Object* fourthFurthestPrimary;
	Object* fourthFurthestSecondary;
	std::vector<Object*> fourthFurthestScenery; //Not used yet. For non repeating items.
	std::vector<float> fourthFurthestSceneryInitXPos;
	float fourthFurthestOffset = 15.0f;
	float fourthFurthestScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float fourthFurthestFollowSpeed = 3.0f;

	//3rd CLOSEST BACKGROUND MANAGEMENT.//Layer is called "background4"
	Object* thirdClosePrimary;
	Object* thirdCloseSecondary;
	std::vector<Object*> thirdCloseScenery; //Not used yet. For non repeating items.
	std::vector<float> thirdCloseSceneryInitXPos;
	float thirdCloseOffset = 15.0f;
	float thirdCloseScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float thirdCloseFollowSpeed = 2.5f;


	//2nd CLOSEST BACKGROUND MANAGEMENT.//Layer is called "background5"
	Object* secondClosePrimary;
	Object* secondCloseSecondary;
	std::vector<Object*> secondCloseScenery; //Not used yet. For non repeating items.
	std::vector<float> secondCloseSceneryInitXPos;
	float secondCloseOffset = 15.0f;
	float secondCloseScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float secondCloseFollowSpeed = 2.0f;


	//CLOSE BACKGROUND MANAGEMENT. //Layer is called "background6"
	Object* closePrimary;
	Object* closeSecondary;
	std::vector<Object*> closeScenery; //Not used yet. For non repeating items.
	std::vector<float> closeSceneryInitXPos;
	float closeOffset = 15.0f;
	float closeScrollOffset = 0.0f;
	//DECIMAL FOR FOREGROUND, ABOVE 1 FOR BACK GROUND. IF THIS IS '2' THE BACK GROUND WILL MOVE AT HALF THE RATE OF THE PLAYGROUND. AT "0.5" IT WILL MOVE TWICE AS QUICKLY.
	float closeFollowSpeed = 1.5f;
	

	//CLOSE BACKGROUND MANAGEMENT. //Layer is called "background6"
	Object* foreGroundPrimary;
	Object* foreGroundSecondary;
	std::vector<Object*> foreGroundScenery; //Not used yet. For non repeating items.
	std::vector<float> foreGroundSceneryInitXPos;
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
		sceneCam = SceneManager::GetScene()->GetCamera();

		furthestPrimary = SceneManager::GetScene()->FindObject("Furthest-A");
		furthestSecondary = SceneManager::GetScene()->FindObject("Furthest-B");
		/*Add scenery Search and pushback on this line.*/
		
		secondFurthestPrimary = SceneManager::GetScene()->FindObject("SecondFurthest-A");
		secondFurthestSecondary = SceneManager::GetScene()->FindObject("SecondFurthest-B");
		/*Add scenery Search and pushback on this line.*/

		thirdFurthestPrimary = SceneManager::GetScene()->FindObject("ThirdFurthest-A");
		thirdFurthestSecondary = SceneManager::GetScene()->FindObject("ThirdFurthest-B");
		/*Add scenery check on this line.*/


		fourthFurthestPrimary = SceneManager::GetScene()->FindObject("FourthFurthest-A");
		fourthFurthestSecondary = SceneManager::GetScene()->FindObject("FourthFurthest-B");
		 /*FIX scenery Search and pushback on this line.*/
		fourthFurthestScenery.push_back(SceneManager::GetScene()->FindObject("BluePop"));

		thirdClosePrimary = SceneManager::GetScene()->FindObject("ThirdClose-A");
		thirdCloseSecondary = SceneManager::GetScene()->FindObject("ThirdClose-B");
		/*Add scenery check on this line.*/

		secondClosePrimary = SceneManager::GetScene()->FindObject("SecondClose-A");
		secondCloseSecondary = SceneManager::GetScene()->FindObject("SecondClose-B");
		/*Add scenery check on this line.*/

		closePrimary = SceneManager::GetScene()->FindObject("Close-A");
		closeSecondary = SceneManager::GetScene()->FindObject("Close-B");
		/*Add scenery check on this line.*/

		foreGroundPrimary = SceneManager::GetScene()->FindObject("Foreground-A");
		foreGroundSecondary = SceneManager::GetScene()->FindObject("Foreground-B");
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


		if (furthestPrimary != nullptr && furthestSecondary != nullptr) 
		{
			furthestPrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			furthestSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + furthestOffset;
		}
		if (secondFurthestPrimary != nullptr && secondFurthestSecondary != nullptr) 
		{
			secondFurthestPrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			secondFurthestSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + secondFurthestOffset;
		}
		if (thirdFurthestPrimary != nullptr && thirdFurthestSecondary != nullptr) 
		{
			thirdFurthestPrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			thirdFurthestSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + thirdFurthestOffset;
		}
		if (fourthFurthestPrimary != nullptr && fourthFurthestSecondary != nullptr) 
		{
			fourthFurthestPrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			fourthFurthestSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + fourthFurthestOffset;
		}
		if (thirdClosePrimary != nullptr && thirdCloseSecondary != nullptr) 
		{
			thirdClosePrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			thirdCloseSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + thirdCloseOffset;
		}
		if (secondClosePrimary != nullptr && secondCloseSecondary != nullptr) 
		{
			secondClosePrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			secondCloseSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + secondCloseOffset;
		}
		if (closePrimary != nullptr && closeSecondary != nullptr) 
		{
			closePrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			closeSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + closeOffset;
		}
		if (foreGroundPrimary != nullptr && closeSecondary != nullptr) 
		{
			foreGroundPrimary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x;
			foreGroundSecondary->m_Transform->m_Position.x = sceneCam->m_Transform->m_Position.x + foreGroundOffset;
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

	
	std::vector<float> SetInitialSceneryXpos(std::vector<Object*> sceneryList)
	{
		if (!sceneryList.empty()) 
		{
			std::vector<float> xPos;

			for (int i = 0; i < sceneryList.size(); i++)
			{
				xPos.push_back(sceneryList[i]->m_Transform->m_Position.x);
			}
			return xPos;
		}
		else 
		{
			return std::vector<float>();
		}
	
	}

	void ManageLayer(Object* primary, Object* secondary, float followSpeed, float offset, float &scrollOffset, std::vector<Object*> sceneryList, std::vector<float> initSceneryXPos) 
	{
		Transform2D* primaryTransform = primary->m_Transform;
		Transform2D* secondaryTransform = secondary->m_Transform;
		Transform2D* cameraTransform = sceneCam->m_Transform;
		

		scrollOffset = fmod(cameraTransform->m_Position.x, (offset * followSpeed));

		primaryTransform->m_Position.x = cameraTransform->m_Position.x - (scrollOffset / followSpeed);
		secondaryTransform->m_Position.x = primaryTransform->m_Position.x + offset;

		

		if (!sceneryList.empty()) 
		{
			for (int i = 0; i < sceneryList.size(); i++)
			{
				sceneryList[i]->m_Transform->m_Position.x = cameraTransform->m_Position.x - (cameraTransform->m_Position.x / followSpeed) + initSceneryXPos[i];
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