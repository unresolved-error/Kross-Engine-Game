#pragma once
/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include <Kross.h>
using namespace Kross;

static bool leaveLevel = false;
static bool mainMenuMusicPlaying = false;

class bgAudioManager : public Script
{
public:
	AudioPlayer* audioPlayer = nullptr;

	bgAudioManager()
	{
		m_Name = "bgAudioManager";
	}
	~bgAudioManager() {}


	Script* Duplicate() override
	{
		return KROSS_NEW bgAudioManager();
	}

	void Start() override
	{
		audioPlayer = GetComponent<AudioPlayer>();
		if (audioPlayer && !mainMenuMusicPlaying) 
		{
			audioPlayer->Play();
			mainMenuMusicPlaying = true;
		}
	}

	void Update() override
	{
		if (leaveLevel) 
		{
			AudioManager::StopAllSounds();
			leaveLevel = false;
			mainMenuMusicPlaying = false;
		}
		
	}





};
