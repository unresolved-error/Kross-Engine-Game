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

}


