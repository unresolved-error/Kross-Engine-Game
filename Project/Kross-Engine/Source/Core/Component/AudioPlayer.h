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
#include "../Audio/AudioProperties.h"

namespace Kross
{
    class KROSS_API AudioPlayer : public Component
    {
    public:
        /*!
            Audio Players's Constructor.
        */
        AudioPlayer();

        /*!
            Audio Players's Destructor.
        */
        ~AudioPlayer() { delete p_AudioProperties; };
        
        /*!
            Takes a reference to an audio source that has been loaded previously, and attaches it.
            \attention Will not collect the SoLoud Handle!
        */
        void SetAudioSource(AudioSource* toAttach) { p_AudioSrc = toAttach; };

        /*!
            Plays the Audio Source along side the Properties.
        */
        void Play();

        /*!
            Pauses the Current playing Sound.
        */
        void Pause();

        /*!
            Stops the Sounds playing.
        */
        void Stop();

        /*!
            Queries if the Sound is Playing.
        */
        const bool IsPlaying() const { return m_IsPlaying; };

        /*!
            Sets the Pan for the Player.
            \note See AudioProperties for usage.
        */
        void SetPan(float pan);

        /*!
            Sets the Volume of the Player.
            \note See AudioProperties for usage.
        */
        void SetVolume(float volume);

        /*!
            Sets the Loop for the Player.
            \note See AudioProperties for usage.
        */
        void SetLoop(bool loop);

        /*!
            Sets the Play Speed of the Player.
            \note See AudioProperties for usage.
        */
        void SetPlaySpeed(float playSpeed);

        /*!
            Gets the Audio Source.
        */
        AudioSource* GetSource() { return p_AudioSrc; };

        /*!
            Gets the Audio Properties.
        */
        AudioProperties* GetProperties() { return p_AudioProperties; };

        /*!
            Moves the read position to the seconds specified to this point in the track. Eg. Seconds = 40.0, Sounds Starts Playing. 40 seconds in.
            \note Seconds cannot be Negative!
            \attention Some sound types will NOT be able to seek backwards! (Still to be Specified!)
        */
        void PlaySoundTimeStamped(float seconds);

        /*!
            Pauses the sound after specified amount of Seconds has passed. Eg. Seconds = 20.5f, wait 20 and a Half seconds to paused this sound from here.
            \note To restart the sound, Stop it. Then Play it.
        */
        void PauseSoundAfterElapsedTime(float seconds);

        /*!
            Changes the Volume to the specified Volume over time.
            \note Seconds To Fade is how long it will take to get there.
            \note Changing Volume through this process will stop this command till called again.
            \attention Must Follow Volume Rules.
        */
        void FadeVolume(float destinedVolume, float secondsToFade);

        /*!
            Changes the Pan to the specified Pan over time.
            \note Seconds To Fade is how long it will take to get there.
            \note Changing Pan through this process will stop this command till called again.
            \attention Must Follow Pan Rules.
        */
        void FadePan(float destinedPan, float secondsToFade);

        /*!
            Changes the Play Speed to the specified Play Speed over time.
            \note Seconds To Fade is how long it will take to get there.
            \note Changing Play Speed through this process will stop this command till called again.
            \attention Must Follow Play Speed Rules.
        */
        void FadeRelativePlaySpeed(float destinedSpeed, float secondsToFade);

        /*!
            Will Oscilate between Min and Max Volume through each Cycle.
            \note Seconds is how long each Cycle goes.
            \attention Must Follow Volume Rules.
        */
        void OscillateVolume(float minVol, float maxVol, float seconds);

        /*!
            Will Oscilate between Min and Max Pan through each Cycle.
            \note Seconds is how long each Cycle goes.
            \attention Must Follow Pan Rules.
        */
        void OscillatePan(float minPan, float maxPan, float seconds);

        /*!
            Will Oscilate between Min and Max Play Speed through each Cycle.
            \note Seconds is how long each Cycle goes.
            \attention Must Follow Play Speed Rules.
        */
        void OscillateRelitivePlaySpeed(float minSpeed, float maxSpeed, float seconds);

    protected:

    private:
        SoLoud::handle m_AudioHandle;

        AudioSource* p_AudioSrc;
        AudioProperties* p_AudioProperties;

        bool m_IsPlaying, m_Stopped;
    };
}