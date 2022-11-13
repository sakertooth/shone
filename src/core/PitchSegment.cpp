#include "PitchSegment.hpp"
#include <rubberband/RubberBandStretcher.h>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace shone::core 
{
    PitchSegment::PitchSegment(const std::vector<AudioFrame>& frames, int sampleRate, int numChannels) 
    : m_frames(frames),
    m_sampleRate(sampleRate),
    m_numChannels(numChannels) {}

    void PitchSegment::shiftPitch(int numSemitones)
    {
        auto rubberBandStretcher = RubberBand::RubberBandStretcher{
            static_cast<size_t>(m_sampleRate), static_cast<size_t>(m_numChannels)};

        rubberBandStretcher.setPitchScale(std::pow(2, numSemitones / 12.0f));

        auto input = std::vector<const float*>(m_frames.size());
        auto output = std::vector<float*>(m_frames.size());

        std::transform(m_frames.begin(), m_frames.end(), input.begin(), [&](auto frame)
        {
            return frame.samples().data();
        });
        
        rubberBandStretcher.study(input.data(), input.size(), true);
        rubberBandStretcher.process(input.data(), input.size(), true);
        auto samplesRetrieved = rubberBandStretcher.retrieve(output.data(), output.size());

        if (samplesRetrieved != m_frames.size()) 
        {
            std::cerr << "Could not retrieve all audio frames from pitch shift.\n";
        }

        m_frames.clear();
        for (const auto& outputFrame : output) 
        {
            m_frames.emplace_back(outputFrame, outputFrame + m_numChannels, m_numChannels);
        }
    }

    void PitchSegment::append(const std::vector<AudioFrame>& newFrames) 
    {
        m_frames.insert(m_frames.end(), newFrames.begin(), newFrames.end());
    }

    const std::vector<AudioFrame>& PitchSegment::audioFrames() const 
    {
        return m_frames;
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