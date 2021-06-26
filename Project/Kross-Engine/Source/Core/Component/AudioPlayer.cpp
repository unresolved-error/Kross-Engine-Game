/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#include "AudioPlayer.h"

namespace Kross
{
	AudioPlayer::AudioPlayer()
	{
		AudioManager::OnAttachReference(this);
	}
	
	void AudioPlayer::AttachSoundToPlayer(AudioSource* toAttach)
	{
		audioSrc = toAttach;
	}

	void Kross::AudioPlayer::PlaySoundEffect(AudioSource* audioSrc, float volume, float pan, bool paused)
	{
		if (audioSrc->isStream) 
		{
			//Set the handle that the audioPlayer owns to this source's newly generated handle.
			audioHandle = audioEngine->play(audioSrc->wavStreamFile, volume, pan, paused); 
			//collect the handle and add to the audio source as well. This is so the player can recover handles.
			audioSrc->sourceHandle = audioHandle;
		}
		else 
		{
			audioHandle = audioEngine->play(audioSrc->wavFile, volume, pan, paused);
			
			audioSrc->sourceHandle = audioHandle;
		}

	}

	void AudioPlayer::SetPlaySpeed(float playSpeed)
	{
		audioEngine->setRelativePlaySpeed(audioHandle, playSpeed);
	}

	void AudioPlayer::SetPan(float pan)
	{
		audioEngine->setPan(audioHandle, pan);
	}

	void AudioPlayer::SetVolume(float volume)
	{
		audioEngine->setVolume(audioHandle, volume);
	}

	void AudioPlayer::SetIfLooping(bool looping)
	{
		audioEngine->setLooping(audioHandle, looping);
	}

}


