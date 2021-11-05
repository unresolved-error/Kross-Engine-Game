#pragma once
/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include <Kross.h>
using namespace Kross;

static bool leaveLevel = false;

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
		if (audioPlayer) 
		{
			audioPlayer->Play();
		}
	}

	void Update() override
	{
		if (leaveLevel) 
		{
			//audioPlayer->FadeVolume(0, 3);
			audioPlayer->Stop();
			leaveLevel = false;
		}
		
	}





};
