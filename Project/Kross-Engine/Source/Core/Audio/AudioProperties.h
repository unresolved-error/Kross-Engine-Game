/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	/*!
		\struct AudioProperties
		\details Data struct for all Audio Properties in terms of how a particular sound is played.
	*/
	struct KROSS_API AudioProperties
	{
	private:
		float m_Volume, m_Pan, m_PlaySpeed;
		bool m_Loop;

	protected:

	public:
		/*!
		    Audio Properties Constructor.
		*/
		AudioProperties() :
			m_Volume	(1.0f),
			m_Pan		(0.0f),
			m_PlaySpeed	(1.0f),
			m_Loop		(false)
		{};
		/*!
		    Audio Properties Destructor.
		*/
		~AudioProperties() {};

		/*!
		 	Sets all of the Audio Properties to Default.
		*/
		void SetDefault()
		{
			m_Volume = 1.0f;
			m_Pan = 0.0f;
			m_PlaySpeed = 1.0f;
			m_Loop = false;
		}

		/*!
			Gets the Volume.
		*/
		float GetVolume() const { return m_Volume; };

		/*!
			Gets the Pan.
		*/
		const float GetPan() const { return m_Pan; };

		/*!
			Gets the Play Speed.
		*/
		const float GetPlaySpeed() const { return m_PlaySpeed; };

		/*!
			Gets if the Audio Source should loop.
		*/
		const bool GetLoop() const { return m_Loop; };

		/*!
			Sets the Volume.
			\attention Must be between 0.0 and 1.0!
		*/
		void SetVolume(float value) { m_Volume = (value > 1.0f) ? 1.0f : ((value < 0.0f) ? 0.0f : value); };

		/*!
			Sets the Pan.
			 1.0 for Right.
			 0.0 for Center.
			-1.0 for Left.
			\attention Must be between -1.0 and 1.0!
		*/
		void SetPan(float value) { m_Pan = (value > 1.0f) ? 1.0f : ((value < -1.0f) ? -1.0f : value); };

		/*!
			Sets the Play Speed.
			Eg of Play Speeds.
			1.0 for Normal.
			0.5 for Half.
			Etc..
			\attention Must be above 0.0!
		*/
		void SetPlaySpeed(float value) { m_PlaySpeed = (value < 0.0f) ? 0.0f : value; };
		
		/*!
			Sets the Loop ability.
		*/
		void SetLoop(bool value) { m_Loop = value; };
	};
}