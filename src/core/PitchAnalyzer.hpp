#pragma once
#include "AudioBuffer.hpp"
#include "PitchSegment.hpp"
#include <aubio/aubio.h>

namespace shone::core
{
    class PitchAnalyzer
    {
    public:
        PitchAnalyzer(int sampleRate, float referenceFrequency = 440.0f, int windowSize = 2048, int hopSize = 256);
        ~PitchAnalyzer();

        std::vector<PitchSegment> analyzePitch(AudioBuffer& audioFile);
    private:
        aubio_pitch_t* m_aubioPitch;
        fvec_t* m_inputBuffer;
        fvec_t* m_outputBuffer;
        float m_referenceFrequency;
        int m_windowSize;
        int m_hopSize;
        int m_sampleRate;
    };
}