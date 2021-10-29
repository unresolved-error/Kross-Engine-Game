/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "SceneManager.h"
#include "../File-IO/FileSystem.h"

namespace Kross
{
	SceneManager*		SceneManager::m_Instance =		nullptr;

	SceneManager::~SceneManager()
	{
		Scene::OnDestroy(m_Instance->m_Scene);
		m_Instance->m_Scene = nullptr;
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
		if (m_Instance->m_ApplicationStart)
		{
			m_Instance->m_Scene = FileSystem::OnReadScene(m_Instance->m_Filepath);
			m_Instance->m_Scene->OnStart();
			m_Instance->m_ApplicationStart = false;		/* ----------------- */
			m_Instance->m_Transition = false;			/*       Reset       */
			m_Instance->m_KeepOther = false;			/*     Everything    */
			m_Instance->m_Filepath = "";				/* ----------------- */
		}
		else
		{
			if (m_Instance->m_Transition)
			{
				if (!m_Instance->m_KeepOther)
				{
					Scene::OnDestroy(m_Instance->m_Scene);
				}

				m_Instance->m_Scene = FileSystem::OnReadScene(m_Instance->m_Filepath);
				m_Instance->m_Scene->OnStart();

				m_Instance->m_Transition = false;
			}

			else return;
		}
	}

	void SceneManager::OnUpdate()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_Scene) return;

		/* if we do have a Current Scene. Update it. */
		m_Instance->m_Scene->OnUpdate();

	}

	void SceneManager::OnPhysicsUpdate()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_Scene) return;

		/* if we do have a Current Scene. Do a physics update on it. */
		m_Instance->m_Scene->OnPhysicsUpdate();
	}

	void SceneManager::OnRender()
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_Scene) return;

		/* if we do have a Current Scene. Render it. */
		m_Instance->m_Scene->OnRender();
	}

	void SceneManager::OnUpdateSceneCameraAspectRatio(float aspectRatio)
	{
		/* If no current scene set, early out. */
		if (!m_Instance->m_Scene) return;

		/* Update the Camera Aspect Ratio. */
		m_Instance->m_Scene->OnUpdateCameraAspectRatio(aspectRatio);
	}

	void SceneManager::SetScene(const std::string& filepath, bool keepOther)
	{
		m_Instance->m_Filepath = filepath;
		m_Instance->m_KeepOther = keepOther;
		m_Instance->m_Transition = true;
	}
}