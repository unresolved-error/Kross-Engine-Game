#pragma once
#include <Kross.h>

using namespace Kross;

class ScrollCredits : public Script
{
private:
	float m_WaitTimer = 1.5f;
	Animator* m_Animator = nullptr;

public:
	ScrollCredits()
	{
		m_Name = "ScrollCredits";
	}
	~ScrollCredits() {}


	Script* Duplicate() override
	{
		return KROSS_NEW ScrollCredits();
	}

	void Start() override
	{
		m_Animator = GetComponent<Animator>();
	}

	void Update() override
	{
		if (m_WaitTimer > 0.0f) m_WaitTimer -= Time::GetDeltaTime();
		else
		{
			if (m_GameObject->GetName() != "Donut")
			{
				m_GameObject->m_Transform->m_Position.y += 0.5f * Time::GetDeltaTime();
			}

			else
			{
				if (m_GameObject->m_Transform->m_Position.y < 0.0f)
				{
					m_GameObject->m_Transform->m_Position.y += 0.5f * Time::GetDeltaTime();
				}
				else
				{
					if (m_Animator)
					{
						m_Animator->SetCurrentAnimation(1);
						m_GameObject->m_Transform->m_Position.x += Time::GetDeltaTime();
						m_GameObject->m_Transform->m_Rotation -= 2;

						if (m_GameObject->m_Transform->m_Position.x > 7.0f)
						{
							SceneManager::SetScene("Assets/Scenes/Menu.kscn");
						}
					}
				}
			}
		}
	}
};