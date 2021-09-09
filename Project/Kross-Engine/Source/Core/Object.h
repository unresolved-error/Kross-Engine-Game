/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "Core.h"

#include "Debug.h"
#include "Layer.h"

#include "Physics/PhysicsScene.h"
#include "Renderer/LineRenderer.h"

namespace Kross
{
	/* Forward declare the Component and Transform Class. */

	class KROSS_API Component;
	class KROSS_API Renderer;

	class KROSS_API Transform2D;
	class KROSS_API Rigidbody2D;
	class KROSS_API Collider;

	class KROSS_API ParticleEmitter;
	class KROSS_API ParticleProperties;

	class KROSS_API RopeAvatar;

	class KROSS_API Object
	{
	private:
		Object();
		Object(const std::string& name);
		~Object();

		std::string m_Name;
		bool m_Static, m_Enable, m_Prefab, m_Started, m_Remove;

		std::vector<Component*> m_Components;
		std::vector<Renderer*> m_RenderComponents;

		PhysicsScene* m_Physics;
		LineRenderer* m_DebugRenderer;

		Layer m_Layer;

		// Used for displaying its children and storing them.
		std::vector<Object*> m_Children;

		Object* m_ParentObject;

	protected:
		friend class Scene;
		friend class ObjectEditor;
		friend class Component;

		friend class FileSystem;
		template<typename Type> friend class Serialiser;

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

		// Sets the Physics Scene.
		void SetPhysicsScene(PhysicsScene* physics) { m_Physics = physics; };

		// Sets the Line Renderer.
		void SetLineRenderer(LineRenderer* renderer) { m_DebugRenderer = renderer; };

		// Adds a Child Object.
		void AttachChildObject(Object* object);

		// Removes a Child Object. (BY NAME)
		void DetachChildObject(const std::string& name);

		// Removes a Child Object. (BY INDEX)
		void DetachChildObject(int index);

		// Removes a Child Object. (BY OBJECT)
		void DetachChildObject(Object* object);

		// Sets the Object Parent.
		void SetParentObject(Object* object) { m_ParentObject = object; };

		// Checks if the Object has a Render Component.
		const bool GetRenderableStatus() const { return (m_RenderComponents.size() > 0); };

		// Should Remove Object.
		const bool ShouldBeRemoved() const { return m_Remove; };

		// Gets all the Renderer Components on the Object.
		std::vector<Renderer*> GetRendererComponents() const { return m_RenderComponents; };

	public:
		Transform2D* m_Transform;

		const void DrawCross(Vector2 position) { m_DebugRenderer->DrawCross(position, 4.0f); };
		
		LineRenderer* GetDebugRenderer() const { return m_DebugRenderer; };

		// Creates a Blank Object.
		static Object* OnCreate(const std::string& name = "GameObject");

		// Destroys a specified object.
		static void OnDestroy(Object* object);

		// Gets the Object Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Object Layer.
		const Layer GetLayer() const { return m_Layer; };

		// Gets the Object Static Status.
		const bool IsStatic() const { return m_Static; };

		// Gets if the Object is a Prefab.
		const bool IsPrefab() const { return m_Prefab; };

		// Gets the Object Enable Status.
		const bool Enabled() const { return m_Enable; };

		// Gets the Object Parent.
		Object* GetParentObject() const { return m_ParentObject; };

		// Gets all of the Object's Children.
		const std::vector<Object*> GetChildObjects() const { return m_Children; };

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

		// Sets if the Object is Static.
		void SetStatic(bool value) { m_Static = value; };

		// Sets if the Object is Enabled.
		void SetEnable(bool value) { m_Enable = value; };

		// Sets if the Object is a Prefab. (DO NOT CALL, SERIALISER USE ONLY)
		void SetPrefab(bool value) { m_Prefab = value; };

		// Adds a Component to the Object.
		template<typename Type>
		Type* AttachComponent()
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Checks if the Type Specified is a RigidBody. */
			if (typeid(Type) == typeid(Rigidbody2D))
			{
				/* If we don't have a Collider. */
				if (!GetComponent<Collider>())
				{
					AttachComponent<Collider>(); /* Attach it. */
				}
			}

			/* Checks if the Type Specified is a RigidBody. */
			else if (typeid(Type) == typeid(ParticleEmitter))
			{
				/* If we don't have a Collider. */
				if (!GetComponent<ParticleProperties>())
				{
					AttachComponent<ParticleProperties>(); /* Attach it. */
				}
			}

			

			/* Set up of the new Component. */
			Component* component = KROSS_NEW Type();
			component->m_GameObject = this;

			if (typeid(Type) == typeid(Rigidbody2D))
			{
				((Rigidbody2D*)component)->SetPhysicsScene(m_Physics);
				((Rigidbody2D*)component)->p_DebugRenderer = m_DebugRenderer;
			}
			else if (typeid(Type) == typeid(ParticleEmitter))
			{
				((ParticleEmitter*)component)->SetPhysicsScene(m_Physics);
			}

			/* Checks if the Type Specified is a RigidBody. */
			else if (typeid(Type) == typeid(RopeAvatar))
			{
				((RopeAvatar*)component)->SetPhysicsScene(m_Physics);
				((RopeAvatar*)component)->SetDebugRenderer(m_DebugRenderer);
			}

			/* Then Check if the Component is a Renderer. */
			if (std::is_convertible<Type*, Renderer*>::value)
			{
				m_RenderComponents.push_back((Renderer*)component);
			}
			/* Add it to the list. */
			m_Components.push_back(component);

			if (m_Started)
			{
				component->OnStart();
			}

			/* Return the Component Type. */
			return (Type*)component;
		}

		// Removes a Component from the Object.
		template<typename Type>
		void DetachComponent(int index = 0)
		{
			/* Check if the type passed through is a Child of Component. */
			static_assert(std::is_convertible<Type*, Component*>::value, "Type must be of Component!");

			/* Search Index to match the Current Index. */
			int searchedIndex = 0;

			/* Go through the Components. */
			for (int i = 0; i < m_Components.size(); i++)
			{
				/* Make a local variable for the currently looked at Component. */
				Component* component = m_Components[i];

				/* If it is the Type of Component we are looking for. */
				if (typeid(*component) == typeid(Type))
				{
					/* If we are at the Search index. */
					if (searchedIndex == index)
					{
						/* Then Check if the Component is a Renderer. */
						if (std::is_convertible<Type*, Renderer*>::value)
						{
							/* Go through the Renderer Components. */
							for (int r = 0; r < m_RenderComponents.size(); r++)
							{
								Renderer* renderComponent = (Renderer*)component;
								/* Check if that Component is the One we are after. */
								if (renderComponent == m_RenderComponents[r])
								{
									/* Erase it from the List. */
									m_RenderComponents[r] = nullptr;
									m_RenderComponents.erase(m_RenderComponents.begin() + r);
									break;
								}
							}
						}

						/* Delete the Component. */
						delete m_Components[i];
						m_Components[i] = nullptr;

						/* Erase the Null Pointer from the list. */
						m_Components.erase(m_Components.begin() + i);
						return;
					}
					/* If it isn't. */
					else
					{
						searchedIndex++; /* Keep Searching. */
					}
				}
			}

			/* If we get here. Something Wasn't found. */
			std::string componentName = "Name";//typeid(Type).name();
			Debug::LogWarningLine("Component Type: " + componentName + "! Couldn't be deleted, as no Instance was found!");
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

#include "Component/Component.h"