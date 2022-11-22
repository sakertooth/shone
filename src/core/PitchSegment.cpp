#include <rubberband/RubberBandStretcher.h>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "PitchSegment.hpp"
#include "RubberbandWrapper.hpp"

namespace shone::core 
{
    PitchSegment::PitchSegment(const std::vector<AudioFrame>& frames, MusicalNote::Note pitch, int sampleRate, int numChannels) 
    : m_frames(frames),
    m_pitch(pitch),
    m_sampleRate(sampleRate),
    m_numChannels(numChannels) {}

    void PitchSegment::shiftPitch(int numSemitones)
    {
        auto rubberBandStretcher = RubberBand::RubberBandStretcher{
            static_cast<size_t>(m_sampleRate), static_cast<size_t>(m_numChannels)};
        rubberBandStretcher.setPitchScale(std::pow(2, numSemitones / 12.0f));
        m_frames = RubberbandWrapper::executeRubberband(rubberBandStretcher, m_frames, m_sampleRate, m_numChannels);
    }

    void PitchSegment::append(const std::vector<AudioFrame>& newFrames) 
    {
        m_frames.insert(m_frames.end(), newFrames.begin(), newFrames.end());
    }

    const std::vector<AudioFrame>& PitchSegment::audioFrames() const 
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