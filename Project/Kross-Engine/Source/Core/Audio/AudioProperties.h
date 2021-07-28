/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	struct KROSS_API AudioProperties
	{
	private:
		float m_Volume, m_Pan, m_PlaySpeed;
		bool m_Loop;

	protected:

	public:
		AudioProperties() :
			m_Volume	(1.0f),
			m_Pan		(0.0f),
			m_PlaySpeed	(1.0f),
			m_Loop		(false)
		{};
		~AudioProperties() {};

		// Sets all of the Audio Properties.
		void SetDefault()
		{
			m_Volume = 1.0f;
			m_Pan = 0.0f;
			m_PlaySpeed = 1.0f;
			m_Loop = false;
		}

		// Gets the Volume.
		float GetVolume() const { return m_Volume; };

		// Gets the Pan.
		const float GetPan() const { return m_Pan; };

		// Gets the Play Speed.
		const float GetPlaySpeed() const { return m_PlaySpeed; };

		// Gets if the Audio Source should loop.
		const bool GetLoop() const { return m_Loop; };

		// Sets the Volume. (CLAMPS BETWEEN 1.0 - 0.0)
		void SetVolume(float value) { m_Volume = (value > 1.0f) ? 1.0f : ((value < 0.0f) ? 0.0f : value); };

		/**
			Sets the Volume. (CLAMPS BETWEEN -1.0 - 1.0)
			 1.0 for Right.
			 0.0 for Center.
			-1.0 for Left.
		*/
		void SetPan(float value) { m_Pan = (value > 1.0f) ? 1.0f : ((value < -1.0f) ? -1.0f : value); };

		/**
			Sets the Play Speed. (WILL NOT GO BELLOW 0.0)
			Eg of Play Speeds.
			1.0 for Normal.
			0.5 for Half.
			Etc..
		*/
		void SetPlaySpeed(float value) { m_PlaySpeed = (value < 0.0f) ? 0.0f : value; };
		
		// Sets the Loop ability.
		void SetLoop(bool value) { m_Loop = value; };
	};
}