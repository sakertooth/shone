#include "AudioFile.hpp"
#include <iostream>
#include <numeric>

namespace shone::core
{
    AudioFile::AudioFile(const std::filesystem::path& filepath) 
    {
        auto nativeFilePath = filepath.c_str();
        SNDFILE* audioFile = nullptr;
        SF_INFO audioInfo;

        if (std::is_same_v<decltype(audioFile), char>) 
        {
            audioFile = sf_open(nativeFilePath, SFM_READ, &audioInfo);
        }
        #ifdef WIN32
        else if (std::is_same_v<decltype(nativeFilePath), wchar_t>) 
        {
            audioFile = sf_wchar_open(nativeFilePath, SFM_READ, &audioInfo);
        }
        #endif
        else 
        {
            throw std::domain_error{"Unknown/unsupported file path.\n"};
        }
        
        auto samples = std::vector<float>(audioInfo.frames * audioInfo.channels);
        auto samples_read = sf_read_float(audioFile, samples.data(), audioInfo.frames * audioInfo.channels);

        if (samples_read != static_cast<size_t>(samples.size())) 
        {
            throw std::runtime_error{"Could not read the required number of samples from the audio file."};
        }

        auto audioFrames = std::vector<AudioFrame>{};
        audioFrames.reserve(audioInfo.frames);
        
        for (int i = 0; i < samples.size(); i += audioInfo.channels)
        {
            audioFrames.emplace_back(&samples[i], &samples[i + audioInfo.channels], audioInfo.channels);
        }

        m_sampleRate = audioInfo.samplerate;
        m_numChannels = audioInfo.channels;
    }

    std::vector<float> AudioFile::mixToMono()
    {
        auto monoSignal = std::vector<float>(m_audioFrames.size());
        for (const auto& audioFrame : m_audioFrames)
        {
            const auto& samples = audioFrame.samples();
            auto frameAverage = std::accumulate(samples.begin(), samples.end(), 0) / samples.size();
            monoSignal.push_back(frameAverage);
        }

        return monoSignal;
    }

    const std::vector<AudioFrame> AudioFile::audioFrames() const 
    {
        return m_audioFrames;
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