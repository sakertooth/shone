#pragma once
#include "StereoFrame.hpp"

#include <vector>
#include <filesystem>
#include <sndfile.h>

namespace shone::core
{
    class AudioBuffer 
    {
    public:
        AudioBuffer(const std::filesystem::path& filePath);
        AudioBuffer(const std::size_t size);

        void writeToDisk(const std::filesystem::path& outputFilePath);

        const std::filesystem::path filePath() const;
        const std::vector<StereoFrame>& audioFrames() const;
        int sampleRate() const;

    private:
        std::pair<SNDFILE*, SF_INFO> openAudioHandle(const std::filesystem::path& filePath, int mode);

    private:
        std::filesystem::path m_filePath;
        std::vector<StereoFrame> m_audioFrames;
        int m_sampleRate = 0;
    };
}