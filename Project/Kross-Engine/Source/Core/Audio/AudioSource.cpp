/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "AudioSource.h"

namespace Kross
{

	AudioSource::AudioSource(std::string filePath, bool isThisStream)
		: isStream(isThisStream), filePath(filePath)
	{
		if (isThisStream)
		{
			const char* filepathCStr = filePath.c_str();
			wavStreamFile->load(filepathCStr);

		}
		else
		{
			const char* filepathCStr = filePath.c_str();
			wavFile->load(filepathCStr);

		}
	}
}