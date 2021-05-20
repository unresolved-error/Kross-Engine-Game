/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Time.h"

namespace Kross
{
	float Time::s_DeltaTime = 0.0f;
	float Time::s_PreviousTime = 0.0f;

	Time* Time::s_Instance = nullptr;

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
		float currentTime = glfwGetTime();
		
		/* Update Delta Time. */
		s_DeltaTime = (currentTime - s_PreviousTime);
		
		s_PreviousTime = currentTime;
	}
}
