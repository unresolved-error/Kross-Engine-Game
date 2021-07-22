/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Application.h"

#include "Manager/ShaderManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Manager/AudioManager.h"
#include "Manager/Time.h"
#include "Physics/Physics.h"

#include "Debug.h"

#include "Renderer/Image/Atlas.h"

#include "Input.h"

#include "Editor/Editor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Kross
{
	Application*	Application::s_Instance =	nullptr;

	Application::Application(const std::string& title, int width, int height) :
		p_Window	(KROSS_NEW Window())
	{
		p_Window->SetWidth(width);
		p_Window->SetHeight(height);
		p_Window->SetTitle(title);
		p_Window->SetVSync(0);
	}

	Application::~Application()
	{}

	void Application::OnCreate(const std::string& title, int width, int height)
	{
		if (!s_Instance)
			s_Instance = KROSS_NEW Application(title, width, height);
	}

	void Application::OnStart()
	{
		s_Instance->p_Window->OnInitialise();
		ShaderManager::OnCreate();
		ResourceManager::OnCreate();
		SceneManager::OnCreate();
		Time::OnCreate();
		Input::OnCreate();
		Input::SetWindow(s_Instance->p_Window);
		Physics::OnCreate();
		AudioManager::OnCreate();
		AudioManager::OnStart();
		Editor::OnCreate();

		/* Reads the Manifest File. */
		ResourceManager::OnReadManifest();
	}

	void Application::OnUpdate()
	{
		/* If the window was successfully Started. Run the Application. */
		if (s_Instance->p_Window->GetInitialiseStatus())
		{
			Debug::LogLine(std::string() + "Kross Engine Running...");

			SceneManager::OnStart();
			Debug::Log(std::string() + "Starting Main Loop...");
			Debug::EndLine();

			#ifdef KROSS_EDITOR
			Editor::OnStart(s_Instance->p_Window);
			#endif

			/* While the window isn't closed */
			while (s_Instance->p_Window->GetClosedStatus() == false)
			{
				s_Instance->p_Window->OnStart();

				Time::OnUpdateDeltaTime();
				SceneManager::OnUpdateSceneCameraAspectRatio(s_Instance->p_Window->GetApsectRatio());

				SceneManager::OnUpdate();

				#ifndef KROSS_EDITOR
				SceneManager::OnPhysicsUpdate();
				#endif

				SceneManager::OnRender();

				#ifdef KROSS_EDITOR
				Editor::NewFrame();
				Editor::StylePush();
				Editor::OnUpdate();

				///* Do stuff here. */
				//ImGui::Begin("Scene Hierarchy");
				//List<Object*> objects = SceneManager::GetCurrentScene()->GetObjects();
				//if (ImGui::TreeNodeEx(SceneManager::GetCurrentScene()->GetName().c_str()))
				//{
				//	for (int i = 0; i < objects.size(); i++)
				//	{
				//		if (ImGui::TreeNodeEx(objects[i]->GetName().c_str(), ImGuiTreeNodeFlags_Leaf));
				//		{
				//			if (ImGui::IsItemHovered() && Input::GetKeyPressed(Key::Delete))
				//				SceneManager::GetCurrentScene()->DetachObject(objects[i]);
				//
				//			ImGui::TreePop();
				//		}
				//	}
				//	ImGui::Begin("Other Window");
				//
				//	float value = 0.0f;
				//	int other = 0;
				//	ImGui::DragFloat("X Position", &value, FLT_MIN, FLT_MAX);
				//	ImGui::SliderInt("Someting", &other, INT32_MIN, INT32_MAX);
				//	if (ImGui::Button("Press Me"))
				//	{
				//		Debug::LogLine((std::string)"Button Pressed!");
				//	}
				//	ImGui::End();
				//
				//	ImGui::TreePop();
				//}
				//
				//ImGui::End();

				Editor::StylePop();
				Editor::OnRender();
				#endif

				s_Instance->p_Window->OnPollEvents();

			}
		}

		#ifdef KROSS_EDITOR
		Editor::OnShutdown();
		#endif

		return;
	}

	void Application::OnShutdown()
	{
		Editor::OnDestroy();

		s_Instance->p_Window->OnShutdown();
		AudioManager::OnShutdown();

		/* Writes the Manifest. */
		ResourceManager::OnWriteManifest();

		ResourceManager::OnDestroy();

		AudioManager::OnDestroy();
		ShaderManager::OnDestroy();
		SceneManager::OnDestroy();
		Time::OnDestroy();
		Input::OnDestoy();
		Physics::OnDestroy();
	}

	void Application::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}
}