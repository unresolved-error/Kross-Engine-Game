/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

#include "Object.h"

namespace Kross
{
	class KROSS_API Scene
	{
	private:
		Scene(const std::string& name)
			: m_Name(name), m_Objects(List<Object*>()), p_StartObject(nullptr), p_Camera(nullptr)
		{};
		~Scene();

		std::string m_Name;

		List<Object*> m_Objects;
		Object* p_StartObject;
		Object* p_Camera;
		
	protected:
		friend class SceneManager;

		// Starts the Objects.
		void OnStart();

		// Updates the Objects.
		void OnUpdate();

		// Physics Checks.
		void OnPhysicsUpdate() { return; };

		// Renders the Objects.
		void OnRender();

		// Updates the Primary Camera Aspect Ratio.
		void OnUpdateCameraAspectRatio(float aspectRatio);

	public:
		// Creates an Empty Scene.
		static Scene* OnCreate(const std::string& name);

		// Destroys the Scene specified.
		static void OnDestroy(Scene* scene);

		// Sets the Scene Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Gets the Scene Name.
		const std::string GetName() const { return m_Name; };

		// Adds a Object to the Scene.
		void AttachObject(Object* object);

		// Removes a Object from the Scene. (BY NAME)
		void DetachObject(const std::string& name);

		// Removes a Object from the Scene. (BY OBJECT)
		void DetachObject(Object* object);

		// Removes a Object from the Scene. (BY INDEX)
		void DetachObject(int index);

	};

	//// Creates a Object and attaches a name to it. (NOTHING YET)
	//Object* OnCreateObject(const std::string& name) { return nullptr; };
	//
	//// Creates a clone of the Object passed in. (NOTHING YET)
	//Object* OnCreateObject(Object* object) { return nullptr;  };
	//
	//// Destroys the Object passed in. (NOTHING YET)
	//void OnDestroyObject(Object* object) {};
}