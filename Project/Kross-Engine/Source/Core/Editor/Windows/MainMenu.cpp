/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Chris Deitch;
 */

#include "../../Core.h"

#include "MainMenu.h"
#include "../../Application.h"
#include "../../Manager/SceneManager.h"
#include "../../File-IO/FileSystem.h"

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

			if (ImGui::MenuItem("Save", "  Crtl + S")) 
			{	
				FileSystem::OnWriteScene(SceneManager::GetCurrentScene());
			}
			if (ImGui::MenuItem("Save As"))	{}
			if (ImGui::MenuItem("Save All", "  Ctrl + Shift + S")) 
			{
				for (int i = 0; i < SceneManager::s_Instance->m_Scenes.size(); i++)
				{
					FileSystem::OnWriteScene(SceneManager::s_Instance->m_Scenes[i]);
				}
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Exit", "  Alt + F4")) 
			{
				Application::GetWindow()->CloseWindow();
			}
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

				if (ImGui::MenuItem("Empty"))
				{
					Object* object = Object::OnCreate();
					SceneManager::GetCurrentScene()->AttachObject(object);
				}
				if (ImGui::MenuItem("Camera"))
				{
					Object* camera = Object::OnCreate("Camera");
					camera->AttachComponent<Camera>();
					SceneManager::GetCurrentScene()->AttachObject(camera);
				}
				if (ImGui::MenuItem("Text"))
				{
					Object* text = Object::OnCreate("Text");
					text->AttachComponent<TextRenderer>();
					SceneManager::GetCurrentScene()->AttachObject(text);
				}
				if (ImGui::MenuItem("Sprite"))
				{
					Object* sprite = Object::OnCreate("Sprite");
					sprite->AttachComponent<SpriteRenderer>();
					SceneManager::GetCurrentScene()->AttachObject(sprite);
				}
				if (ImGui::MenuItem("Rigidbody 2D"))
				{
					Object* rigidbody = Object::OnCreate("Rigidbody");
					rigidbody->AttachComponent<Rigidbody2D>();
					SceneManager::GetCurrentScene()->AttachObject(rigidbody);
				}
				if (ImGui::MenuItem("Tile Map"))
				{
					Object* tileMap = Object::OnCreate("Tile Map");
					tileMap->AttachComponent<TileMapRenderer>();
					SceneManager::GetCurrentScene()->AttachObject(tileMap);
				}
				if (ImGui::MenuItem("Particle Emitter"))
				{
					Object* particleEmitter = Object::OnCreate("Particle Emitter");
					particleEmitter->AttachComponent<ParticleEmitter>();
					SceneManager::GetCurrentScene()->AttachObject(particleEmitter);
				}
				if (ImGui::MenuItem("Audio Player"))
				{
					Object* audioPlayer = Object::OnCreate("Audio player");
					audioPlayer->AttachComponent<AudioPlayer>();
					SceneManager::GetCurrentScene()->AttachObject(audioPlayer);
				}

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
				if (ImGui::MenuItem("Camera")) 
				{
					if (p_SelectedObject && !p_SelectedObject->AttachComponent<Camera>())
					{
						Debug::LogWarningLine("Could not add Camera to Object: " + p_SelectedObject->GetName());
					}
				}
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
*		// When setting tool tips add two spaces before //
*		if (ImGui::MenuItem("Exit", "  Alt + F4")) {}
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
