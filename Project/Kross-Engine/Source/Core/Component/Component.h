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
		Component* p_NextComponent;
		Object* p_Object;

	protected:
		friend class Object;

		// Gets the Next Component.
		Component* GetNextComponent() const { return p_NextComponent; };

		// Sets the Next Component.
		void SetNextComponent(Component* component) { p_NextComponent = component; };

		// Sets the Object that the Component will be linked to.
		void SetObject(Object* object) { p_Object = object; };

	public:
		Component()
			: p_NextComponent(nullptr), p_Object(nullptr)
		{};
		virtual ~Component() {};

		// Component Start Method.
		virtual void OnStart();

		// Component Update Method.
		virtual void OnUpdate();

		// Component Collision Enter Method.
		virtual void OnCollisionEnter();

		// Component Collision Stay Method.
		virtual void OnCollisionStay();

		// Component Collision Exit Method.
		virtual void OnCollisionExit();

		// Component Render Method.
		virtual void OnRender();

		// Gets the Object that the Component is linked to.
		Object* GetObject() const { return p_Object; };

	};
}

#include "Transform2D.h"
#include "Script.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Rigidbody2D.h"
#include "Collider2D.h"
#include "ParticleEmitter.h"