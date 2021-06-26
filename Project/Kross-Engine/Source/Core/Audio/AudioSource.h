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
        AudioSource(std::string filepath, bool isStream = false);
        ~AudioSource();

        bool isStream;

        std::string filePath;
        std::string name;

        SoLoud::Wav wavFile;
        SoLoud::WavStream wavStreamFile;

        SoLoud::handle sourceHandle;


    private:



    };

}