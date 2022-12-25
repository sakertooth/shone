#pragma once
#include <vector>
#include <filesystem>
#include <optional>
#include <sndfile.h>

namespace shone::core
{
    class AudioFile 
    {
    public:
        AudioFile(const std::filesystem::path& filePath);
        const std::vector<float>& samples() const;
        const std::filesystem::path& filePath() const;
        int sampleRate() const;
        int numChannels() const;
    private:
        std::vector<float> m_samples;
        std::filesystem::path m_filePath;
        int m_sampleRate = 0;
        int m_numChannels = 0;
    private:
        SNDFILE* openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode) const;
    };
}