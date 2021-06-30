/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "AudioSource.h"

namespace Kross
{
	
	AudioSource::AudioSource(std::string filePath, bool isThisStream)
		: m_IsStream(isThisStream), m_FilePath(filePath)
	{
		if (isThisStream)
		{
			const char* filepathCStr = filePath.c_str();
			m_WavStreamFile.load(filepathCStr);


			std::cout << " wav STREAM loaded." << std::endl;


		}
		else
		{
			const char* filepathCStr = filePath.c_str();
			m_WavFile.load(filepathCStr);

			std::cout << " wav loaded." << std::endl;

		}
	}

}