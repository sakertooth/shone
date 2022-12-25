#pragma once
#include "AudioFrame.hpp"
#include <vector>
#include <filesystem>
#include <optional>
#include <sndfile.h>

namespace shone::core
{
    class AudioBuffer
    {
    public:
        AudioBuffer(const std::filesystem::path& filePath, int sampleRate);
        AudioBuffer(const std::vector<AudioFrame>& frames, int sampleRate);
        AudioBuffer(std::size_t size, int sampleRate);

        void writeToDisk(const std::filesystem::path& path, int format) const;

        const std::optional<std::filesystem::path> filePath() const;
        const std::vector<AudioFrame>& audioFrames() const;
        int sampleRate() const;
        int originalSampleRate() const;
        int originalNumChannels() const;
    private:
        std::optional<std::filesystem::path> m_filePath;
        std::vector<AudioFrame> m_audioFrames;
        int m_sampleRate = 0;
        int m_originalSampleRate = 0;
        int m_originalNumChannels = 0;
    private:
        SNDFILE* openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode) const;
    };
}