#pragma once
#include "MusicalNote.hpp"
#include "StereoFrame.hpp"
#include <vector>

namespace shone::core
{
    class PitchSegment
    {
    public:
        PitchSegment(const std::vector<StereoFrame>& frames, MusicalNote::Note pitch, int sampleRate, int numChannels);
        
        void shiftPitch(int numSemitones);
        void append(const std::vector<StereoFrame>& newFrames);

        const std::vector<StereoFrame>& audioFrames() const;
        MusicalNote::Note pitch() const;
        int sampleRate() const;
        int numChannels() const;
    private:
        std::vector<StereoFrame> m_frames;
        MusicalNote::Note m_pitch;
        int m_sampleRate;
        int m_numChannels;
    };
}