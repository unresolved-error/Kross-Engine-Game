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
	{
		AudioManager::OnAttachReference(this);
	}

	void Kross::AudioPlayer::PlaySoundEffect()
	{

	}

}


