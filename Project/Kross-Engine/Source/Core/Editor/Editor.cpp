/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Editor.h"

#include "../Input.h"

namespace Kross
{
	Editor* Editor::s_Instance = nullptr;

	Editor::~Editor()
	{
		/* Delete all of the Editor Windows Added. */
		for (int i = 0; i < m_EditorWindows.size(); i++)
		{
			delete m_EditorWindows[i];
			m_EditorWindows[i] = nullptr;
		}
	}

	void Editor::OnCreate()
	{
		if (!s_Instance)
			s_Instance = KROSS_ALLOCATION_REPORT(Editor());
	}

	void Editor::OnDestroy()
	{
		if (s_Instance)
			delete s_Instance;
	}

	void Editor::OnStart(Window* window)
	{
		/* Creates the Context. */
		ImGui::CreateContext();

		/* Make use of the GLFW and OpenGL Backends. */
		ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");

		/* Starts the Editor Windows. */
		for (int i = 0; i < s_Instance->m_EditorWindows.size(); i++)
			s_Instance->m_EditorWindows[i]->OnStart();

		/* Editor has Started. */
		s_Instance->m_IsUpdating = true;
	}

	void Editor::OnUpdate()
	{
		/* Gets the Main Viewport. */
		s_Instance->p_Viewport = ImGui::GetMainViewport();

		/* Attach all of the Editor Windows to the ImGui Render Queue. */
		for (int i = 0; i < s_Instance->m_EditorWindows.size(); i++)
			s_Instance->m_EditorWindows[i]->Attach();
	}

	void Editor::NewFrame()
	{
		/* Initialise the New Frame. */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::AttachEditorWindow(EditorWindow* window)
	{
		s_Instance->m_EditorWindows.push_back(window);

		if (typeid(*window) == typeid(ObjectEditor))
			s_Instance->p_ObjectEditor = (ObjectEditor*)window;

		if (typeid(*window) == typeid(MainMenu))
			s_Instance->p_MainMenu = (MainMenu*)window;

		if (typeid(*window) == typeid(AssetPanel))
			s_Instance->p_AssetPanel = (AssetPanel*)window;

		if (s_Instance->m_IsUpdating)
			window->OnStart();
	}
	void Editor::DetachEditorWindow(EditorWindow* window)
	{
		for (int i = 0; i < s_Instance->m_EditorWindows.size(); i++)
		{
			if (s_Instance->m_EditorWindows[i] == window)
			{
				delete s_Instance->m_EditorWindows[i];
				s_Instance->m_EditorWindows.erase(s_Instance->m_EditorWindows.begin() + i);
				break;
			}
		}
	}
	Vector2 Editor::GetViewportPosition()
	{
		if(s_Instance->p_Viewport)
			return Vector2(s_Instance->p_Viewport->WorkPos.x, s_Instance->p_Viewport->WorkPos.y);

		return Vector2(0);
	}

	Vector2 Editor::GetViewportSize()
	{
		if (s_Instance->p_Viewport)
			return Vector2(s_Instance->p_Viewport->WorkSize.x, s_Instance->p_Viewport->WorkSize.y);

		return Vector2(0);
	}

	void Editor::OnRender()
	{
		/* Render the Editor. */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::SetScene(Scene* scene)
	{
		for (int i = 0; i < s_Instance->m_EditorWindows.size(); i++)
		{
			s_Instance->m_EditorWindows[i]->p_Scene = scene;
		}
	}

	void Editor::OnShutdown()
	{
		/* Destroy the Existance of ImGui. */
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Editor::StylePush()
	{
		/* Colour Variables. */ 
		ImVec4 blue =				ImVec4(0.000f, 0.314f, 0.745f, 1.000f);
		ImVec4 lightBlue =			ImVec4(0.196f, 0.588f, 1.000f, 1.000f);
		ImVec4 lightGrey =			ImVec4(0.216f, 0.219f, 0.259f, 1.000f);
		ImVec4 grey =				ImVec4(0.176f, 0.180f, 0.224f, 1.000f);
		ImVec4 darkGrey =			ImVec4(0.137f, 0.141f, 0.180f, 1.000f);
		ImVec4 evenDarkerGrey =		ImVec4(0.102f, 0.106f, 0.145f, 1.000f);

		/* Push Colour Styles. */
		ImGui::PushStyleColor(ImGuiCol_WindowBg, darkGrey);
		ImGui::PushStyleColor(ImGuiCol_Border, evenDarkerGrey);
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, grey);
		ImGui::PushStyleColor(ImGuiCol_Header, lightGrey);
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, lightBlue);
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, blue);
		ImGui::PushStyleColor(ImGuiCol_TitleBg, lightGrey);
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, blue);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, lightGrey);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, lightBlue);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, blue);
		ImGui::PushStyleColor(ImGuiCol_Tab, lightGrey);
		ImGui::PushStyleColor(ImGuiCol_TabHovered, lightBlue);
		ImGui::PushStyleColor(ImGuiCol_TabActive, blue);
		ImGui::PushStyleColor(ImGuiCol_CheckMark, blue);

		/* Padding. */
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 2.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 2.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4.0f, 4.0f));

		/* Spacing. */
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 8.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));

		/* Rounding. */
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 8.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 4.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4.0f);

		/* Sizes. */
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 16.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 16.0f);
	}

	void Editor::StylePop()
	{
		/* Pop all Style Modifications. */
		ImGui::PopStyleColor(15);
		ImGui::PopStyleVar(14);
	}
}