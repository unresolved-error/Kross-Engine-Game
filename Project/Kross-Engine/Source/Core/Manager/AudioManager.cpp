/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "AudioManager.h"

namespace Kross
{
    AudioManager* AudioManager::s_Instance = nullptr;



    void Kross::AudioManager::OnCreate()
    {
        if (!s_Instance)
            s_Instance = KROSS_NEW AudioManager();
    }

    void Kross::AudioManager::OnStart()
    {
        s_Instance->p_Soloud = KROSS_NEW SoLoud::Soloud;
        SoLoud::result result = s_Instance->p_Soloud->init();

        if (result)
        {
            std::cout << " Everything is Fine?" << std::endl;
        }

        else
        {
            std::cout << "Something dung fucked up!" << std::endl;
        }
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
    void AudioManager::OnAttachReference(AudioPlayer* player)
    {
       player->SetAudioEngine(s_Instance->p_Soloud);
    }
}
