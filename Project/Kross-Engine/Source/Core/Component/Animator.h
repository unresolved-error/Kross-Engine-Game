/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Animation/Animation.h"
#include "Component.h"
#include "Renderer.h"

/* ------ NOTE: ------ */
/*
	Animator Rules:
	 - Cannot modify the Transform if the Object is 
	   Static or using Physics.

	 - Cannot Change Sprite if no Sprite Renderer
	   is found.
*/

namespace Kross
{
	class KROSS_API Animator : public Component
	{
	private:
		Animation* p_AnimationCurrent;
		List<Animation*> m_Animations;

		/* Keyframe Properties Components. */

		Rigidbody2D* p_Rigidbody;

		SpriteRenderer* p_Renderer;
		Transform2D* p_Transform;

		/* ------------------------------- */

	protected:
		// Animators Start Method.
		void OnStart() override;

		// Animators Update Method.
		void OnUpdate() override;

	public:
		Animator() :
			p_AnimationCurrent	(nullptr),
			m_Animations		(List<Animation*>()),
			p_Rigidbody			(nullptr),
			p_Renderer			(nullptr),
			p_Transform			(nullptr)
		{};
		~Animator();

		// Plays the Current Animation.
		void OnPlay();

		// Pauses the Current Animation.
		void OnPause();

		// Stops the Current Animation.
		void OnStop();

		// Adds an Animation to the Animator.
		void AttachAnimation(Animation* animation);

		// Removes an Animation from the Animator. (BY INDEX)
		void DetachAnimation(int index);

		// Removes the Animation from the Animator. (BY NAME)
		void DetachAnimation(const std::string& name);

		// Gets the Current Animation.
		Animation* GetCurrentAnimation() const { return p_AnimationCurrent; };

		// Sets the Current Animation. (BY INDEX)
		void SetCurrentAnimation(int index);

		// Sets the Current Animation. (BY NAME)
		void SetCurrentAnimation(const std::string& name);

	};
}