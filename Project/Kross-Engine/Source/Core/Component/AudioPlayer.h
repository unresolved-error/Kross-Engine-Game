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
#include "../Manager/AudioManager.h"

namespace Kross
{
    class KROSS_API AudioPlayer : public Component
    {
    public:
        AudioPlayer();
        ~AudioPlayer();
        
         //Takes a reference to an audio source that has been loaded previously, and attaches it. WILL NOT COLLECT IT'S HANDLE.
        void AttachSoundToPlayer(AudioSource* toAttach);

        void PlaySoundEffect(AudioSource* audioSrc, float volume, float pan, bool paused);
        void SetPlaySpeed(float playSpeed);
        void SetPan(float pan);
        void SetVolume(float volume);
        void SetIfLooping(bool looping);

    protected:
        friend class AudioManager;
        void SetAudioEngine(SoLoud::Soloud* engine) { audioEngine = engine; };

    private:
        AudioSource* audioSrc;
        SoLoud::Soloud* audioEngine;
        SoLoud::handle audioHandle;

    };
}