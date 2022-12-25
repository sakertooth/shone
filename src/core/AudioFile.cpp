#include "shone/AudioFile.hpp"

namespace shone::core 
{
    AudioFile::AudioFile(const std::filesystem::path& filePath) : m_filePath(filePath) 
    {
        if (!std::filesystem::exists(filePath)) 
        {
            throw std::runtime_error{"AudioFile::AudioFile: filePath does not exist"};
        }

        auto audioInfo = SF_INFO{};
        auto audioHandle = openAudioHandle(filePath, audioInfo, SFM_READ);
        
        m_samples = std::vector<float>(audioInfo.frames * audioInfo.channels);
        const size_t samplesRead = sf_read_float(audioHandle, m_samples.data(), m_samples.size());

        if (samplesRead != m_samples.size()) 
        {
            throw std::runtime_error{"AudioFile::AudioFile: # of samples read does not match the expected amount."};
        }

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

    int AudioFile::sampleRate() const 
    {
        return m_sampleRate;
    }

    int AudioFile::numChannels() const 
    {
        return m_numChannels;
    }

    SNDFILE* AudioFile::openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode) const 
    {
        auto nativeFilePath = filePath.c_str();
        SNDFILE* audioFile = nullptr;
        
        if (std::is_same_v<std::filesystem::path::value_type, char>) 
        {
            audioFile = sf_open(nativeFilePath, mode, &info);
        }
        #ifdef WIN32
        else if (std::is_same_v<std::filesystem::path::value_type, wchar_t>) 
        {
            audioFile = sf_wchar_open(nativeFilePath, mode, &info);
        }
        #endif
        else 
        {
            throw std::domain_error{"AudioFile::AudioFile: Unknown/unsupported file path.\n"};
        }

        if (sf_error(audioFile))
        {
            throw std::runtime_error{std::string{"AudioFile::AudioFile: SndFile error, "} + sf_strerror(audioFile)};
        }

        return audioFile;
    }
}