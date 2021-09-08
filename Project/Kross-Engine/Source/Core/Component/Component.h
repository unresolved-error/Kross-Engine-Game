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

	protected:
		friend class Object;

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

	public:
		Component() :
			m_GameObject(nullptr)
		{};

		virtual ~Component() {};

		// The Object the Component is Attached to. (READ ONLY)
		Object* m_GameObject;

		// Gets the first Component that is of the Type specified.
		template<typename Type>
		Type* GetComponent()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Go through the Components list. */
			for (int i = 0; i < m_GameObject->m_Components.size(); i++)
			{
				/* Make a local variable for the currently looked at Component. */
				Component* component = m_GameObject->m_Components[i];

				/* Check if it is the Component Type we are looking for, then return it. */
				if (typeid(Type) == typeid(*component))
				{
					return (Type*)component;
				}
			}

			/* If we get here, it doesn't exist within the Object. */
			return nullptr;
		}

		// Gets all of the Components that are of the Type specified.
		template<typename Type>
		std::vector<Type*> GetComponents()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Variables. */
			std::vector<Type*> components = std::vector<Type*>();

			/* Go through the Components list. */
			for (int i = 0; i < m_GameObject->m_Components.size(); i++)
			{
				/* Make a local variable for the currently looked at Component. */
				Component* component = m_GameObject->m_Components[i];

				/* Check if it is the Component Type we are looking for, then add it. */
				if (typeid(Type) == typeid(*component))
				{
					Type* componentConverted = (Type*)component;
					components.push_back(componentConverted);
				}
			}

			/* Return the list. */
			return components;
		}
	};
}

#include "Transform2D.h"
#include "Script.h"
#include "Camera.h"
#include "PlayerController.h"
#include "Collider.h"
#include "ParticleProperties.h"
#include "Animator.h"
#include "AudioPlayer.h"
#include "ButtonProperties.h"

#include "Renderer.h"