/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include <Kross.h>
#include "Health.h"

using namespace Kross;

class HealthManager : public Script
{
public:
	friend class Health;

	HealthManager()
	{
		m_Name = "HealthManager";
	}
	~HealthManager() {}

	std::vector<Health*> m_Health;

	Script* Duplicate() override
	{
		return KROSS_NEW HealthManager();
	}

	void Start() override
	{
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Player")->AttachComponent<Health>());
		m_Health[0]->SetHealth(2.5f);

		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy1")->AttachComponent<Health>());
		m_Health[1]->SetHealth(4.0f);

		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy")->AttachComponent<Health>());
		m_Health[2]->SetHealth(4.0f);
	}

	void Update() override
	{
		for (int i = 0; i < m_Health.size(); i++)
		{
			if (!CheckAlive(m_Health[i]))
			{
				SceneManager::GetCurrentScene()->DetachObject(m_Health[i]->m_GameObject);

				m_Health[i] = nullptr;
				m_Health.erase(m_Health.begin() + i);

				continue;
			}
		}

		//if (m_Health[2] != nullptr)
		//{
		//	m_Health[2]->TakeDamage(1.0f * Time::GetDeltaTime());
		//	Debug::LogLine(m_Health[2]->GetHealth());
		//}
	}

	bool CheckAlive(Health* health)
	{
		return health->GetHealth() > 0.0f;
	}

	void DoDamage(Object* object, float damage)
	{
		for (int i = 0; i < m_Health.size(); i++)
		{
			if (m_Health[i]->m_GameObject == object)
			{
				m_Health[i]->TakeDamage(damage);
			}
		}
	}

	Health* GetInstance(int index) { return m_Health[index]; }
};
