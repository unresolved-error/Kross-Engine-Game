/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Keyframe.h"

namespace Kross
{
	class KROSS_API Animation
	{
	private:
		Animation() :
			m_Keyframes				(List<Keyframe*>()),
			m_DynamicAnimations		(List<Animation*>()),
			m_Name					("Animation"),
			m_Duration				(1.0f),
			m_KeyframeTime			(0.0f),
			m_KeyframeTimeElapsed	(0.0f),
			m_KeyframeCurrent		(0),
			m_IsStopped				(false)
		{};
		~Animation();

		List<Keyframe*> m_Keyframes;
		List<Animation*> m_DynamicAnimations;

		std::string m_Name;

		float m_Duration; /* Time in Seconds. */
		float m_KeyframeTime, m_KeyframeTimeElapsed;

		int m_KeyframeCurrent;

		bool m_IsStopped;

	protected:
		friend class Animator;

		// Gets the Current Keyframe.
		Keyframe* GetCurrentKeyframe() const { return m_Keyframes[m_KeyframeCurrent]; };

		// Sets the Current Index.
		void SetCurrentKeyframe(int index) { m_KeyframeCurrent = index; };

		// Sets the Animation Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Update Method.
		void OnUpdate();

		// Plays the Animation.
		void Play() { m_IsStopped = false; };

		// Pauses the Animation.
		void Pause() { m_IsStopped = true; };

		// Stops the Animation.
		void Stop();

	public:
		Animation(const Animation &other)
		{
			this->SetName(other.GetName());
			this->SetDuration(other.GetDuration());

			this->m_KeyframeCurrent = 0;

			for (int i = 0; i < other.m_Keyframes.size(); i++)
				this->AttachKeyframe(KROSS_NEW Keyframe(*other.m_Keyframes[i]));
		}
		// Sets the Animation Time. (IN SECONDS)
		void SetDuration(float duration);

		// Gets the Animation Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Animation Duration. (IN SECONDS)
		const float GetDuration() const { return m_Duration; };

		// Gets if the Animation is Playing.
		const bool IsPlaying() const { return !m_IsStopped; };

		// Adds a Keyframe.
		void AttachKeyframe(Keyframe* keyframe);

		// Removes a Keyframe.
		void DetachKeyFrame(int index);

		// Creates a blank Animation.
		static Animation* OnCreate(const std::string& name);

		// Destroys the Animation Specified.
		static void OnDestroy(Animation* animation);
	};
}