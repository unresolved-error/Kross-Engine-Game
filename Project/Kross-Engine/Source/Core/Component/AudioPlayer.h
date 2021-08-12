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

        //Destined volume is intended end volume. 0 is silent, 1 is full volume. Seconds is how long to get there, in seconds.
        //This is disabled if you change volume mid way.
        void FadeVolume(float destinedVolume, float secondsToFade);

        //DestinedPan is intended end pan. -1 is left, 1 is right. Seconds is how long to get there, in seconds.
        //This is disabled if you change Pan mid way.
        void FadePan(float destinedPan, float secondsToFade);

        ////DestinedSpeed is intended end play speed. 0 OR NEGATIVE MAY PRODUCE AN ERROR.  1 is Normal Speed. Seconds is how long to get there, in seconds.
        //This is disabled if you change speed mid way through fade.
        void FadeRelativePlaySpeed(float destinedSpeed, float secondsToFade);

        //minVol (0 is silent) and maxVol (1 is regular vol) are what is oscillated between and seconds is each cycles length.
        void OscillateVolume(float minVol, float maxVol, float seconds);

        //minPan and maxPan (-1 is left, 1 is right) are what is oscillated between and seconds is each cycles length.
        void OscillatePan(float minPan, float maxPan, float seconds);

        //minSpeed and maxSpeed (less than 0 may error, 1 is normal play speed) are what is oscillated between and seconds is each cycles length.
        void OscillateRelitivePlaySpeed(float minSpeed, float maxSpeed, float seconds);

    protected:

    private:
        SoLoud::handle m_AudioHandle;

        AudioSource* p_AudioSrc;
        AudioProperties* p_AudioProperties;

        bool m_IsPlaying, m_Stopped;
    };
}