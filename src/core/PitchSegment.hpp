#pragma once
#include "AudioFrame.hpp"
#include <vector>

namespace shone::core
{
    class PitchSegment 
    {
    public:
        PitchSegment(const std::vector<AudioFrame>& frames, int sampleRate, int numChannels);
        
        void shiftPitch(int numSemitones);
        void append(const std::vector<AudioFrame>& newFrames);

        const std::vector<AudioFrame>& audioFrames() const;
        int sampleRate() const;
        int numChannels() const;
    private:
        std::vector<AudioFrame> m_frames;
        int m_sampleRate;
        int m_numChannels;
    };
}