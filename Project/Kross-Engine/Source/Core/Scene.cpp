/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Scene.h"

#include "Component/Camera.h"
#include "Manager/ShaderManager.h"
#include "Manager/SceneManager.h"

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
    }

    void Scene::OnStart()
    {
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
            if (m_Objects[i]->GetEnableStatus() == true)
            {
                /* Keep Record of the index, so we know where in the list it is to remove it. */
                int index = AttachObjectToRenderQueue(m_Objects[i]);
                dynamicRenderQueueReferencePoints.push_back(index);
            }
        }

        /* Render the Objects. */
        for (int l = 0; l < (int)Layer::Count; l++)
        {
            /* Go through each Layer and render the Objects. */
            for (int i = 0; i < m_RenderList[l].size(); i++)
                m_RenderList[l][i]->OnRender();
        }

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

    int Scene::AttachObjectToRenderQueue(Object* object)
    {
        /* Early out if the Object doesn't have a renderer of any sort. */
        Renderer* renderer = object->GetRendererComponent();

        /* If there is no renderer on the object. */
        if (!renderer)
            return -1; /* Return null. */

        /* This is to return where abouts the Object sits in the Render Queue. */
        int index = 0;

        /* The Layer ID. */
        int layer = (int)object->GetLayer();

        /* If the Object's layer list is larger than zero. */
        if (m_RenderList[layer].size() > 0)
        {
            /* Run through the Layer List. */
            for (int i = 0; i < m_RenderList[layer].size(); i++)
            {
                /* Grab the Render Component of the Object. */
                Renderer* rendererInList = m_RenderList[layer][i]->GetRendererComponent();

                /* Check if the Depth of the object is larger than the one currently being checked in the list. */
                if (renderer->GetDepth() > rendererInList->GetDepth())
                    index++; /* Keep going down the list. */

                /* We have found a spot in the Render Queue. */
                else
                    break; /* Stop the Search. */
            }

            /* Add the Object to the Render Queue. */
            m_RenderList[layer].emplace(m_RenderList[layer].begin() + index, object);
        }

        /* If not... */
        else
        {
            /* Attach as the First one. */
            m_RenderList[layer].push_back(object);
        }

        /* Return the Index. */
        return index;
    }

    void Scene::DetachObjectFromRenderQueue(Layer layer, Object* object)
    {
        /* Early out if the Object doesn't have a renderer of any sort. */
        Renderer* renderer = object->GetRendererComponent();

        /* Early out if there is no renderer on the object. */
        if (!renderer)
            return;

        /* Go through Layer Objects. */
        for (int i = 0; i < m_RenderList[(int)layer].size(); i++)
        {
            /* If this is the Object we are looking for. */
            if (m_RenderList[(int)layer][i] == object)
                DetachObjectFromRenderQueue(layer, i); /* Remove it. */
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
        /* Start the object inside of the Scene. */
        if (m_Started)
            object->OnStart();

        /* Check if the Object is of type Camera. */
        Camera* camera = object->GetComponent<Camera>();

        /* if the Object is a Camera. */
        if (camera)
        {
            /* If we have no Camera, set it. */
            if (!p_Camera)
                p_Camera = object;
        }

        /* If the Object is Static. */
        if (object->GetStaticStatus() == true)
        {
            /* Attach the Object to the Static list and place it in the render Queue. */
            AttachObjectToRenderQueue(object);
            m_StaticObjects.push_back(object);
        }

        else
        {
            /* Attach the Object to the Dynamic list. */
            m_Objects.push_back(object);
        }
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