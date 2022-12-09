#include <aubio/aubio.h>
#include <cmath>
#include <iostream>

#include "PitchAnalyzer.hpp"
#include "MusicalNote.hpp"
#include "Mix.hpp"

namespace shone::core
{
    PitchAnalyzer::PitchAnalyzer(int sampleRate, float referenceFrequency, int windowSize, int hopSize) :
        m_aubioPitch(new_aubio_pitch("default", windowSize, hopSize, sampleRate)),
        m_inputBuffer(new_fvec(hopSize)),
        m_outputBuffer(new_fvec(1)),
        m_referenceFrequency(referenceFrequency),
        m_windowSize(windowSize),
        m_hopSize(hopSize) {}

    PitchAnalyzer::~PitchAnalyzer() 
    {
        del_aubio_pitch(m_aubioPitch);
        del_fvec(m_inputBuffer);
        del_fvec(m_outputBuffer);
    }

    std::vector<PitchSegment> PitchAnalyzer::analyzePitch(AudioFile& audioFile) 
    {
        std::vector<PitchSegment> pitchSegments{};
        const auto monoSignal = Mix::mixToMono(audioFile.audioFrames());
        const auto& audioFrames = audioFile.audioFrames();
        const auto totalHops = monoSignal.size() / m_hopSize;
        const auto sampleRate = audioFile.sampleRate();
        const auto numChannels = 2;

        for (int i = 0; i < totalHops; ++i)
        {
            for (int sampleIndex = 0; sampleIndex < m_hopSize; ++sampleIndex) 
            {
                fvec_set_sample(m_inputBuffer, monoSignal[m_hopSize * i + sampleIndex], sampleIndex);
            }

            aubio_pitch_do(m_aubioPitch, m_inputBuffer, m_outputBuffer);

            auto frequency = fvec_get_sample(m_outputBuffer, 0);
            if (frequency == 0) { continue; }

            auto pitchFrames = std::vector<StereoFrame>{audioFrames[m_hopSize * i], audioFrames[m_hopSize * i + m_hopSize]};
            auto musicalNote = MusicalNote{frequency};
            
            //Can we merge this segment with the most recent one? (WIP, confusion with cent differences between segments)
            if (!pitchSegments.empty() && pitchSegments.back().pitch() == musicalNote.note()) 
            {
                pitchSegments.back().append(pitchFrames);
            }
            else
            {
                pitchSegments.emplace_back(pitchFrames, musicalNote.note(), sampleRate, numChannels);
            }
        }

        return pitchSegments;
    }

}