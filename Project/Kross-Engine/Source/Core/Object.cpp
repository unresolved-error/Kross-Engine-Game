/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Object.h"

namespace Kross
{
	Object::Object()
		: m_Name("GameObject"), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), p_Transform(nullptr), m_Children(List<Object*>()), p_NextObject(nullptr), p_NextRenderObject(nullptr), p_ParentObject(nullptr)
	{
		/* First Component is the Transform Component. */
		AttachComponent<Transform2D>();
		p_Transform = GetComponent<Transform2D>();
	}

	Object::Object(const std::string& name)
		: m_Name(name), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), p_Transform(nullptr), m_Children(List<Object*>()), p_NextObject(nullptr), p_NextRenderObject(nullptr), p_ParentObject(nullptr)
	{
		/* First Component is the Transform Component. */
		AttachComponent<Transform2D>();
		p_Transform = GetComponent<Transform2D>();
	}

	Object::~Object()
	{
		/* Clean up the Components from the heap. */
		for (int i = 0; i < m_Components.size(); i++)
		{
			delete m_Components[i];
			m_Components[i] = nullptr;
		}
	}

	Object* Object::OnCreate(const std::string& name)
	{
		/* Create a new Object. */
		Object* object = new Object(name);

		/* Return the new Object. */
		return object;
	}

	void Object::OnDestroy(Object* object)
	{
		/* Safe programming, not really needed but good to have. */
		if (object)
			delete object;
	}

	void Object::OnStart()
	{
		/* Start up Components. */
		p_StartComponent->OnStart();

		/* Start the Next Object. */
		if (p_NextObject)
			p_NextObject->OnStart();

		return;
	}

	void Object::OnUpdate()
	{
		/* Update Components. */
		p_StartComponent->OnUpdate();

		/* Update the Next Object. */
		if (p_NextObject)
			p_NextObject->OnUpdate();

		return;
	}

	void Object::OnCollisionEnter()
	{
		/* Call Collision Enter on Components. */
		p_StartComponent->OnCollisionEnter();

		return;
	}

	void Object::OnCollisionStay()
	{
		/* Call Collision Stay on Components. */
		p_StartComponent->OnCollisionStay();

		return;
	}

	void Object::OnCollisionExit()
	{
		/* Call Collision Exit on Components. */
		p_StartComponent->OnCollisionExit();

		return;
	}

	void Object::OnRender()
	{
		/* Render Components. */
		p_StartComponent->OnRender();

		/* Render the Next Object. */
		if (p_NextObject)
			p_NextObject->OnRender();

		return;
	}

	void Object::AttachChildObject(Object* object)
	{
		/* If the Object is itself. */
		if (object == this)
			return;

		/* Early out if no Object. */
		if (!object)
			return;

		/* Check for duplicates. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children[i] == object)
				return;
		}

		/* If no duplicates. */
		m_Children.push_back(object);
	}

	void Object::DetachChildObject(const std::string& name)
	{
		/* Find the Object and remove it from being the child list. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children[i]->GetName() == name)
				DetachChildObject(i); /* If the child has been found, remove it from the list. */
		}
	}

	void Object::DetachChildObject(int index)
	{
		/* If the index is in the bounds of the list. */
		if (index >= 0 && index < m_Children.size())
			m_Children.erase(m_Children.begin() + index); /* remove the specified child. */
	}

	void Object::DetachChildObject(Object* object)
	{
		/* Find the Object and remove it from being the child list. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children[i] == object)
				DetachChildObject(i); /* If the child has been found, remove it from the list. */
		}
	}

	Object* Object::GetChildObject(const std::string& name)
	{
		/* Find the Object and return it. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children[i]->GetName() == name)
				return GetChildObject(i); /* If the child has been found, return it. */
		}

		/* If no Object could be found, return null. */
		return nullptr;
	}

	Object* Object::GetChildObject(int index)
	{
		/* If the index is in the bounds of the list. */
		if (index >= 0 && index < m_Children.size())
			return m_Children[index]; /* Return the Child. */

		/* If the index is out of bounds return null. */
		return nullptr;
	}

	Object* Object::GetChildObject(Object* object)
	{
		/* Find the Object and return it. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children[i] == object)
				return GetChildObject(i); /* If the child has been found, return it. */
		}

		/* If no Object could be found, return null. */
		return nullptr;
	}
}