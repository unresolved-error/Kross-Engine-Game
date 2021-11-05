#pragma once

#include <Kross.h>
#include "bgAudioManager.h"


using namespace Kross;

class StartButton : public Script
{
public:
	StartButton()
	{
		/* Every Script Must do this! */
		m_Name = "StartButton";
	};
	~StartButton() {};

	float m_MinX, m_MinY, m_MaxX, m_MaxY;

	Script* Duplicate() override
	{
		return KROSS_NEW StartButton();
	}

	void Start() override
	{
		Vector2 scale = m_GameObject->m_Transform->m_Scale;
		m_MinX = -0.4f * scale.x;
		m_MaxX = 0.4f * scale.x;
		m_MinY = 0.25f * scale.y;
		m_MaxY = -0.25f * scale.y;

		Application::GetWindow()->UnHideCursor();
	}

	void Update() override
	{
		Vector2 mousePos = Input::GetMousePosition();
		Window* window = Application::GetWindow();
		float aspectRatio = window->GetApsectRatio();

		Camera* camera = SceneManager::GetScene()->GetCamera()->GetComponent<Camera>();

		Vector2 mousePoint = (Vector2(((mousePos.x / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((mousePos.y / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize()) + camera->m_GameObject->m_Transform->m_Position;

		if (mousePoint.x <= m_GameObject->m_Transform->m_Position.x + m_MaxX && mousePoint.x >= m_GameObject->m_Transform->m_Position.x + m_MinX && 
			mousePoint.y >= m_GameObject->m_Transform->m_Position.y + m_MaxY && mousePoint.y <= m_GameObject->m_Transform->m_Position.y + m_MinY)
		{
			if (Input::GetMouseButtonReleased(Mouse::Left))
			{
				leaveLevel = true;
				SceneManager::SetScene("Assets/Scenes/Main.kscn");
			}
		}
	}
};