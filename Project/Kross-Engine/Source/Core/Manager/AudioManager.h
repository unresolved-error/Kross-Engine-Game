/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"
#define WITH_WINMM
#include "soloud.h"

namespace Kross
{
    class KROSS_API AudioManager
    {
    private:
       
        static AudioManager* s_Instance;
        SoLoud::Soloud* p_Soloud;

    public:
        // Creates an Instance of the Manager.
        static void OnCreate();
         
        //deinits the soloud, AND Destroys an Instance of the Manager.
        static void OnDestroy();

        //inits soloud.
        static void OnStart();

        //De-inits the soloud manager. DOES NOT DELETE.
        static void OnShutdown();

    };
}