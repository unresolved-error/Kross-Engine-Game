/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Time.h"

namespace Kross
{
	Time*	Time::s_Instance =		nullptr;

	void Time::OnCreate()
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW Time();
	}

	void Time::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}

	void Time::OnUpdateDeltaTime()
	{
		/* Get the Current frame Time. */
		float currentTime = (float)glfwGetTime();
		
		/* Update Delta Time. */
		s_Instance->m_DeltaTime = (currentTime - s_Instance->m_PreviousTime);
		s_Instance->m_PreviousTime = currentTime;
	}
}
