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
	/*!
		\class Animation
		\details Used for Sprite Animations or for timed / sequenced position, rotation and scaling.
	*/
	class KROSS_API Animation
	{
	private:
		/*!
		    Animation Contructor.
		*/
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
		/*!
		    Animation Destructor.
		*/
		~Animation();

		List<Keyframe*> m_Keyframes;
		List<Animation*> m_DynamicAnimations;

		std::string m_Name;

		float m_Duration; /* Time in Seconds. */
		float m_KeyframeTime, m_KeyframeTimeElapsed;

		int m_KeyframeCurrent;

		bool m_IsStopped;

	protected:
		/*!
		    Gives Animator access to all Protected and Private areas of the class.
		*/
		friend class Animator;

		/*!
			Gets the Current Keyframe. 
		*/
		Keyframe* GetCurrentKeyframe() const { return m_Keyframes[m_KeyframeCurrent]; };

		/*!
			Sets the Current Index.
			\attention Index must be between 0 and Keyframe Size - 1!
		*/
		void SetCurrentKeyframe(int index) { m_KeyframeCurrent = index; };

		/*! 
			Sets the Animation Name.
		*/
		void SetName(const std::string& name) { m_Name = name; };

		/*!
			The Update Method.
		*/
		void OnUpdate();

		/*!
			Plays the Animation.
		*/
		void Play() { m_IsStopped = false; };

		/*!
			Pauses the Animation.
		*/
		void Pause() { m_IsStopped = true; };

		/*!
			Stops the Animation.
		*/
		void Stop();

	public:
		/*!
			Copy Contructor.
		*/
		Animation(const Animation& other);

		/*!
			Sets the Animation Duration.
			\note Duration is in Seconds.
			\attention Must be above zero!
		*/
		void SetDuration(float duration);

		/*!
			Gets the Animation Name.
		*/
		const std::string GetName() const { return m_Name; };

		/*!
			Gets the Animation Duration.
			\note Duration is in Seconds.
		*/
		const float GetDuration() const { return m_Duration; };

		/*!
			Gets if the Animation is Playing.
		*/
		const bool IsPlaying() const { return !m_IsStopped; };

		/*!
			Adds a Keyframe.
		*/
		void AttachKeyframe(Keyframe* keyframe);

		/*!
			Removes a Keyframe.
		*/
		void DetachKeyFrame(int index);

		/*!
			Creates a blank Animation.
		*/
		static Animation* OnCreate(const std::string& name);

		/*!
			Destroys the Animation Specified.
		*/
		static void OnDestroy(Animation* animation);
	};
}