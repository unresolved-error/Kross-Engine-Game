#pragma once

#include <Kross.h>

using namespace Kross;

class DoorFunny : public Script
{
public:
	DoorFunny()
	{
		/* Every Script Must do this! */
		m_Name = "DoorFunny";
	};
	~DoorFunny() {};

	bool m_Open = false;
	Rigidbody2D* m_Rigidbody = nullptr;
	Object* m_Player = nullptr;

	Script* Duplicate() override
	{
		return KROSS_NEW DoorFunny();
	}

	void Start() override
	{
		m_Rigidbody = GetComponent<Rigidbody2D>();
		m_Player = SceneManager::GetCurrentScene()->FindObject("Player");
	}

	void Update() override
	{
		if (m_Player->m_Transform->m_Position.x > m_GameObject->m_Transform->m_Position.x)
		{
			if (!m_Open)
			{
				Debug::Log("Im a poo");
				m_Open = true;
				m_Rigidbody->OnApplyImpulse(Vector2(10.0f, 0.0f));
			}
		}
	}
};