/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Jake Warren.
 */

#include "Scene.h"

#include "Component/Camera.h"
#include "Manager/ShaderManager.h"
#include "Manager/Time.h"


namespace Kross
{
    Scene::~Scene()
    {
        /* Clean up the Objects from the heap. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            Object::OnDestroy(m_Objects[i]);
            m_Objects[i] = nullptr;
        }
    }

    void Scene::OnStart()
    {
        
        /* Start all Game Objects. */
        if (p_StartObject)
            p_StartObject->OnStart();
    }

    void Scene::OnUpdate()
    {
        /* Update all Game Objects. */
        if (p_StartObject)
            p_StartObject->OnUpdate();
    }

    void Scene::OnPhysicsUpdate()
    {
        p_Physics->GetPhysicsWorld()->Step(0.01f, 8, 3, 1);

        b2World* worldPointer = p_Physics->GetPhysicsWorld();
        //b2Body* bodyPointer = worldPointer->GetBodyList()->GetNext();

        //bodyPointer->ApplyForce({ 1,1 }, { 1,0 }, true);

        //b2World* world = p_Physics->GetPhysicsWorld();

    }

    void Scene::OnRender()
    {
        /* Get the Camera Component. if we have a Camera. */
        if (p_Camera)
        {
            Camera* camera = p_Camera->GetComponent<Camera>();
            ShaderManager::OnUpdateShaderVPMatrix(camera->GetView(), camera->GetProjection());
        }

        /* this needs to be looked at as well */
        /* Render all Game Objects. */
        if (p_StartObject)
            p_StartObject->OnRender();
    }

    void Scene::OnUpdateCameraAspectRatio(float aspectRatio)
    {
        /* If we have a Camera. */
        if(p_Camera)
            p_Camera->GetComponent<Camera>()->SetAspectRatio(aspectRatio);
    }

    Scene* Scene::OnCreate(const std::string& name)
    {
        /* Create the Scene. */
        Scene* scene = new Scene(name);

        /* Return the new Scene. */
        return scene;
    }

    void Scene::OnDestroy(Scene* scene)
    {
        /* Safe programming, not really needed but good to have. */
        if (scene)
            delete scene;
    }

    void Scene::AttachObject(Object* object)
    {
        /* Check if the Object is of type Camera. */
        Camera* camera = object->GetComponent<Camera>();

        /* if the Object is a Camera. */
        if (camera)
        {
            /* If we have no Camera, set it. */
            if (!p_Camera)
                p_Camera = object;
        }

        Rigidbody2D* body = object->GetComponent<Rigidbody2D>();

        if (body)
        {
            body->SetPhysicsScene(p_Physics);
        }

        /* Place the Object inside of the list and link it to the last Object. */
        if (m_Objects.size() > 0)
            m_Objects[m_Objects.size() - 1]->SetNextObject(object);

        else
            p_StartObject = object;

        m_Objects.push_back(object);
    }

    void Scene::DetachObject(const std::string& name)
    {
        /* Find the Object and remove it from the list. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            if (m_Objects[i]->GetName() == name)
                DetachObject(i); /* If the Object has been found, remove it from the list. */
        }
    }

    void Scene::DetachObject(Object* object)
    {
        /* Find the Object and remove it from the list. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            if (m_Objects[i] == object)
                DetachObject(i); /* If the Object has been found, remove it from the list. */
        }
    }

    void Scene::DetachObject(int index)
    {
       /* Needs to be looked at... */
    }
}