#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

#include "AudioFile.hpp"
#include "Mix.hpp"

namespace shone::core
{
    AudioFile::AudioFile(const std::filesystem::path& filePath) : m_filePath(filePath)
    {
        auto [audioFile, audioInfo] = openAudioFile(filePath, SFM_READ);
        auto sampleData = std::vector<float>(audioInfo.frames * audioInfo.channels);
        auto samplesRead = sf_read_float(audioFile, sampleData.data(), sampleData.size());

        if (samplesRead != sampleData.size()) 
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
            m_audioFrames = std::vector<StereoFrame>(audioInfo.frames);
            std::copy(sampleData.begin(), sampleData.end(), m_audioFrames.begin()->data());
        }
                
        sf_close(audioFile);
    }

    void AudioFile::writeToDisk(const std::filesystem::path& outputFilePath) 
    {
        auto [audioFile, audioInfo] = openAudioFile(outputFilePath, SFM_WRITE);
        sf_writef_float(audioFile, m_audioFrames.data()->data(),  m_audioFrames.size());
        sf_write_sync(audioFile);
        sf_close(audioFile);
    }

    const std::filesystem::path AudioFile::filePath() const 
    {
        return m_filePath;
    }

    const std::vector<StereoFrame>& AudioFile::audioFrames() const 
    {
        return m_audioFrames;
    }
    
    int AudioFile::sampleRate() const 
    {
        return m_sampleRate;
    }

    std::pair<SNDFILE*, SF_INFO> AudioFile::openAudioFile(const std::filesystem::path& filePath, int mode) 
    {
        auto nativeFilePath = filePath.c_str();
        SNDFILE* audioFile = nullptr;
        auto audioInfo = SF_INFO{};

        if (std::is_same_v<std::filesystem::path::value_type, char>) 
        {
            audioFile = sf_open(nativeFilePath, mode, &audioInfo);
        }
        #ifdef WIN32
        else if (std::is_same_v<std::filesystem::path::value_type, wchar_t>) 
        {
            audioFile = sf_wchar_open(nativeFilePath, mode, &audioInfo);
        }
        #endif
        else 
        {
            throw std::domain_error{"Unknown/unsupported file path.\n"};
        }

        if (sf_error(audioFile)) 
        {
            throw std::runtime_error{std::string{"SndFile error in AudioFile::openAudioFile: "} + sf_strerror(audioFile)};
        }

        return {audioFile, audioInfo};
    }
}