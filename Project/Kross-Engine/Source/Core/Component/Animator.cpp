/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Animator.h"

namespace Kross
{
	Animator::~Animator()
	{
		/* Clear the Data. */
		m_Animations.clear();

		/* Null everything out. */
		p_AnimationCurrent = nullptr;
		p_Renderer = nullptr;
		p_Transform = nullptr;
	}

	void Animator::OnStart()
	{
		/* Grab the Object. */
		Object* gameObject = (Object*)c_Object;

		/* Get the Components needed. */
		p_Rigidbody = gameObject->GetComponent<Rigidbody2D>();
		p_Renderer = gameObject->GetComponent<SpriteRenderer>();
		p_Transform = gameObject->GetTransform();

		/* Play the Current Animation. */
		if(p_AnimationCurrent)
			p_AnimationCurrent->Play();
	}

	void Animator::OnUpdate()
	{
		/* If the Engine State isn't in Editor. */
		#ifndef KROSS_EDITOR

		/* If the Animation is Currently Playing. */
		if (p_AnimationCurrent->IsPlaying())
		{
			/* Update the Animation. */
			p_AnimationCurrent->OnUpdate();

			/* Grab the Current Keyframe. */
			Keyframe* currentKeyframe = p_AnimationCurrent->GetCurrentKeyframe();

			/* If the object doesn't contain a Rigidbody or isn't static. */
			if (!p_Rigidbody && !c_Object->IsStatic())
			{
				/* If the Position Data has been set. */
				if (currentKeyframe->HasPositionData())
					p_Transform->m_Position = currentKeyframe->GetPosition();

				/* If the Rotation Data has been set. */
				if (currentKeyframe->HasRotationData())
					p_Transform->m_Rotation = currentKeyframe->GetRotation();

				/* If the Scale Data has been set. */
				if (currentKeyframe->HasScaleData())
					p_Transform->m_Scale = currentKeyframe->GetScale();
			}

			/* If the Sprite Data has been set. */
			if (currentKeyframe->HasSpriteData())
				if (p_Renderer) /* If we have a Renderer, set its Sprite. */
					p_Renderer->GetMaterial()->SetDiffuse(currentKeyframe->GetSprite());
		}
		#endif 

	}

	void Animator::Play()
	{
		/* If the Current Animation isn't playing. */
		if (!p_AnimationCurrent->IsPlaying())
			p_AnimationCurrent->Play(); /* Play it. */
	}

	void Animator::Pause()
	{
		/* If the Current Animation is playing. */
		if (p_AnimationCurrent->IsPlaying())
			p_AnimationCurrent->Pause(); /* Pause it. */
	}

	void Animator::Stop()
	{
		/* If the Current Animation is playing. */
		if (!p_AnimationCurrent->IsPlaying())
			p_AnimationCurrent->Stop(); /* Stop it. */
	}

	void Animator::AttachAnimation(Animation* animation)
	{
		/* If this is the first animation to be added. */
		if (m_Animations.size() == 0)
			p_AnimationCurrent = animation; /* Set it as the current. */

		/* Add it to the List. */
		m_Animations.push_back(animation);
	}

	void Animator::DetachAnimation(int index)
	{
		/* Early out if the Index is outside the bounds of the Array. */
		if (index < 0 || index >= m_Animations.size())
			return;

		/* Delete the Animation. */
		delete m_Animations[index];

		/* Remove the Animation from the List. */
		m_Animations[index] = nullptr;
		m_Animations.erase(m_Animations.begin() + index);
	}

	void Animator::DetachAnimation(const std::string& name)
	{
		/* Go through the Animations. */
		for (int i = 0; i < m_Animations.size(); i++)
		{
			/* If the Current Animation's Name is the one we are looking for. */
			if (m_Animations[i]->GetName() == name)
				DetachAnimation(i); /* Remove it. */
		}
	}

	void Animator::SetCurrentAnimation(int index)
	{
		/* Early out if the index is outside the bounds of the Array. */
		if (index < 0 || index >= m_Animations.size())
			return;

		/* Get the Animation we wish to change to. */
		Animation* animation = m_Animations[index];

		/* If the Animation is the same as the Current, early out. */
		if (p_AnimationCurrent == animation)
			return;

		// TODO: Dynamic stuff...

		/* Stop the Current Animation. */
		p_AnimationCurrent->Stop();

		/* Set and Play the other one. */
		p_AnimationCurrent = animation;
		p_AnimationCurrent->Play();
	}

	void Animator::SetCurrentAnimation(const std::string& name)
	{
		/* Go through the Animations List. */
		for (int i = 0; i < m_Animations.size(); i++)
		{
			/* If the Animation is the one we are looking for. */
			if (m_Animations[i]->GetName() == name)
				SetCurrentAnimation(i); /* Set the Animation. */
		}
	}
}