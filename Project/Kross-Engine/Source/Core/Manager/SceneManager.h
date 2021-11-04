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
            m_Scene             (nullptr),
            m_Transition        (false),
            m_KeepOther         (false),
            m_ApplicationStart  (true),
            m_Filepath          ("")
        {};
        ~SceneManager();

        static SceneManager* m_Instance;
        Scene* m_Scene;

        bool m_Transition, m_KeepOther, m_ApplicationStart;
        std::string m_Filepath;

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
        static Scene* GetScene() { return m_Instance->m_Scene; };

        // Sets the Current Scene. (Will Delete the Old Scene).
        static void SetScene(const std::string& filepath, bool keepOther = false);
    };
}
