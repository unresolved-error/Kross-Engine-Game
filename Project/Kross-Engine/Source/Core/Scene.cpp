/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Jake Warren.
 */

#include "Scene.h"

#include "Component/Camera.h"
#include "Manager/ShaderManager.h"
#include "Manager/SceneManager.h"
#include "Manager/Time.h"

#include "Application.h"

namespace Kross
{
    Scene::~Scene()
    {
        /* Clean up Dynamic Objects. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            Object::OnDestroy(m_Objects[i]);
            m_Objects[i] = nullptr;
        }

        /* Clean up Static Objects. */
        for (int i = 0; i < m_StaticObjects.size(); i++)
        {
            Object::OnDestroy(m_StaticObjects[i]);
            m_StaticObjects[i] = nullptr;
        }

        /* Clear the Render Queue. */
        m_RenderList.clear();

        for (int i = 0; i < m_BatchRenderers.size(); i++)
        {
            BatchRenderer::OnDestroy(m_BatchRenderers[i]);
            m_BatchRenderers[i] = nullptr;
        }

        m_BatchRenderers.clear();

        delete p_Physics;
        delete p_WorldFilter;
        delete p_DebugRenderer;
        p_DebugShader = nullptr;
    }

    void Scene::OnStart()
    {
        for (int i = 0; i < m_BatchRenderers.size(); i++)
            m_BatchRenderers[i]->OnStart();

        /* Grab the Debug Shader. */
        p_DebugShader = ResourceManager::GetResource<Shader>("LineShader");
        p_DebugRenderer->Initialise();

        /* Start All Objects. */
        for (int i = 0; i < m_Objects.size(); i++)
            m_Objects[i]->OnStart();

        for (int i = 0; i < m_StaticObjects.size(); i++)
            m_StaticObjects[i]->OnStart();

        /* Scene has Started. */
        m_Started = true;
    }

    void Scene::OnUpdate()
    {
        /* Update all Dynamic Objects. */
        for (int i = 0; i < m_Objects.size(); i++)
            m_Objects[i]->OnUpdate();

        #ifdef KROSS_DEBUG
        for (int i = 0; i < m_RigidbodyComponents.size(); i++)
        {
            Rigidbody2D* body = (Rigidbody2D*)m_RigidbodyComponents[i];
            body->OnUpdateDrawInformation();
        }
        #endif
    }

    void Scene::OnPhysicsUpdate()
    {
        /* Update the physics step */
        p_Physics->GetPhysicsWorld()->Step(1.0f / (float)Application::GetWindow()->GetScreenRefreshRate(), 8, 3, 3);

        //p_Physics->GetPhysicsWorld()->Step(Time::GetDeltaTime(), 8, 3, 2); / Not recommended. /

        /* Update all Dynamic Objects. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            Rigidbody2D* body = m_Objects[i]->GetComponent<Rigidbody2D>();
            if (body)
            {
                if (body->GetRayCollisionBody())
                {
                    if (body->GetCollision() == CollisionState::Enter)
                        m_Objects[i]->OnCollisionEnter((Object*)body->GetRayCollisionBody()->GetUserData());

                    else if (body->GetCollision() == CollisionState::Stay)
                        m_Objects[i]->OnCollisionStay((Object*)body->GetRayCollisionBody()->GetUserData());

                    else if (body->GetCollision() == CollisionState::Exit)
                        m_Objects[i]->OnCollisionExit((Object*)body->GetRayCollisionBody()->GetUserData());
                }
            }
        }

    }

    void Scene::OnRender()
    {
        /* Get the Camera Component. if we have a Camera. */
        if (p_Camera)
        {
            Camera* camera = p_Camera->GetComponent<Camera>();
            ShaderManager::OnUpdateShaderVPMatrix(camera->GetView(), camera->GetProjection());
        }

        /* Render all Game Objects. */

        /* For removing the Objects from the Render Queue that are dynamic. */
        List<int> dynamicRenderQueueReferencePoints;

        /* Go through the Dynamic Object List. To place them in the Render Queue. */
        for (int i = 0; i < m_Objects.size(); i++)
        {
            /* If the Obejct is Enabled. Add it.*/
            if (m_Objects[i]->GetEnableStatus() == true && m_Objects[i]->GetRenderableStatus())
            {
                /* Keep Record of the index, so we know where in the list it is to remove it. */
                List<int> indexes = AttachObjectToRenderQueue(m_Objects[i]);

                for(int j = 0; j < indexes.size(); j++)
                    dynamicRenderQueueReferencePoints.push_back(indexes[j]);
            }
        }

        /* Render the Objects. */
        for (int l = 0; l < (int)Layer::Count; l++)
        {   
            for (int i = 0; i < m_RenderList[l].size(); i++)
                m_BatchRenderers[l]->AttachRenderer(m_RenderList[l][i]);

            m_BatchRenderers[l]->OnFinish();
        }

        #ifdef KROSS_DEBUG
        /* Draw Debug Information. */
        p_DebugShader->Attach();
        p_DebugRenderer->UpdateFrame();
        #endif

        /* Remove the Dynamic Objects from the Render Queue. */
        for (int i = 0; i < m_Objects.size(); i++)
            DetachObjectFromRenderQueue(m_Objects[i]->GetLayer(), m_Objects[i]);
    }

    void Scene::OnUpdateCameraAspectRatio(float aspectRatio)
    {
        /* If we have a Camera. */
        if(p_Camera)
            p_Camera->GetComponent<Camera>()->SetAspectRatio(aspectRatio);
    }

    List<int> Scene::AttachObjectToRenderQueue(Object* object)
    {
        /* List of all the indexes Recorded on this Object. */
        List<int> indexes = List<int>();

        /* If there is no renderer on the object. */
        if (!object->GetRenderableStatus())
            return indexes; /* Return Empty. */

        /* This is to return where abouts the Object sits in the Render Queue. */
        int index = 0;

        /* The Layer ID. */
        int layer = (int)object->GetLayer();

        /* Renderer Component List. */
        List<Renderer*> objectRenderList = object->GetRendererComponents();

        /* Go through the Object Render List. */
        for (int j = 0; j < objectRenderList.size(); j++)
        {
            /* If the Scenes's layer list is larger than zero. */
            if (m_RenderList[layer].size() > 0)
            {
                /* Run through the Layer List. */
                for (int i = 0; i < m_RenderList[layer].size(); i++)
                {
                    /* Check if the Depth of the object is larger than the one currently being checked in the list. */
                    if (objectRenderList[j]->GetDepth() > m_RenderList[layer][i]->GetDepth())
                        index++; /* Keep going down the list. */

                    /* We have found a spot in the Render Queue. */
                    else
                        break; /* Stop the Search. */
                }

                /* Add the Object to the Render Queue. */
                m_RenderList[layer].emplace(m_RenderList[layer].begin() + index, objectRenderList[j]);

                /* Add the Indexes as well. */
                indexes.push_back(index);

                /* Reset Index. */
                index = 0;
            }

            /* If not... */
            else
            {
                /* Attach as the First one. */
                m_RenderList[layer].push_back(objectRenderList[j]);

                /* Add the Indexes as well. */
                indexes.push_back(index);

                /* Reset Index. */
                index = 0;
            }
        }

        /* Return the Index. */
        return indexes;
    }

    void Scene::SetCamera(Object* object)
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

        return;
    }

    void Scene::DetachObjectFromRenderQueue(Layer layer, Object* object)
    {
        /* Early out if there is no renderer on the object. */
        if (!object->GetRenderableStatus())
            return;

        List<Renderer*> objectRenderList = object->GetRendererComponents();

        for (int j = 0; j < objectRenderList.size(); j++)
        {
            /* Go through Layer Objects. */
            for (int i = 0; i < m_RenderList[(int)layer].size(); i++)
            {
                /* If this is the Component we are looking for. */
                if (m_RenderList[(int)layer][i] == objectRenderList[j])
                    DetachObjectFromRenderQueue(layer, i); /* Remove it. */
            }
        }
    }

    void Scene::DetachObjectFromRenderQueue(Layer layer, int index)
    {
        /* Remove the Object from the List. */
        m_RenderList[(int)layer].erase(m_RenderList[(int)layer].begin() + index);
    }

    Scene* Scene::OnCreate(const std::string& name)
    {
        /* Create the Scene. */
        Scene* scene = KROSS_NEW Scene(name);

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
        /* Start the object inside of the Scene. */
        if (m_Started)
            object->OnStart();

        /* Checks if the Object has a Camera. */
        SetCamera(object);

        /* Check if the object is type RigidBody2D */
        Rigidbody2D* body = object->GetComponent<Rigidbody2D>();

        /* If the object is a RigidBody the physics scene is set */
        if (body)
        {
            body->SetPhysicsScene(p_Physics);
            body->AttachLineRenderer(p_DebugRenderer);
            m_RigidbodyComponents.push_back(body);
        }

        /* Check if the object is type Particleemitter */
        ParticleEmitter* emitter = object->GetComponent<ParticleEmitter>();

        /* If the object is a ParticleEmitter the physics scene is set */
        if (emitter)
            emitter->SetPhysicsScene(p_Physics);

        /* If the Object is Static. */
        if (object->GetStaticStatus() == true)
        {
            /* Attach the Object to the Static list and place it in the render Queue. */
            AttachObjectToRenderQueue(object);
            m_StaticObjects.push_back(object);
        }

        /* If it's not. */
        else
            m_Objects.push_back(object); /* Attach the Object to the Dynamic List. */
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