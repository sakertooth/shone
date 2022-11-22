#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

#include "AudioFile.hpp"
#include "SndFileHelper.hpp"
#include "RubberbandHelper.hpp"

namespace shone::core
{
    AudioFile::AudioFile(const std::filesystem::path& filepath) : m_filePath(filepath)
    {
        auto [audioFile, audioInfo] = SndFileHelper::open(filepath, SFM_READ);
        
        auto samples = std::vector<float>(audioInfo.frames * audioInfo.channels);
        auto samples_read = sf_read_float(audioFile.get(), samples.data(), audioInfo.frames * audioInfo.channels);

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

        m_audioFrames = audioFrames;
        m_sampleRate = audioInfo.samplerate;
        m_numChannels = audioInfo.channels;
    }

    std::vector<float> AudioFile::mixToMono()
    {
        auto monoSignal = std::vector<float>{};
        for (const auto& audioFrame : m_audioFrames)
        {
            const auto& samples = audioFrame.samples();
            auto frameAverage = std::accumulate(samples.begin(), samples.end(), 0.0f) / samples.size();
            monoSignal.push_back(frameAverage);
        }

        return monoSignal;
    }

    void AudioFile::shiftBPM(int currentBPM, int newBPM) 
    {
        if (currentBPM == newBPM) { return; }
        if (newBPM == 0) { throw std::logic_error("AudioFile.cpp: New BPM cannot be 0."); }

        auto rubberBandStretcher = RubberBand::RubberBandStretcher{m_sampleRate, m_numChannels};
        rubberBandStretcher.setTimeRatio(currentBPM / newBPM);
        m_audioFrames = RubberbandHelper::executeRubberband(rubberBandStretcher, m_audioFrames, m_sampleRate, m_numChannels);
    }
    
    void AudioFile::shiftPitch(int numCents) 
    {
        if (numCents == 0) { return; }
        
        auto rubberBandStretcher = RubberBand::RubberBandStretcher{m_sampleRate, m_numChannels};
        rubberBandStretcher.setPitchScale(std::pow(2.0, (numCents / 100.0f) / 12.0f));
        m_audioFrames = RubberbandHelper::executeRubberband(rubberBandStretcher, m_audioFrames, m_sampleRate, m_numChannels);
    }

    void AudioFile::writeToDisk(const std::filesystem::path& outputFilePath) 
    {
        auto [audioFile, audioInfo] = SndFileHelper::open(outputFilePath, SFM_WRITE);
        for (auto& frame : m_audioFrames) 
        {
            sf_write_float(audioFile.get(), frame.samples().data(), frame.samples().size());
        }
    }

    const std::vector<AudioFrame>& AudioFile::audioFrames() const 
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