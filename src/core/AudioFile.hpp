#pragma once
#include "AudioFrame.hpp"

#include <vector>
#include <filesystem>
#include <sndfile.h>

namespace shone::core
{
    class AudioFile
    {
    public:
        AudioFile(const std::filesystem::path& filepath);
        
        std::vector<float> mixToMono();
        void shiftBPM(int currentBPM, int newBPM);
        void shiftPitch(int numCents);
        void writeToDisk(const std::filesystem::path& outputFilePath);
        
        const std::vector<AudioFrame>& audioFrames() const;
        int sampleRate() const;
        int numChannels() const;
    private:
        std::filesystem::path m_filePath;
        std::vector<AudioFrame> m_audioFrames;
        int m_sampleRate;
        int m_numChannels;
    };
}