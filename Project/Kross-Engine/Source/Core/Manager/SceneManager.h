/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "../Core.h"

#include "../Scene.h"

namespace Kross
{
    class KROSS_API SceneManager
    {
    private:
        SceneManager() :
            m_Scenes        (std::vector<Scene*>()),
            m_CurrentScene  (nullptr)
        {};
        ~SceneManager();

        static SceneManager* m_Instance;

        std::vector<Scene*> m_Scenes;
        Scene* m_CurrentScene;

    protected:
        friend class Application;
        friend class MainMenu;

        // Creates an instance of the Scene Manager.
        static void OnCreate();

        // Destroys the innstance of the Scene Manager.
        static void OnDestroy();

        // Starts all Scenes.
        static void OnStart();

        // Updates the Current Scene.
        static void OnUpdate();

        // Does a Physics Update on the Current Scene.
        static void OnPhysicsUpdate();

        // Renders the Current Scene.
        static void OnRender();

        // Updates the Current Scene Primary Camera Aspect Ratio.
        static void OnUpdateSceneCameraAspectRatio(float apsectRatio);

    public:
        // Get's the Current Selected Scene.
        static Scene* GetCurrentScene() { return m_Instance->m_CurrentScene; };

        // Sets the Current Scene. (BY NAME)
        static void SetCurrentScene(const std::string& name);

        // Sets the Current Scene. (BY INDEX)
        static void SetCurrentScene(int index);

        // Adds a Scene to the Scene Manager.void
        static void AttachScene(Scene* scene);
    };
}
