/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "../../Core.h"

#include "MainMenu.h"

namespace Kross
{
	void MainMenu::Attach()
	{
		/* Begins the main menu bar */
		ImGui::BeginMainMenuBar();

		/* Adds the "File" menu */
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Separator();

			if (ImGui::MenuItem("New Scene", "  Crtl + N")) {}
			if (ImGui::MenuItem("Open Scene", "  Crtl + O")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Save", "  Crtl + S")) {}
			if (ImGui::MenuItem("Save As"))	{}
			if (ImGui::MenuItem("Save All", "  Ctrl + Shift + S")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Exit")) {}
			ImGui::Separator();

			ImGui::EndMenu();
		}

		/* Adds the "Edit" menu */
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "  Ctrl + Z")) {}
			if (ImGui::MenuItem("Redo", "  Ctrl + Y")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Cut", "  Ctrl + X")) {}
			if (ImGui::MenuItem("Copy", "  Ctrl + C")) {}
			if (ImGui::MenuItem("Paste", "  Ctrl + V")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Rename")) {}
			if (ImGui::MenuItem("Delete", "  Del")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Find", "  Ctrl + F")) {}
			ImGui::Separator();

			if (ImGui::MenuItem("Play", "  Alt + P")) {}
			if (ImGui::MenuItem("Pause", "  Alt + Shift + P")) {}
			if (ImGui::MenuItem("Stop", "  Ctrl + Alt + P")) {}
			ImGui::Separator();

			ImGui::EndMenu();
		}
		
		/* Adds the "Create" menu */
		if (ImGui::BeginMenu("Create"))
		{
			ImGui::Separator();

			if (ImGui::BeginMenu("Object"))
			{
				ImGui::Separator();

				if (ImGui::MenuItem("Empty")) {}
				if (ImGui::MenuItem("Camera")) {}
				if (ImGui::MenuItem("Text")) {}
				if (ImGui::MenuItem("Sprite")) {}
				if (ImGui::MenuItem("Physical")) {}
				if (ImGui::MenuItem("Tile Map")) {}
				if (ImGui::MenuItem("Particle Emitter")) {}
				ImGui::Separator();

				ImGui::EndMenu();
			}
			ImGui::Separator();


			ImGui::EndMenu();
		}

		/* Adds the "Component" menu */
		if (ImGui::BeginMenu("Component"))
		{
			ImGui::Separator();
			if (ImGui::BeginMenu("Add Component"))
			{
				ImGui::Separator();

				if (ImGui::MenuItem("Animator")) {}
				if (ImGui::MenuItem("Audio Player")) {}
				if (ImGui::MenuItem("Camera")) {}
				if (ImGui::MenuItem("Particle Emitter")) {}
				if (ImGui::MenuItem("Rigidbody 2D")) {}
				if (ImGui::MenuItem("Script")) {}
				if (ImGui::MenuItem("Sprite Renderer")) {}
				if (ImGui::MenuItem("Text Renderer")) {}
				if (ImGui::MenuItem("Tile Map Renderer")) {}
				if (ImGui::MenuItem("Transform 2D")) {}
				ImGui::Separator();

				ImGui::EndMenu();
			}

			ImGui::Separator();
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	void MainMenu::SetFlags()
	{
	}

	void MainMenu::OnStart()
	{
	}
}


/*
* Example of adding a menu items 
* 
* // Adds the "Create" menu //
* if (ImGui::BeginMenu("Example"))
* {
* 	// Top of menu separator //
* 	ImGui::Separator();
* 
* 	// This creates a menu inside the existing menu //
* 	if (ImGui::BeginMenu("innerMenu"))
* 	{
* 		// Top of menu separator
* 		ImGui::Separator();
*		
*		// Creates the Menu items //
* 		if (ImGui::MenuItem("Empty")) {}
* 		if (ImGui::MenuItem("Item")) {}
* 
* 		// Bottom of menu separator //
* 		ImGui::Separator();
* 
* 		// Ends the menu //
* 		ImGui::EndMenu();
* 	}
* 	// Bottom of menu separator //
* 	ImGui::Separator();
* 
* 	// Ends the menu //
* 	ImGui::EndMenu();
* }*/
