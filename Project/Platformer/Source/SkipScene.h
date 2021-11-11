#pragma once
#include <Kross.h>

using namespace Kross;

class SkipScene : public Script
{
private:
	float m_WaitTimer = 1.5f;
	Animator* m_Animator = nullptr;

public:
	SkipScene()
	{
		m_Name = "SkipScene";
	}
	~SkipScene() {}


	Script* Duplicate() override
	{
		return KROSS_NEW SkipScene();
	}

	void Update() override
	{
		if (SceneManager::GetScene()->GetName() == "Credits")
		{
			if (Input::GetMouseButtonPressed(Mouse::Left))
			{
				SceneManager::SetScene("Assets/Scenes/Menu.kscn");
			}
		}
	}
};