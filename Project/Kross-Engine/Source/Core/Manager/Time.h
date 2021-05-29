/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Kross
{
    class KROSS_API Time
    {
    private:
        Time() :
            m_DeltaTime     (0.0f),
            m_PreviousTime  (0.0f)
        {};
        ~Time() {};

        static Time* s_Instance;

        float m_DeltaTime;
        float m_PreviousTime;

    protected:
        friend class Application;

        // Creates the Shader Manager.
        static void OnCreate();

        // Destroys the Shader Manager.
        static void OnDestroy();

        // Updates Delta Time.
        static void OnUpdateDeltaTime();

    public:
        /* Returns the current delta time */
        static const float GetDeltaTime() { return s_Instance->m_DeltaTime; };
    };
}
