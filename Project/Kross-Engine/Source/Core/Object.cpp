/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Object.h"

#include "Manager/SceneManager.h"

namespace Kross
{
	Object::Object() :
		m_Name			("GameObject"),
		m_Components	(List<Component*>()),
		m_Children		(List<Object*>()),
		p_Transform		(nullptr), 
		m_Layer			(Layer::Default),
		p_ParentObject	(nullptr),
		m_Static		(false),
		m_Enable		(true),
		m_Prefab		(false),
		m_Started		(false)
	{
		/* First Component is the Transform Component. */
		AttachComponent<Transform2D>();
		p_Transform = GetComponent<Transform2D>();
	}

	Object::Object(const std::string& name) : 
		m_Name			(name), 
		m_Static		(false), 
		m_Enable		(true), 
		m_Components	(List<Component*>()), 
		p_Transform		(nullptr), 
		m_Layer			(Layer::Default),
		m_Children		(List<Object*>()), 
		p_ParentObject	(nullptr),
		m_Started		(false)
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

		/* Clean up the Children from the heap. */
		for (int i = 0; i < m_Children.size(); i++)
		{
			delete m_Children[i];
			m_Children[i] = nullptr;
		}

		delete p_ParentObject;
	}

	Object* Object::OnCreate(const std::string& name)
	{
		/* Create a new Object. */
		Object* object = KROSS_ALLOCATION_REPORT(Object(name));

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
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->OnStart();

		m_Started = true;
	}

	void Object::OnUpdate()
	{
		if (!m_Static && m_Enable)
		{
			/* Update Components. */
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->OnUpdate();
		}

		return;
	}

	void Object::OnCollisionEnter(Object* other)
	{
		if (!m_Static && m_Enable)
		{
			/* Enter Components Collision. */
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->OnCollisionEnter(other);
		}

		return;
	}

	void Object::OnCollisionStay(Object* other)
	{
		if (!m_Static && m_Enable)
		{
			/* Stay Components Collision. */
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->OnCollisionStay(other);
		}

		return;
	}

	void Object::OnCollisionExit(Object* other)
	{
		if (!m_Static && m_Enable)
		{
			/* Exit Components Collision. */
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->OnCollisionExit(other);
		}

		return;
	}

	//void Object::OnRender()
	//{
	//	/* Variables for Camera View Checking. */
	//	Object* camera = SceneManager::GetCurrentScene()->GetCamera();
	//	Camera* cameraComponent = camera->GetComponent<Camera>();
	//
	//	float cameraSize = (cameraComponent->GetSize() / 2.0f) + 3.0f;
	//
	//	Vector2 cameraPosition = camera->GetTransform()->m_Position;
	//	Vector2 position = GetTransform()->m_Position;
	//
	//	/* If the Object is outside of camera View. Don't Render Anything. */
	//	if (cameraPosition.x + cameraSize < position.x || cameraPosition.x - cameraSize > position.x)
	//		return;
	//
	//	else if (cameraPosition.y + cameraSize < position.y || cameraPosition.y - cameraSize > position.y)
	//		return;
	//
	//	if (m_Enable)
	//	{
	//		/* Render Components. */
	//		for (int i = 0; i < m_RenderComponents.size(); i++)
	//			m_RenderComponents[i]->OnRender();
	//	}
	//
	//	return;
	//}

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