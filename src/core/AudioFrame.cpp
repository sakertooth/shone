#include <vector>
#include <cassert>
#include "AudioFrame.hpp"

namespace shone::core 
{
    AudioFrame::AudioFrame(float* begin, float* end, int numChannels) : m_samples(begin, end), m_numChannels(numChannels) 
    {
        assert(m_samples.size() == m_numChannels);
    }

    int AudioFrame::numChannels() const 
    {
        return m_numChannels;
    }

    const std::vector<float>& AudioFrame::samples() const 
    {
        return m_samples;
    }
} 