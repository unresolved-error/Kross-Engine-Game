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
        AudioPlayer();
        ~AudioPlayer() { delete p_AudioProperties; };
        
         //Takes a reference to an audio source that has been loaded previously, and attaches it. WILL NOT COLLECT IT'S HANDLE.
        void SetAudioSource(AudioSource* toAttach) { p_AudioSrc = toAttach; };

        // Plays the Audio Source along side the Properties.
        void Play();

        // Pauses the Current playing Sound.
        void Pause();

        // Stops the Sounds playing.
        void Stop();

        // Queries if the Sound is Playing.
        const bool IsPlaying() const { return m_IsPlaying; };

        //-1 for left, +1 for right. 0.0 is center.
        void SetPan(float pan);

        //1 is base volume. High values cause clipping and static
        void SetVolume(float volume);

        //True if you want this to loop.
        void SetLoop(bool loop);

        // Gets the Pan.
        float GetPan() { return p_AudioProperties->GetPan(); };

        // Gets the Volume.
        float GetVolume() { return p_AudioProperties->GetVolume(); };

        // Gets if Looping is Enabled.
        bool GetLoop() { return p_AudioProperties->GetLoop(); };

        //moves the read to the seconds to this point in the track. Use only on paused sounds. Some sound types will NOT be able to seek backwards, if the read point is beyond the float supplied.
        void SeekSoundClipPoint(float seconds);

        //Pauses the sound after "seconds". Restart the track with the PauseSound function, this one can't.
        void PauseSoundDelayed(float seconds);

        //For both wavs and streams. Note: this sets relitive play speed, and therefore edits the sample rate. 1 is normal, .5 is half speed, and so on.
        void SetPlaySpeed(float playSpeed); /* Negative values Safe Guarded. */

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