#include "shone/AudioFile.hpp"
#include "shone/SndFileHelper.hpp"

namespace shone::core 
{
    AudioFile::AudioFile(const std::filesystem::path& filePath) : m_filePath(filePath) 
    {
        if (!std::filesystem::exists(filePath)) 
        {
            throw std::runtime_error{"AudioFile::AudioFile: filePath does not exist"};
        }

        auto audioInfo = SF_INFO{};
        auto audioHandle = SndFileHelper::openAudioHandle(filePath, audioInfo, SFM_READ);
        
        m_samples = std::vector<float>(audioInfo.frames * audioInfo.channels);
        const size_t samplesRead = sf_read_float(audioHandle, m_samples.data(), m_samples.size());

        if (samplesRead != m_samples.size()) 
        {
            throw std::runtime_error{"AudioFile::AudioFile: # of samples read does not match the expected amount."};
        }

        m_numFrames = audioInfo.frames;
        m_sampleRate = audioInfo.samplerate;
        m_numChannels = audioInfo.channels;
    }

    const std::vector<float>& AudioFile::samples() const 
    {
        return m_samples;
    }

    const std::filesystem::path& AudioFile::filePath() const 
    {
        return m_filePath;
    }

    int AudioFile::numFrames() const 
    {
        return m_numFrames;
    }

    int AudioFile::sampleRate() const 
    {
        return m_sampleRate;
    }

    int AudioFile::numChannels() const 
    {
        return m_numChannels;
    }
}