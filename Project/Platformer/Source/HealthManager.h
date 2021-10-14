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
		m_Health[0]->SetHealth(2.5f);

		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Health>());
		m_Health[1]->SetHealth(4.0f);

		m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Enemy")->GetComponent<Health>());
		m_Health[2]->SetHealth(4.0f);
	}

	void Update() override
	{
		for (int i = 0; i < m_Health.size(); i++)
		{
			if (!CheckAlive(m_Health[i]))
			{
				//SceneManager::GetCurrentScene()->DetachObject(m_Health[i]->m_GameObject);

				RespawnPlayer(i);
				

				m_Health[i]->SetHealth(3.0f);

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

				Debug::LogLine(i);
			}
		}
	}

	void RespawnPlayer(int index)
	{
		Vector2 respawnPoint(1.0f, 1.0f);
		Vector2 resetVelocity(0.0f, 0.0f);
		if (index == 0)
		{
			SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
			SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		}
		else if (index == 1)
		{
			SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
			SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		}
		else if (index == 2)
		{
			SceneManager::GetCurrentScene()->FindObject("Enemy")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
			SceneManager::GetCurrentScene()->FindObject("Enemy")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		}
	}

	Health* GetInstance(int index) { return m_Health[index]; }
};
