#pragma once
#include <vector>
#include <filesystem>
#include <sndfile.h>

#include "AudioFrame.hpp"

namespace shone::core
{
    class AudioFile
    {
    public:
        AudioFile(const std::filesystem::path& filepath);
        
        std::vector<float> mixToMono();
        
        const std::vector<AudioFrame> audioFrames() const;
        int sampleRate() const;
        int numChannels() const;
    private:
        std::vector<AudioFrame> m_audioFrames;
        int m_sampleRate;
        int m_numChannels;
    };
}