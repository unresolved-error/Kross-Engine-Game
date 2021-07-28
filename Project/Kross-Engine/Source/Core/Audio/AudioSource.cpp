/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "AudioSource.h"

#include "../Manager/AudioManager.h"

#include "../Debug.h"

namespace Kross
{
	AudioSource* AudioSource::OnCreate(const std::string& filepath, const std::string& name, bool isStream)
	{
		/* Create a Blank Audio Source. */
		AudioSource* audioSource = KROSS_NEW AudioSource();

		/* Set up basic properties. */
		audioSource->SetName(name);
		audioSource->SetFilepath(filepath);
		audioSource->SetStream(isStream);

		/* Loads the Wav File. */
		AudioManager::LoadAudioSource(audioSource);

		/* Return the Audio Source. */
		return audioSource;
	}

	void AudioSource::OnDestroy(AudioSource* audioSource)
	{
		/* Safe programming, not need but good to have. */
		if (audioSource)
			delete audioSource;
	}
}