#pragma once
#include "AudioFile.hpp"
#include "AudioBuffer.hpp"
#include "rubberband/RubberBandStretcher.h"

#include <filesystem>
#include <samplerate.h>

namespace shone::core
{
    class AudioBuffer
    {
    public:
        AudioBuffer(const AudioFile& audioFile, int sampleRate, int numChannels);
        AudioBuffer(const std::vector<float>& samples, int sampleRate, int numChannels);
        AudioBuffer(size_t size, int sampleRate, int numChannels);

        void applyStretcher(const RubberBand::RubberBandStretcher& stretcher, int from, int to);
        void writeToDisk(std::filesystem::path& filePath, int mode);
        void resample(int newSampleRate, int interpolatonMode = SRC_SINC_MEDIUM_QUALITY);
        void mix(int newNumChannels);

        const std::vector<float>& samples() const;
        int sampleRate() const;
        int numChannels() const;
        int numFrames() const;
    private:
        std::vector<float> m_samples;
        int m_sampleRate = 0;
        int m_numChannels = 0;
        int m_numFrames = 0;
    };
}