/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Animation.h"

#include "../Manager/Time.h"
#include "../Manager/ResourceManager.h"

namespace Kross
{
	Animation::~Animation()
	{
		/* Go through each Keyframe. */
		for (int i = 0; i < m_Keyframes.size(); i++)
		{
			/* Delete the Keyframe and null it out. */
			delete m_Keyframes[i];
			m_Keyframes[i] = nullptr;
		}
	}

	Animation* Animation::OnCreate(const std::string& name)
	{
		/* Create a Blank animation. */
		Animation* animation = new Animation();
		animation->SetName(name);

		/* Attach itself to the Resource Manager. */
		ResourceManager::AttachResource<Animation>(animation);

		/* Return the new Animation. */
		return animation;
	}

	void Animation::OnDestroy(Animation* animation)
	{
		/* Safe programming, not needed but good to have. */
		if (animation)
			delete animation;
	}

	void Animation::OnUpdate()
	{
		/* If the Animation isn't Playing, early out. */
		if (m_IsStopped)
			return;

		/* Check if the Frame Time hasn't hit the Max. */
		if (m_KeyframeTimeElapsed < m_KeyframeTime)
			m_KeyframeTimeElapsed += Time::GetDeltaTime();

		/* If it has. */
		else
		{
			/* Loop back around. */
			if (m_KeyframeCurrent >= m_Keyframes.size() - 1)
				m_KeyframeCurrent = 0;

			/* Continue up. */
			else
				m_KeyframeCurrent++;

			/* Reset the Elapsed Time. */
			m_KeyframeTimeElapsed = 0.0f;
		}
	}

	void Animation::SetDuration(float duration)
	{
		/* Set the Duration. */
		m_Duration = duration;

		/* Calculate the time of each frame. */
		m_KeyframeTime = m_Duration / (float)m_Keyframes.size();
	}

	void Animation::OnStop()
	{
		/* Reset the Animation. */
		m_KeyframeCurrent = 0;
		m_KeyframeTimeElapsed = 0.0f;

		/* Stop the Animation. */
		m_IsStopped = true;
	}

	void Animation::AttachKeyframe(Keyframe* keyframe)
	{
		/* Attach the Keyframe. */
		m_Keyframes.push_back(keyframe);

		/* Calculate the time of each frame. */
		m_KeyframeTime = m_Duration / (float)m_Keyframes.size();
	}

	void Animation::DetachKeyFrame(int index)
	{
		/* Delete the Keyframe. */
		delete m_Keyframes[index];
		m_Keyframes[index] = nullptr;

		/* Remove the Keyframe. */
		m_Keyframes.erase(m_Keyframes.begin() + index);

		/* Calculate the time of each frame. */
		m_KeyframeTime = m_Duration / (float)m_Keyframes.size();
	}
}