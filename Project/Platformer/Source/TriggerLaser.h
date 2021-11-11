#pragma once

#include <Kross.h>

using namespace Kross;

class TriggerLaser : public Script
{
public:

	SpriteRenderer* renderer = nullptr;
	Object* m_ObjectToTrigger = nullptr;
	Object* m_ObjectThatTriggers = nullptr;
	RaycastData* m_RaycastData = nullptr;
	Sprite* m_Accepted = nullptr;


	TriggerLaser() :
		renderer(nullptr),
		m_ObjectToTrigger(nullptr),
		m_ObjectThatTriggers(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "TriggerLaser";
	};
	~TriggerLaser() {};

	Script* Duplicate() override
	{
		return KROSS_NEW TriggerLaser();
	}

	void Start() override
	{
		renderer = GetComponent<SpriteRenderer>();

		m_Accepted = ResourceManager::GetResource<Sprite>("Laser2-0");

		if (m_GameObject->GetName() == "Puzzle1Trigger1")
		{
			m_ObjectThatTriggers = SceneManager::GetScene()->FindObject("Player");
			m_ObjectToTrigger = SceneManager::GetScene()->FindObject("Puzzle1Cog1");
		}

		if (m_GameObject->GetName() == "TuteTrigger1")
		{
			m_ObjectThatTriggers = SceneManager::GetScene()->FindObject("Player");
			m_ObjectToTrigger = SceneManager::GetScene()->FindObject("Puzzle1Cog1");
		}

		if (m_GameObject->GetName() == "EndLaser")
		{
			m_ObjectThatTriggers = SceneManager::GetScene()->FindObject("Player");
			m_ObjectToTrigger = nullptr;
		}



		if (m_GameObject->GetName() == "Puzzle2Trigger1")
		{
			m_ObjectThatTriggers = SceneManager::GetScene()->FindObject("Player");
			m_ObjectToTrigger = SceneManager::GetScene()->FindObject("Puzzle2Cog1");
		}

		if (m_GameObject->GetName() == "Puzzle4Trigger1")
		{
			m_ObjectThatTriggers = SceneManager::GetScene()->FindObject("Player");
			m_ObjectToTrigger = SceneManager::GetScene()->FindObject("Puzzle4Cog1");
		}


	}

	void Update() override
	{
		SpriteRenderer* renderer = GetComponent<SpriteRenderer>();

		if (m_GameObject->GetName() == "Puzzle1Trigger1")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x > 13.5f && m_ObjectThatTriggers->m_Transform->m_Position.y < -3.0f)
			{
				m_ObjectToTrigger->GetComponent<Cog>()->TriggerMotor();
				renderer->GetMaterial()->SetDiffuse(m_Accepted);
			}
		}

		if (m_GameObject->GetName() == "TuteTrigger1")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x > 22.6 && m_ObjectThatTriggers->m_Transform->m_Position.y < -2.1f)
			{
				m_ObjectToTrigger->GetComponent<Cog>()->TriggerMotor();
				renderer->GetMaterial()->SetDiffuse(m_Accepted);
			}
		}

		if (m_GameObject->GetName() == "EndLaser")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x > 29.9)
			{
				renderer->GetMaterial()->SetDiffuse(m_Accepted);
				SceneManager::SetScene("Assets/Scenes/Main.kscn");
			}
		}

		if (m_GameObject->GetName() == "Puzzle2Trigger1")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x > 26.4f && m_ObjectThatTriggers->m_Transform->m_Position.y > 0.0f)
			{
				m_ObjectToTrigger->GetComponent<Cog>()->TriggerMotor();
				renderer->GetMaterial()->SetDiffuse(m_Accepted);
			}
		}


		if (m_GameObject->GetName() == "Puzzle4Trigger1")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x > 105.50 && m_ObjectThatTriggers->m_Transform->m_Position.y > -2.0f && m_ObjectThatTriggers->m_Transform->m_Position.y < -0.5f)
			{
				m_ObjectToTrigger->GetComponent<Cog>()->TriggerMotor();
				renderer->GetMaterial()->SetDiffuse(m_Accepted);
			}
		}



	}


};