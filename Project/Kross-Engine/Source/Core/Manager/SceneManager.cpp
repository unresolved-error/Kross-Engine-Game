/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SceneManager.h"

namespace Kross
{
	SceneManager*		SceneManager::m_Instance =		nullptr;

	SceneManager::~SceneManager()
	{
		/* Destroy all the Scenes. */
		for (int i = 0; i < m_Instance->m_Scenes.size(); i++)
		{
			Scene::OnDestroy(m_Instance->m_Scenes[i]);
			m_Instance->m_Scenes[i] = nullptr;
		}

		/* Clean up Memory. */
		m_Instance->m_Scenes.clear();
		m_Instance->m_Scenes.~vector();
	}

	void SceneManager::OnCreate()
	{
		if (!m_Instance)
		{
			m_Instance = KROSS_NEW SceneManager();
		}
	}

	void SceneManager::OnDestroy()
	{
		if (m_Instance)
		{
			delete m_Instance;
		}
	}

	void SceneManager::OnStart()
	{
		/* Go through all Scenes and Start them. */
		for (int i = 0; i < m_Instance->m_Scenes.size(); i++)
		{
			m_Instance->m_Scenes[i]->OnStart();
		}
	}

	void SceneManager::OnUpdate()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_CurrentScene)
		{
			return;
		}
		/* if we do have a Current Scene. Update it. */
		m_Instance->m_CurrentScene->OnUpdate();

	}

	void SceneManager::OnPhysicsUpdate()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_CurrentScene)
		{
			return;
		}
		/* if we do have a Current Scene. Do a physics update on it. */
		m_Instance->m_CurrentScene->OnPhysicsUpdate();
	}

	void SceneManager::OnRender()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_CurrentScene)
		{
			return;
		}
		/* if we do have a Current Scene. Render it. */
		m_Instance->m_CurrentScene->OnRender();
	}

	void SceneManager::OnUpdateSceneCameraAspectRatio(float aspectRatio)
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_CurrentScene)
		{
			return;
		}
		/* Update the Camera Aspect Ratio. */
		m_Instance->m_CurrentScene->OnUpdateCameraAspectRatio(aspectRatio);
	}
	
	void SceneManager::SetCurrentScene(const std::string& name)
	{
		/* If the name of the Scene already matches the current. Early out. */
		if (m_Instance->m_CurrentScene->GetName() == name)
		{
			return;
		}
		/* Search through the list of Scenes added. */
		for (int i = 0; i < m_Instance->m_Scenes.size(); i++)
		{
			Scene* scene = m_Instance->m_Scenes[i];

			/* If the scene currently being looked at is the one we are looking for, set it as current. */
			if (scene->GetName() == name)
			{
				m_Instance->m_CurrentScene = scene;
				return;
			}
		}

		/* If we get here the scene was never found. */
		return;
	}

	void SceneManager::SetCurrentScene(int index)
	{
		/* Check if the index is outside the bounds of the Scenes array, early out. */
		if (index < 0 && index >= m_Instance->m_Scenes.size())
		{
			return;
		}

		/* Other wise set the scene. */
		m_Instance->m_CurrentScene = m_Instance->m_Scenes[index];
	}

	void SceneManager::AttachScene(Scene* scene)
	{
		/* Add a Scene. */
		for (int i = 0; i < m_Instance->m_Scenes.size(); i++)
		{
			/* Check for Duplicate. */
			if (m_Instance->m_Scenes[i] == scene)
			{
				return; /* if a duplicate was found don't add it. */
			}
		}

		/* If no duplicate was found, add it. */
		m_Instance->m_Scenes.push_back(scene);
	}
}