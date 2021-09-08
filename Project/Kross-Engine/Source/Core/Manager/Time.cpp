/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Time.h"

namespace Kross
{
	Time*	Time::m_Instance =		nullptr;

	void Time::OnCreate()
	{
		if (!m_Instance)
		{
			m_Instance = KROSS_NEW Time();
		}
	}

	void Time::OnDestroy()
	{
		if (m_Instance)
		{
			delete m_Instance;
		}
	}

	void Time::OnUpdateDeltaTime()
	{
		/* Get the Current frame Time. */
		float currentTime = (float)glfwGetTime();
		
		/* Update Delta Time. */
		m_Instance->m_DeltaTime = (currentTime - m_Instance->m_PreviousTime);
		m_Instance->m_PreviousTime = currentTime;
	}
}
