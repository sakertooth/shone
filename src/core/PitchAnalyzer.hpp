#pragma once
#include "AudioFile.hpp"
#include "PitchSegment.hpp"
#include <aubio/aubio.h>

namespace shone::core
{
    class PitchAnalyzer
    {
    public:
        PitchAnalyzer(int sampleRate, int windowSize = 4096, int hopSize = 32);
        ~PitchAnalyzer();

        void analyzePitch(AudioFile& audioFile);
    private:
        std::vector<PitchSegment> m_pitchSegments;
        aubio_pitch_t* m_aubioPitch;
        fvec_t* m_inputBuffer;
        fvec_t* m_outputBuffer;
        int m_windowSize;
        int m_hopSize;
    };
}