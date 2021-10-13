#pragma once

#include <Kross.h>

using namespace Kross;

class TriggerLaser : public Script
{
public:

	SpriteRenderer* renderer = nullptr;
	Cog* m_ObjectToTrigger = nullptr;
	Object* m_ObjectThatTriggers = nullptr;

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
			m_ObjectThatTriggers = SceneManager::GetCurrentScene()->FindObject("Puzzle1AllSorts1");
			m_ObjectToTrigger = (Cog*)SceneManager::GetCurrentScene()->FindObject("Puzzle1Cog1");
		}

	}

	void Update() override
	{
		if (m_ObjectThatTriggers->m_Transform->m_Position.x <= m_GameObject->m_Transform->m_Position.x)
		{
			m_ObjectToTrigger->TriggerMotor();
		}
	}

};