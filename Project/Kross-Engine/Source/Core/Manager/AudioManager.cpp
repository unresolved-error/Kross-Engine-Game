/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#include "AudioManager.h"

#include "../Debug.h"

namespace Kross
{
    AudioManager* AudioManager::s_Instance = nullptr;

    void Kross::AudioManager::OnCreate()
    {
        if (!s_Instance)
            s_Instance = KROSS_ALLOCATION_REPORT(AudioManager());
    }

    void Kross::AudioManager::OnStart()
    {
        s_Instance->p_Soloud = KROSS_ALLOCATION_REPORT(SoLoud::Soloud);
        SoLoud::result result = s_Instance->p_Soloud->init();
    }

    void Kross::AudioManager::OnShutdown()
    {
        s_Instance->p_Soloud->deinit();
    }

    void Kross::AudioManager::OnDestroy()
    {
        if (s_Instance->p_Soloud)
        {
            s_Instance->p_Soloud->deinit();
            delete s_Instance->p_Soloud;
        }

        if (s_Instance)
            delete s_Instance;
    }

    void AudioManager::SetGlobalVolume(float volume)
    {
        p_Soloud->setGlobalVolume(volume);
       
    }

    float AudioManager::GetGlobalVolume()
    {

        return p_Soloud->getGlobalVolume();
         
    }

    void AudioManager::LoadAudioSource(AudioSource* audioSource)
    {
        unsigned int result;

        /* Check if it is streamable or not. */
        if (audioSource->IsStreamable())
            result = audioSource->GetWavStream()->load(audioSource->GetFilepath().c_str());

        else
            result = audioSource->GetWav()->load(audioSource->GetFilepath().c_str());

        /* Error Checking. */
        if (result)
        {
            /* Get the Error Message. */
            const char* errorMessage = s_Instance->p_Soloud->getErrorString(result);
            Debug::LogErrorLine("Audio Source " + audioSource->GetName() + " Failed to Load! Filepath: " + audioSource->GetFilepath());
            Debug::LogErrorLine("[" + std::to_string(result) + "] " + (std::string)errorMessage + "!");
        }
    }
}
