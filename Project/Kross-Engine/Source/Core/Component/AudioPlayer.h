/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"
#include "Component.h"
#include "../Audio/AudioSource.h"

namespace Kross
{
    class KROSS_API AudioPlayer : public Component
    {
    public:
        AudioPlayer();
        ~AudioPlayer() {};
        
         //Takes a reference to an audio source that has been loaded previously, and attaches it. WILL NOT COLLECT IT'S HANDLE.
        void AttachSoundToPlayer(AudioSource* toAttach);

        //for both wav and streams. Volume ranges [0,1], pan ranges from [-1,1].
        void PlaySoundEffect(AudioSource* audioSrc, float volume, float pan, bool paused);

        void SetPlaySpeed(float playSpeed);
        void SetPan(float pan);
        void SetVolume(float volume);
        void SetIfLooping(bool looping);


    protected:
        friend class AudioManager;
        void SetAudioEngine(SoLoud::Soloud* engine) { p_AudioEngine = engine; };

    private:
        AudioSource* p_AudioSrc;
        SoLoud::Soloud* p_AudioEngine;
        SoLoud::handle m_AudioHandle;

    };
}