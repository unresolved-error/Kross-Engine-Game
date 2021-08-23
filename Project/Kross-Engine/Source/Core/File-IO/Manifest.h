/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Logger.h"

namespace Kross
{
	class KROSS_API Manifest
	{
	private:
		static Manifest* m_Instance;

		Kross::Logger* m_Logger;

		Manifest() :
			m_Logger	(KROSS_NEW Kross::Logger())
		{
			m_Logger = KROSS_NEW Kross::Logger();
		};
		~Manifest();

	protected:
		template<typename Type> friend class Serialiser;

		/*!
			Gets the Logger.
		*/
		static Kross::Logger* Logger() { return m_Instance->m_Logger; };

	public:
		/*!
			Creates a Manifest Instance.
		*/
		static void OnCreate();

		/*!
			Destroys the Manifest Instance.
		*/
		static void OnDestroy();

		/*!
			Loads a Manifest File.
		*/
		static void Load(const std::string& filepath);

		/*!
			Writes a Manifest File.
		*/
		static void Write(const std::string& filepath);
	};
}
