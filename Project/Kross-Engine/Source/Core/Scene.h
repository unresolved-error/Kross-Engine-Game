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
#include "Renderer/Batch/BatchRenderer.h"
#include "Renderer/LineRenderer.h"

namespace Kross
{
	class KROSS_API Scene
	{
	private:
		Scene(const std::string& name) : 
			m_Name					(name), 
			m_Started				(false), 
			m_Objects				(std::vector<Object*>()), 
			m_StaticObjects			(std::vector<Object*>()),
			m_ActualObjects			(std::vector<Object*>()),
			m_DebugRenderer			(KROSS_NEW LineRenderer()),
			m_DebugShader			(nullptr),
			#ifdef KROSS_EDITOR
			m_EditorCamera			(nullptr),
			#endif
			m_Camera				(nullptr), 
			m_Physics				(KROSS_NEW PhysicsScene()), 
			m_WorldFilter			(KROSS_NEW ContactFilter())
		{
			/* Sets the physics world for Box2D */
			//World* world = KROSS_NEW World({ 0.0f, -9.8f });
			World* world = KROSS_NEW World({ 0.0f, 0.0f });
			world->SetContactFilter(m_WorldFilter);
			m_Physics->SetPhysicsWorld(world);

			/* Sets a default particle system */
			ParticleSystemDef particleSystemDef;
			ParticleSystem* particleSystem = world->CreateParticleSystem(&particleSystemDef);
			m_Physics->AddParticleSystem(particleSystem);

			/* Sets the particle contact filters */

			/* Add lists on every Layer for Rendering. */
			for (int i = 0; i < (int)Layer::Count; i++)
			{
				m_RenderList.push_back(std::vector<Renderer*>());
				m_BatchRenderers.push_back(BatchRenderer::OnCreate((Layer)i));
			}

			#ifdef KROSS_EDITOR
			m_EditorCamera = Object::OnCreate("EditorCamera");
			m_EditorCamera->AttachComponent<Camera>();

			m_Camera = m_EditorCamera;
			#endif

		};
		~Scene();

		std::string m_Name;

		bool m_Started;

		std::vector<Object*> m_Objects;
		std::vector<Object*> m_StaticObjects;

		// Editor Purposes only!
		std::vector<Object*> m_ActualObjects;

		// List of Layer Groups.
		std::vector<std::vector<Renderer*>> m_RenderList; /* | Layer | Object | */

		std::vector<BatchRenderer*> m_BatchRenderers;

		LineRenderer* m_DebugRenderer;
		Shader* m_DebugShader;

		Object* m_Camera;
		#ifdef KROSS_EDITOR
		Object* m_EditorCamera;
		#endif

		PhysicsScene* m_Physics;

		ContactFilter* m_WorldFilter;
		
	protected:
		friend class SceneManager;
		friend class Application;
		friend class SceneHierarchy;
		friend class FileSystem;

		// Starts the Objects.
		void OnStart();

		// Updates the Objects.
		void OnUpdate();

		// Physics Checks.
		void OnPhysicsUpdate();

		// Renders the Objects.
		void OnRender();

		// Removes all Object that have been tagged.
		void OnRemoveObjects();

		// Gets all of the Objects in the Scene.
		std::vector<Object*> GetObjects() const { return m_ActualObjects; };

		// Updates the Primary Camera Aspect Ratio.
		void OnUpdateCameraAspectRatio(float aspectRatio);

		// Places an object in the Render Queue.
		std::vector<int> AttachObjectToRenderQueue(Object* object);

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
		void AttachObject(Object* object, bool startOverride = false);

		// Removes a Object from the Scene. (BY NAME)
		void DetachObject(const std::string& name);

		// Removes a Object from the Scene. (BY OBJECT)
		void DetachObject(Object* object);

		// Removes a Object from the Scene. (BY INDEX)
		void DetachObject(int index);

		// Gets the total Number of Objects in the Scene.
		const int GetObjectCount() const { return m_Objects.size() + m_StaticObjects.size(); }

		// Find a Object from the given name.
		Object* FindObject(std::string name);

		// Gets the Main Camera of the Scene.
		Object* GetCamera() const { return m_Camera; };

		// Sets the Gravity of the Scene.
		void SetGravity(float gravity, Vector2 direction) { direction = glm::normalize(direction);  m_Physics->p_PhysicsWorld->SetGravity({ direction.x * gravity, direction.y * gravity }); };

		// Gets the Direction of the Gravity.
		Vector2 GetGravityDirection() const { return glm::normalize(Vector2((float)m_Physics->p_PhysicsWorld->GetGravity().x, (float)m_Physics->p_PhysicsWorld->GetGravity().y)); };

		// Gets the Gravity Scalar.
		float GetGravityScalar() const { return glm::length(Vector2((float)m_Physics->p_PhysicsWorld->GetGravity().x, (float)m_Physics->p_PhysicsWorld->GetGravity().y)); }
	};

	// Creates an Empty object and assigns a name to it.
	Object* OnCreateObject(const std::string& name);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position, float rotation);

	// Creates an Empty object.
	Object* OnCreateObject(const std::string& name, Vector2 position, float rotation, Vector2 scale);
	
	// Creates a clone of the Object passed in.
	Object* OnCreateObject(Object* object);
	
	// Destroys the Object passed in.
	void OnDestroyObject(Object* object);
}