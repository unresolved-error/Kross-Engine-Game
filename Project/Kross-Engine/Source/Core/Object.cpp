/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Object.h"

#include "Manager/SceneManager.h"

namespace Kross
{
	Object::Object()
		: m_Name("GameObject"), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), p_Transform(nullptr), m_Children(List<Object*>()), p_ParentObject(nullptr)
	{
		/* First Component is the Transform Component. */
		AttachComponent<Transform2D>();
		p_Transform = GetComponent<Transform2D>();
	}

	Object::Object(const std::string& name)
		: m_Name(name), m_Static(false), m_Enable(true), m_Components(List<Component*>()), p_StartComponent(nullptr), p_Transform(nullptr), m_Children(List<Object*>()), p_ParentObject(nullptr)
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

	Renderer* Object::GetRendererComponent()
	{
		/* Trial the Sprite Renderer First. */
		Renderer* renderer = GetComponent<SpriteRenderer>();

		/* If successfull return it. */
		if (renderer)
			return renderer;

		/* Trial the Text Renderer Next. */
		renderer = GetComponent<TextRenderer>();

		/* If successfull return it. */
		if (renderer)
			return renderer;

		/* If all else fails, return nothing. */
		return nullptr;
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
	}

	void Object::OnUpdate()
	{
		if (!m_Static && m_Enable)
		{
			/* Update Components. */
			p_StartComponent->OnUpdate();
		}

		return;
	}

	void Object::OnCollisionEnter()
	{
		if (!m_Static && m_Enable)
		{
			/* Enter Components Collision. */
			p_StartComponent->OnCollisionEnter();
		}

		return;
	}

	void Object::OnCollisionStay()
	{
		if (!m_Static && m_Enable)
		{
			/* Stay Components Collision. */
			p_StartComponent->OnCollisionStay();
		}

		return;
	}

	void Object::OnCollisionExit()
	{
		if (!m_Static && m_Enable)
		{
			/* Exit Components Collision. */
			p_StartComponent->OnCollisionExit();
		}

		return;
	}

	void Object::OnRender()
	{
		/* Variables for Camera View Checking. */
		Object* camera = SceneManager::GetCurrentScene()->GetCamera();
		Camera* cameraComponent = camera->GetComponent<Camera>();

		float cameraSize = (cameraComponent->GetSize() / 2.0f) + 1.0f;

		Vector2 cameraPosition = camera->GetTransform()->m_Position;
		Vector2 position = GetTransform()->m_Position;

		/* If the Object is outside of camera View. Don't Render Anything. */
		if (cameraPosition.x + cameraSize < position.x || cameraPosition.x - cameraSize > position.x)
			return;

		else if (cameraPosition.y + cameraSize < position.y || cameraPosition.y - cameraSize > position.y)
			return;

		if (m_Enable)
		{
			/* Render Components. */
			p_StartComponent->OnRender();
		}

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