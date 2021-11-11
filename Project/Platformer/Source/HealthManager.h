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
		//m_Health.push_back(SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy1")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy2")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy3")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy4")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy5")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy6")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy7")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy8")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy9")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy10")->GetComponent<Health>());

		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy11")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy12")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy13")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy14")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy15")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy16")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy17")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy18")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy19")->GetComponent<Health>());
		m_Health.push_back(SceneManager::GetScene()->FindObject("Enemy20")->GetComponent<Health>());
	}

	void Update() override
	{	

			// if (!CheckAlive(m_Health[i]))
			// {
			// 	//SceneManager::GetCurrentScene()->DetachObject(m_Health[i]->m_GameObject);
			// 
			// 	 RespawnPlayer(i);
			// 	
			// 
			// 	m_Health[i]->SetHealth(3.0f);
			// 
			// 	continue;
			// }
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

			//	Debug::LogLine(i);
			}
		}
	}

	void RespawnPlayer(int index)
	{
		// Vector2 respawnPoint(1.0f, 1.0f);
		// Vector2 resetVelocity(0.0f, 0.0f);
		// if (index == 0)
		// {
		// 	SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
		// 	SceneManager::GetCurrentScene()->FindObject("Player")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		// }
		// else if (index == 1)
		// {
		// 	SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
		// 	SceneManager::GetCurrentScene()->FindObject("Enemy1")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		// }
		// else if (index == 2)
		// {
		// 	SceneManager::GetCurrentScene()->FindObject("Enemy")->GetComponent<Rigidbody2D>()->SetBodyPos(respawnPoint);
		// 	SceneManager::GetCurrentScene()->FindObject("Enemy")->GetComponent<Rigidbody2D>()->SetBodyVelocity(resetVelocity);
		// }
	}

	Health* GetInstance(int index) { return m_Health[index]; }
};
