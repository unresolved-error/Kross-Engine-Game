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
        
         


        void PlaySoundEffect();



    protected:
        friend class AudioManager;
        void SetAudioEngine(SoLoud::Soloud* engine) { audioEngine = engine; };

    private:
        AudioSource* audioSrc;
        SoLoud::Soloud* audioEngine;
        SoLoud::handle audioHandle;

    };
}