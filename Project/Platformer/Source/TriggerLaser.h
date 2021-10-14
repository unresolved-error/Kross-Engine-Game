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

		if (m_GameObject->GetName() == "Puzzle1Trigger1")
		{
			m_ObjectThatTriggers = SceneManager::GetCurrentScene()->FindObject("Puzzle1AllSort1");
			m_ObjectToTrigger = SceneManager::GetCurrentScene()->FindObject("Puzzle1Cog1");			
		}

	}

	void Update() override
	{
		if (m_GameObject->GetName() == "Puzzle1Trigger1")
		{
			if (m_ObjectThatTriggers->m_Transform->m_Position.x < 11.5f)
			{
				
				m_ObjectToTrigger->GetComponent<Cog>()->TriggerMotor();
			}
		}
	}


};