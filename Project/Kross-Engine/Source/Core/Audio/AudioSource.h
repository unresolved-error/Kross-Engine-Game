/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */
#pragma once
#include "../Core.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

namespace Kross
{
    class KROSS_API AudioSource
    {
    public:
        /**
            On creation: If this is a sound effect, just a filepath is fine.
            If it needs to be streamed, a bool of "true" is required.
        */
        AudioSource(std::string filepath, bool isStream = false);
        ~AudioSource();

        bool m_IsStream;

        std::string m_FilePath;
        std::string m_Name;

        SoLoud::Wav m_WavFile;
        SoLoud::WavStream m_WavStreamFile;

        SoLoud::handle m_SourceHandle;


    private:



    };

}