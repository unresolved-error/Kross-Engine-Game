/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Jake Warren.
 */

#pragma once

#include "../Core.h"

#include "../Object.h"

namespace Kross
{
	/* Forward delcare the Object Class. */

	class KROSS_API Object;

	class KROSS_API Component
	{
	private:
		Object* p_Object;

	protected:
		friend class Object;

		// Sets the Object that the Component will be linked to.
		void SetLinkObject(Object* object) { p_Object = object; c_Object = object; };

	public:
		Component() :
			p_Object(nullptr), c_Object(nullptr)
		{};

		virtual ~Component() {};

		const Object* c_Object;

		// Component Start Method.
		virtual void OnStart() { return; };

		// Component Update Method.
		virtual void OnUpdate() { return; };

		// Component Collision Enter Method.
		virtual void OnCollisionEnter(Object* other) { return; };

		// Component Collision Stay Method.
		virtual void OnCollisionStay(Object* other) { return; };

		// Component Collision Exit Method.
		virtual void OnCollisionExit(Object* other) { return; };

		// Gets the Object that the Component is linked to.
		Object* GetLinkObject() const { return p_Object; };
	};
}

#include "Transform2D.h"
#include "Script.h"
#include "Camera.h" 
#include "Animator.h"
#include "AudioPlayer.h"

#include "Renderer.h"