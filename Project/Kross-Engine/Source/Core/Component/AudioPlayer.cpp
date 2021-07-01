/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#include "AudioPlayer.h"
#include "../Manager/AudioManager.h"

namespace Kross
{
	AudioPlayer::AudioPlayer()
		: p_AudioEngine(nullptr), m_AudioHandle(0), p_AudioSrc(nullptr)
	{
		AudioManager::OnAttachReference(this);
		//audioEngine = AudioManager::ReturnSoLoudReference();
	}
	
	void AudioPlayer::AttachSoundToPlayer(AudioSource* toAttach)
	{
		p_AudioSrc = toAttach;
	}

	void Kross::AudioPlayer::PlaySoundEffect(AudioSource* audioSrc, float volume, float pan, bool paused)
	{
		if (audioSrc->m_IsStream) 
		{
			//Set the handle that the audioPlayer owns to this source's newly generated handle.
			m_AudioHandle = p_AudioEngine->play(audioSrc->m_WavStreamFile, volume, pan, paused);
			//collect the handle and add to the audio source as well. This is so the player can recover handles.
			audioSrc->m_SourceHandle = m_AudioHandle;
		}
		else 
		{
			m_AudioHandle = p_AudioEngine->play(audioSrc->m_WavFile, volume, pan, paused);
			
			audioSrc->m_SourceHandle = m_AudioHandle;
			
		}
	
	}

	void AudioPlayer::PauseSound(bool paused)
	{
		p_AudioEngine->setPause(m_AudioHandle, paused);
	}

	void AudioPlayer::SeekSoundClipPoint(float seconds)
	{
		p_AudioEngine->seek(m_AudioHandle, seconds);
	}

	void AudioPlayer::PauseSoundDelayed(float seconds)
	{
		p_AudioEngine->schedulePause(m_AudioHandle, seconds);
	}

	void AudioPlayer::SetPlaySpeed(float playSpeed)
	{
		p_AudioEngine->setRelativePlaySpeed(m_AudioHandle, playSpeed);
	}

	void AudioPlayer::SetPan(float pan)
	{
		p_AudioEngine->setPan(m_AudioHandle, pan);
	}

	void AudioPlayer::SetVolume(float volume)
	{
		p_AudioEngine->setVolume(m_AudioHandle, volume);
	}

	void AudioPlayer::SetIfLooping(bool looping)
	{
		p_AudioEngine->setLooping(m_AudioHandle, looping);
	}

	void AudioPlayer::FadeVolume(float destinedVolume, float secondsToFade)
	{
		p_AudioEngine->fadeVolume(m_AudioHandle,destinedVolume,secondsToFade);
	}

	void AudioPlayer::FadePan(float destinedPan, float secondsToFade)
	{
		p_AudioEngine->fadePan(m_AudioHandle, destinedPan, secondsToFade);
	}

	void AudioPlayer::FadeRelativePlaySpeed(float destinedSpeed, float secondsToFade)
	{
		p_AudioEngine->fadeRelativePlaySpeed(m_AudioHandle, destinedSpeed, secondsToFade);
	}

	void AudioPlayer::OscillateVolume(float minVol, float maxVol, float seconds)
	{
		p_AudioEngine->oscillateVolume(m_AudioHandle,minVol, maxVol, seconds);
	}

	void AudioPlayer::OscillatePan(float minPan, float maxPan, float seconds)
	{
		p_AudioEngine->oscillatePan(m_AudioHandle, minPan, maxPan, seconds);
	}

	void AudioPlayer::OscillateRelitivePlaySpeed(float minSpeed, float maxSpeed, float seconds)
	{
		p_AudioEngine->oscillateRelativePlaySpeed(m_AudioHandle, minSpeed, maxSpeed, seconds);
	}

	void AudioPlayer::StopThisSound()
	{
		p_AudioEngine->stop(m_AudioHandle);
	}

	

}


