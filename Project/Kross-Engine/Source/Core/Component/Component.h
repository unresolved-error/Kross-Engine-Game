/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
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

		// Gets the Object that the Component is linked to.
		Object* GetObject() const { return p_Object; };

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
		virtual void OnStart() = 0;

		// Component Update Method.
		virtual void OnUpdate() = 0;

		// Component Collision Enter Method.
		virtual void OnCollisionEnter() = 0;

		// Component Collision Stay Method.
		virtual void OnCollisionStay() = 0;

		// Component Collision Exit Method.
		virtual void OnCollisionExit() = 0;

		// Component Render Method.
		virtual void OnRender() = 0;

	};
}

#include "Transform2D.h"
#include "Script.h"
#include "Camera.h"
#include "SpriteRenderer.h"