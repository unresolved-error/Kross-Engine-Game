/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"

namespace Kross
{
	class KROSS_API Profiler : public EditorWindow
	{
	private:
		List<float> m_FramesRecorded;
		float m_FrameCache[24]{ 0.0f };
		float m_TimeElapsed;
		float m_FrameCount;
	protected:

	public:
		Profiler() :
			m_FramesRecorded	(List<float>()),
			m_TimeElapsed		(0.0f),
			m_FrameCount		(0.0f)
		{};
		~Profiler() {};

		// Sets the Asset Directory Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;

	};
}