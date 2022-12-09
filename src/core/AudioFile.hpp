#pragma once
#include "StereoFrame.hpp"

#include <vector>
#include <filesystem>
#include <sndfile.h>

namespace shone::core
{
    class AudioFile 
    {
    public:
        AudioFile(const std::filesystem::path& filePath);

        void writeToDisk(const std::filesystem::path& outputFilePath);

        const std::filesystem::path filePath() const;
        const std::vector<StereoFrame>& audioFrames() const;
        int sampleRate() const;

    private:
        std::pair<SNDFILE*, SF_INFO> openAudioFile(const std::filesystem::path& filePath, int mode);

    private:
        std::filesystem::path m_filePath;
        std::vector<StereoFrame> m_audioFrames;
        int m_sampleRate = 0;
    };
}