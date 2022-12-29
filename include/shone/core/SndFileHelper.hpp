#pragma once
#include <filesystem>
#include <sndfile.h>

namespace shone::core 
{
    class SndFileHelper 
    {
    public:
        static SNDFILE* openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode);
    };
}