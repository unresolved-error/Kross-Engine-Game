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
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy2")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy3")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy4")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy5")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy6")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy7")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy8")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy9")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy10")->GetComponent<Health>());

		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy11")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy12")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy13")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy14")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy15")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy16")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy17")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy18")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy19")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy20")->GetComponent<Health>());
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
