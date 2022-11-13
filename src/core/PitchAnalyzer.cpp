#include "PitchAnalyzer.hpp"
#include <aubio/aubio.h>

namespace shone::core
{
    PitchAnalyzer::PitchAnalyzer(int sampleRate, int windowSize, int hopSize) :
        m_aubioPitch(new_aubio_pitch("default", windowSize, hopSize, sampleRate)),
        m_inputBuffer(new_fvec(hopSize)),
        m_outputBuffer(new_fvec(1)),
        m_windowSize(windowSize),
        m_hopSize(hopSize) {}

    PitchAnalyzer::~PitchAnalyzer() 
    {
        del_aubio_pitch(m_aubioPitch);
        del_fvec(m_inputBuffer);
        del_fvec(m_outputBuffer);
    }

    void PitchAnalyzer::analyzePitch(AudioFile& audioFile) 
    {
        m_pitchSegments.clear();

        auto monoSignal = audioFile.mixToMono();
        for (int i = 0; i < monoSignal.size(); ++i) 
        {
            if (i % m_hopSize == 0) 
            {
                aubio_pitch_do(m_aubioPitch, m_inputBuffer, m_outputBuffer);
                auto frequency = fvec_get_sample(m_outputBuffer, 0);
                //...
                fvec_zeros(m_inputBuffer);
            }
            else 
            {
                fvec_set_sample(m_inputBuffer, monoSignal[i], i);
            }
        }
    }

}