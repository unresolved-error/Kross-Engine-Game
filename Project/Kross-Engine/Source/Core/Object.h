/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "Core.h"

#include "Layer.h"
#include "Component/Component.h"

namespace Kross
{
	/* Forward declare the Component and Transform Class. */

	class KROSS_API Component;
	class KROSS_API Renderer;

	class KROSS_API Transform2D;

	class KROSS_API Object
	{
	private:
		Object();
		Object(const std::string& name);
		~Object();

		std::string m_Name;
		bool m_Static, m_Enable;

		List<Component*> m_Components;
		List<Renderer*> m_RenderComponents;

		Transform2D* p_Transform;

		Layer m_Layer;

		// Used for displaying its children and storing them.
		List<Object*> m_Children;

		Object* p_ParentObject;

	protected:
		friend class Scene;
		friend class ObjectEditor;

		// Object Start Method.
		void OnStart();

		// Object Update Method.
		void OnUpdate();

		// Object Collision Enter Method.
		void OnCollisionEnter(Object* other);

		// Object Collision Stay Method.
		void OnCollisionStay(Object* other);

		// Object Collision Exit Method.
		void OnCollisionExit(Object* other);

		// Object Render Method.
		//void OnRender();

		// Adds a Child Object.
		void AttachChildObject(Object* object);

		// Removes a Child Object. (BY NAME)
		void DetachChildObject(const std::string& name);

		// Removes a Child Object. (BY INDEX)
		void DetachChildObject(int index);

		// Removes a Child Object. (BY OBJECT)
		void DetachChildObject(Object* object);

		// Sets the Object Parent.
		void SetParentObject(Object* object) { p_ParentObject = object; };

		// Checks if the Object has a Render Component.
		const bool GetRenderableStatus() const { return (m_RenderComponents.size() > 0); };

		// Gets all the Renderer Components on the Object.
		List<Renderer*> GetRendererComponents() const { return m_RenderComponents; };

	public:
		// Creates a Blank Object.
		static Object* OnCreate(const std::string& name = "GameObject");

		// Destroys a specified object.
		static void OnDestroy(Object* object);

		// Gets the Object Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Object Layer.
		const Layer GetLayer() const { return m_Layer; };

		// Gets the Object Static Status.
		const bool GetStaticStatus() const { return m_Static; };

		// Gets the Object Enable Status.
		const bool GetEnableStatus() const { return m_Enable; };

		// Gets the Object Parent.
		Object* GetParentObject() const { return p_ParentObject; };

		// Gets the Object Transform.
		Transform2D* GetTransform() const { return p_Transform; };

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

		// Sets the Object Layer.
		void SetLayer(Layer layer) { m_Layer = layer; };

		// Sets the Object Static Status.
		void SetStaticStatus(bool value) { m_Static = value; };

		// Sets the Object Enable Status.
		void SetEnableStatus(bool value) { m_Enable = value; };

		// Adds a Component to the Object.
		template<typename Type>
		Type* AttachComponent()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Set up of the new Component. */
			Component* component = KROSS_NEW Type();
			component->SetLinkObject(this);

			/* Then Check if the Component is a Renderer. */
			if (std::is_convertible<Type*, Renderer*>::value)
				m_RenderComponents.push_back((Renderer*)component);

			/* Add it to the list. */
			m_Components.push_back(component);

			/* Return the Component Type. */
			return (Type*)component;
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