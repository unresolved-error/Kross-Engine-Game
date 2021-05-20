/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *		- Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

#include "Object.h"
#include "Physics/PhysicsScene.h"

namespace Kross
{
	class KROSS_API Scene
	{
	private:
		Scene(const std::string& name)
			: m_Name(name), m_Started(false), m_Objects(List<Object*>()), m_StaticObjects(List<Object*>()),
			p_Camera(nullptr), p_Physics(new PhysicsScene()), p_CollisionFilter(new CollisionFilter())
		{
			/* Sets the physics world for Box2D */
			World* world = new World({ 0.0f, -9.8f });
			p_Physics->SetPhysicsWorld(world);

			/* Sets a default particle system */
			ParticleSystemDef particleSystemDef;
			ParticleSystem* particleSystem = world->CreateParticleSystem(&particleSystemDef);
			p_Physics->SetParticleSystem(particleSystem);

			/* Sets the particle contact filters */


			/* Add lists on every Layer for Rendering. */
			for (int i = 0; i < (int)Layer::Count; i++)
				m_RenderList.push_back(List<Renderer*>());
		};
		~Scene();

		std::string m_Name;

		bool m_Started;

		List<Object*> m_Objects;
		List<Object*> m_StaticObjects;

		// List of Layer Groups.
		List<List<Renderer*>> m_RenderList; /* | Layer | Object | */

		Object* p_Camera;
		PhysicsScene* p_Physics;

		CollisionFilter* p_CollisionFilter;
		
	protected:
		friend class SceneManager;

		// Starts the Objects.
		void OnStart();

		// Updates the Objects.
		void OnUpdate();

		// Physics Checks.
		void OnPhysicsUpdate();

		// Renders the Objects.
		void OnRender();

		// Updates the Primary Camera Aspect Ratio.
		void OnUpdateCameraAspectRatio(float aspectRatio);

		// Places an object in the Render Queue.
		List<int> AttachObjectToRenderQueue(Object* object);

		// Checks if the Object is a Camera Object and sets the Camera.
		void SetCamera(Object* object);

		// Removes an Object from the Render Queue. (BY OBJECT)
		void DetachObjectFromRenderQueue(Layer layer, Object* object);

		// Removes an Object from the Render Queue. (BY INDEX)
		void DetachObjectFromRenderQueue(Layer layer, int index);

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

		// Gets the total Number of Objects in the Scene.
		const int GetObjectCount() const { return m_Objects.size(); }

		// Gets the Main Camera of the Scene.
		Object* GetCamera() const { return p_Camera; };

	};

	// Creates an Empty object and assigns a name to it.
	Object* OnCreateObject(const std::string& name);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position, float rotation);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position, float rotation, Vector2 scale);
	
	//// Creates a clone of the Object passed in.
	//Object* OnCreateObject(Object* object);
	//
	//// Destroys the Object passed in.
	//void OnDestroyObject(Object* object);
}