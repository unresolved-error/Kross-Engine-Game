#pragma once

#include <Kross.h>

using namespace Kross;

class CameraLock : public Script
{
public:
	CameraLock()
	{
		/* Every Script Must do this! */
		m_Name = "CameraLock";
	};
	~CameraLock() {};

	float m_MinX, m_MinY, m_MaxX, m_MaxY;

	Script* Duplicate() override
	{
		return KROSS_NEW CameraLock();
	}

	void Start() override
	{
		m_MinX = 0.0f;
		m_MinY = -0.5f;
		m_MaxY = 2.0f;
	}

	void Update() override
	{
		//c_Object->GetTransform()->m_Position.x = glm::clamp(c_Object->GetTransform()->m_Position.x, m_MinX, m_MaxX);
		//c_Object->GetTransform()->m_Position.y = glm::clamp(c_Object->GetTransform()->m_Position.y, m_MinY, m_MaxY);
	}
};