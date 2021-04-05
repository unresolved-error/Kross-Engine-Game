/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Component/Component.h"

namespace Kross
{
	// Used for Rendering Objects. (FIRST TO LAST. NOTE! THESE ARE ADDED ENGINE SIDE!) 
	enum class Layer
	{
		/* Layers. */

		Default, 
		Player,
		Environment,
		Light,

		/* Layer Count. */

		Count,
	};

	/* Forward declare the Component Class. */

	class KROSS_API Component;

	class KROSS_API Object
	{
	private:
		std::string m_Name;
		bool m_Static, m_Enable;

		List<Component*> m_Components;

		Component* p_StartComponent;

		// Used for displaying its children and storing them.
		List<Object*> m_Children;

		Object* p_NextObject;
		Object* p_NextRenderObject;

		Object* p_ParentObject;

	protected:
		friend class Scene;

		// Object Start Method.
		void OnStart();

		// Object Update Method.
		void OnUpdate();

		// Object Collision Enter Method.
		void OnCollisionEnter();

		// Object Collision Stay Method.
		void OnCollisionStay();

		// Object Collision Exit Method.
		void OnCollisionExit();

		// Object Render Method.
		void OnRender();

		// Object Shutdown Method.
		void OnShutdown();

		// Adds a Child Object.
		void AttachChildObject(Object* object);

		// Removes a Child Object. (BY NAME)
		void DetachChildObject(const std::string& name);

		// Removes a Child Object. (BY INDEX)
		void DetachChildObject(int index);

		// Removes a Child Object. (BY OBJECT)
		void DetachChildObject(Object* object);

		// Gets the Next Object in Scene List.
		Object* GetNextObject() const { return p_NextObject; };

		// Gets the Next Object in the Render Queue.
		Object* GetNextRenderObject() const { return p_NextRenderObject; };

		// Sets the Next Object.
		void SetNextObject(Object* object) { p_NextObject = object; };

		// Sets the Next Object in the Render Queue.
		void SetNextRenderObject(Object* object) { p_NextRenderObject = object; };

		// Sets the Object Parent.
		void SetParentObject(Object* object) { p_ParentObject = object; };

	public:
		Object()
			: m_Name("GameObject"), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), m_Children(List<Object*>()), p_NextObject(nullptr), p_NextRenderObject(nullptr), p_ParentObject(nullptr)
		{};
		Object(const std::string& name)
			: m_Name(name), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), m_Children(List<Object*>()), p_NextObject(nullptr), p_NextRenderObject(nullptr), p_ParentObject(nullptr)
		{};
		~Object();

		// Gets the Object Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Object Static Status.
		const bool GetStaticStatus() const { return m_Static; };

		// Gets the Object Enable Status.
		const bool GetEnableStatus() const { return m_Enable; };

		// Gets the Object Parent.
		Object* GetParentObject() const { return p_ParentObject; };

		// Gets all of the Object's Children.
		const List<Object*> GetChildObjects() const { return m_Children; };

		// Gets a Child Object. (BY NAME)
		Object* GetChildObject(const std::string& name);

		// Gets a Child Object. (BY INDEX)
		Object* GetChildObject(int index);

		// Gets a Child Object. (BY OBJECT)
		Object* GetChildObject(Object* object);

		// Sets the Object Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Sets the Object Static Status.
		void SetStaticStatus(bool value) { m_Static = value; };

		// Sets the Object Enable Status.
		void SetEnableStatus(bool value) { m_Enable = value; };

		// Adds a Component to the Object.
		template<typename Type>
		void AttachComponent()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Set up of the new Component. */
			Component* component = new Type();
			component->SetNextComponent(p_StartComponent);
			component->AttachObject(this);

			/* Set it as the Start Component. */
			p_StartComponent = component;

			/* Add it to the list. */
			m_Components.push_back(component);
		}

		// Gets the first Component that is of the Type specified.
		template<typename Type>
		Type* GetComponent()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Go through the Components list. */
			for (int i = 0; i < m_Components.size(); i++)
			{
				/* Make a local variable for the currently looked at Component. */
				Component* component = m_Components[i];

				/* Check if it is the Component Type we are looking for, then return it. */
				if (typeid(Type) == typeid(*component))
					return (Type*)component;
			}

			/* If we get here, it doesn't exist within the Object. */
			return nullptr;
		}

		// Gets all of the Components that are of the Type specified.
		template<typename Type>
		List<Type*> GetComponents()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Variables. */
			List<Type*> components = List<Type*>();

			/* Go through the Components list. */
			for (int i = 0; i < m_Components.size(); i++)
			{
				/* Make a local variable for the currently looked at Component. */
				Component* component = m_Components[i];

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