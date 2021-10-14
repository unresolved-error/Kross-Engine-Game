/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once
#include <Kross.h>

using namespace Kross;

class Health : public Script
{
private:
	float m_Health = 10.0f;
	float m_MaxHealth = m_Health;

public:
	Health()
	{
		m_Name = "Health";
	}
	~Health() {}


	Script* Duplicate() override
	{
		return KROSS_NEW Health();
	}

	void Start() override
	{
		m_MaxHealth = m_Health;
	}

	void SetHealth(float health) 
	{ 
		m_Health = health;
		m_MaxHealth = m_Health;
	}
	float GetHealth() { return m_Health; }

	void SetMaxHealth(float max) { m_MaxHealth = max; }
	float GetMaxHealth() { return m_MaxHealth; }

	void TakeDamage(float damage) { m_Health -= damage; }

	void Heal(float heal)
	{
		m_Health += heal;

		if (m_Health > m_MaxHealth)
		{
			m_Health = m_MaxHealth;
		}
	}
};