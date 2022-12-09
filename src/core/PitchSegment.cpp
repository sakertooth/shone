#include "PitchSegment.hpp"

#include <rubberband/RubberBandStretcher.h>
#include <cmath>
#include <algorithm>
#include <iostream>
namespace shone::core 
{
    PitchSegment::PitchSegment(const std::vector<StereoFrame>& frames, MusicalNote::Note pitch, int sampleRate, int numChannels) 
    : m_frames(frames),
    m_pitch(pitch),
    m_sampleRate(sampleRate),
    m_numChannels(numChannels) {}

    void PitchSegment::shiftPitch(int numSemitones)
    {
       // TODO
    }

    void PitchSegment::append(const std::vector<StereoFrame>& newFrames) 
    {
        m_frames.insert(m_frames.end(), newFrames.begin(), newFrames.end());
    }

    const std::vector<StereoFrame>& PitchSegment::audioFrames() const 
    {
        return m_frames;
    }

    MusicalNote::Note PitchSegment::pitch() const 
    {
        return m_pitch;
    }

    int PitchSegment::sampleRate() const 
    {
        return m_sampleRate;
    }

    int PitchSegment::numChannels() const 
    {
        return m_numChannels;
    }
}