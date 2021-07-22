/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Scene.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Kross
{
	class KROSS_API EditorWindow
	{
	private:
		Scene* p_Scene;

		std::string m_Title;
		int m_Width, m_Height;

		ImGuiWindowFlags_ m_WindowFlags;

	protected:
		friend class Editor;

		// Sets the Window Flags.
		virtual void SetFlags() = 0;

		// Initialises basic Variables. 
		virtual void OnStart() = 0;

		// Attaches Render Data of the Window.
		virtual void Attach() = 0;

	public:
		EditorWindow() :
			p_Scene			(nullptr),
			m_Title			(std::string()),
			m_Width			(0),
			m_Height		(0),
			m_WindowFlags	(ImGuiWindowFlags_None)
		{};
		virtual ~EditorWindow() {};
	};
}

#include "Windows/SceneHierarchy.h"