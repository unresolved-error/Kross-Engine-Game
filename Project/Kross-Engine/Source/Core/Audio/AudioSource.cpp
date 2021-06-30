/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "AudioSource.h"

#include "../Manager/AudioManager.h"

namespace Kross
{
	
	//AudioSource::AudioSource()
	//	: m_IsStream(isThisStream), m_FilePath(filePath)
	//{
	//	if (isThisStream)
	//	{
	//		const char* filepathCStr = filePath.c_str();
	//		m_WavStreamFile.load(filepathCStr);
	//
	//
	//		std::cout << " wav STREAM loaded." << std::endl;
	//
	//
	//	}
	//	else
	//	{
	//		const char* filepathCStr = filePath.c_str();
	//		m_WavFile.load(filepathCStr);
	//
	//		std::cout << " wav loaded." << std::endl;
	//
	//	}
	//}

	AudioSource* AudioSource::OnCreate(const std::string& filepath, const std::string& name, bool isStream)
	{
		/* Create a Blank Audio Source. */
		AudioSource* audioSource = KROSS_NEW AudioSource();

		/* Set up basic properties. */
		audioSource->SetName(name);
		audioSource->SetFilepath(filepath);
		audioSource->SetStream(isStream);

		/* Loads the Wav File. */
		audioSource->OnLoadWav();

		/* Return the Audio Source. */
		return audioSource;
	}

	void AudioSource::OnDestroy(AudioSource* audioSource)
	{
		/* Safe programming, not need but good to have. */
		if (audioSource)
			delete audioSource;
	}

	void AudioSource::OnLoadWav()
	{
		unsigned int result;

		/* Check if it is streamable or not. */
		if (m_IsStream)
			result = m_WavStreamFile.load(m_Filepath.c_str());

		else
			result = m_WavFile.load(m_Filepath.c_str());

		/* Error Checking. */
		if (result)
		{
			/* Get the Error Message. */
			const char* errorMessage = AudioManager::GetAudioEngine()->getErrorString(result);
			std::cout << "Audio Source " << m_Name << " Failed to Load! \n[" << result << "] " << errorMessage << "!" << std::endl;
		}
	}
}