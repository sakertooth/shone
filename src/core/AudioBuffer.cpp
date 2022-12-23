#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

#include "AudioBuffer.hpp"
#include "Defaults.hpp"
#include "Mix.hpp"

namespace shone::core
{
    AudioBuffer::AudioBuffer(const std::size_t size) : 
        m_audioFrames(size),
        m_originalSampleRate(DEFAULT_SAMPLE_RATE),
        m_originalNumChannels(2) {}

    AudioBuffer::AudioBuffer(const std::filesystem::path& filePath) : m_filePath(filePath)
    {
        auto audioInfo = SF_INFO{};
        auto audioFile = openAudioHandle(filePath, audioInfo, SFM_READ);
        auto sampleData = std::vector<float>(audioInfo.frames * audioInfo.channels);
        auto samplesRead = sf_read_float(audioFile, sampleData.data(), sampleData.size());

        if (samplesRead != static_cast<int>(sampleData.size())) 
        {
            throw std::runtime_error{"Could not read all required samples in audio file"};
        }
        
        if (audioInfo.channels < 2) 
        {
            m_audioFrames = Mix::mixMonoToStereo(sampleData);
        }
        else if (audioInfo.channels > 2)
        {
            m_audioFrames = Mix::mixDownToStereo(sampleData, audioInfo.channels);
        }
        else 
        {
            m_audioFrames = std::vector<AudioFrame>(audioInfo.frames);
            for (size_t i = 0; i < sampleData.size(); i += 2)
            {
                m_audioFrames[i] = AudioFrame{sampleData[i], sampleData[i + 1]};
            }
        }

        if (m_originalSampleRate != DEFAULT_SAMPLE_RATE) 
        {
            //TODO: Resampling to match sample rate of application..
        }

        m_originalSampleRate = audioInfo.samplerate;
        m_originalNumChannels = audioInfo.channels;
        sf_close(audioFile);
    }

    AudioBuffer::AudioBuffer(const std::vector<AudioFrame>& audioFrames) : 
        m_audioFrames(audioFrames),
        m_originalSampleRate(DEFAULT_SAMPLE_RATE),
        m_originalNumChannels(2)
    {}

    void AudioBuffer::writeToDisk(const std::filesystem::path& path, int format) const
    {
        auto audioInfo = SF_INFO{};
        audioInfo.format = format;
        audioInfo.channels = 2;
        audioInfo.samplerate = m_originalSampleRate;
        
        auto audioFile = openAudioHandle(path, audioInfo, SFM_WRITE);
        sf_writef_float(audioFile, m_audioFrames.data()->data(),  m_audioFrames.size());
        sf_close(audioFile);
    }

    const std::optional<std::filesystem::path> AudioBuffer::filePath() const 
    {
        return m_filePath;
    }
    
    SNDFILE* AudioBuffer::openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode) const
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
            throw std::domain_error{"Unknown/unsupported file path.\n"};
        }

        if (sf_error(audioFile))
        {
            throw std::runtime_error{std::string{"SndFile error in AudioBuffer::openAudioBuffer: "} + sf_strerror(audioFile)};
        }

        return audioFile;
    }

    const std::vector<AudioFrame>& AudioBuffer::audioFrames() const 
    {
        return m_audioFrames;
    }
    
    int AudioBuffer::originalSampleRate() const 
    {
        return m_originalSampleRate;
    }

    int AudioBuffer::originalNumChannels() const 
    {
        return m_originalNumChannels;
    }
}
