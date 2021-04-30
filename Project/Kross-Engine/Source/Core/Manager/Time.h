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
        static float s_DeltaTime;
        static float s_PreviousTime;
        static Time* s_Instance;

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
        static const float GetDeltaTime() { return s_DeltaTime; };
    };
}
