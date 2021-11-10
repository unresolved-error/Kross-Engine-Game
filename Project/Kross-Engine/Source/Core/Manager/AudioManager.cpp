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
    AudioManager* AudioManager::m_Instance = nullptr;

    void Kross::AudioManager::OnCreate()
    {
        if (!m_Instance)
        {
            m_Instance = KROSS_NEW AudioManager();
        }
    }

    void Kross::AudioManager::OnStart()
    {
        m_Instance->m_SoloudEngine = KROSS_NEW SoLoud::Soloud;
        SoLoud::result result = m_Instance->m_SoloudEngine->init();
    }

    void Kross::AudioManager::OnShutdown()
    {
        m_Instance->m_SoloudEngine->deinit();
    }

    void Kross::AudioManager::OnDestroy()
    {
        if (m_Instance->m_SoloudEngine)
        {
            m_Instance->m_SoloudEngine->deinit();
            delete m_Instance->m_SoloudEngine;
        }

        if (m_Instance)
        {
            delete m_Instance;
        }
    }

    void AudioManager::SetGlobalVolume(float volume)
    {
        m_Instance->m_SoloudEngine->setGlobalVolume(volume);
    }

    float AudioManager::GetGlobalVolume()
    {
        return m_Instance->m_SoloudEngine->getGlobalVolume();
    }

    void AudioManager::LoadAudioSource(AudioSource* audioSource)
    {
        unsigned int result;

        /* Check if it is streamable or not. */
        if (audioSource->IsStreamable())
        {
            result = audioSource->GetWavStream()->load(audioSource->GetFilepath().c_str());
        }
        else
        {
            result = audioSource->GetWav()->load(audioSource->GetFilepath().c_str());
        }

        /* Error Checking. */
        if (result)
        {
            /* Get the Error Message. */
            const char* errorMessage = m_Instance->m_SoloudEngine->getErrorString(result);
            Debug::LogErrorLine("Audio Source " + audioSource->GetName() + " Failed to Load! Filepath: " + audioSource->GetFilepath());
            Debug::LogErrorLine("[" + std::to_string(result) + "] " + (std::string)errorMessage + "!");
        }
    }
    void AudioManager::StopAllSounds()
    {
        m_Instance->m_SoloudEngine->stopAll();
    }
}
