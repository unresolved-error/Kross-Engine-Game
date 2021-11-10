/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Component/AudioPlayer.h"


#define WITH_WINMM
#include "soloud.h"
#include "soloud_wav.h"

namespace Kross
{
    class KROSS_API AudioManager
    {
    private:
       
        static AudioManager* m_Instance;
        SoLoud::Soloud* m_SoloudEngine;


    protected:
        friend class AudioPlayer;
        friend class Application;

        // Creates an Instance of the Manager.
        static void OnCreate();

        //inits soloud.
        static void OnStart();

        //De-inits the soloud manager. DOES NOT DELETE.
        static void OnShutdown();

        //deinits the soloud, AND Destroys an Instance of the Manager.
        static void OnDestroy();
        
        // Gets the Audio Engine.
        static SoLoud::Soloud* AudioEngine() { return m_Instance->m_SoloudEngine; };

    public:
        //"Sets global volume. 1 is normal, 0 is mute.
        static void SetGlobalVolume(float volume);

        //Get global volume, returns current vol, 1 is normal, 0 is mute.
        static float GetGlobalVolume();

        // Loads an Audio Source.
        static void LoadAudioSource(AudioSource* audioSource);

        // Stops all playing sounds.
        static void StopAllSounds();
    };
}