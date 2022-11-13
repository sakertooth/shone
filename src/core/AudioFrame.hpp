#pragma once

#include <vector>

namespace shone::core 
{
    class AudioFrame 
    {
    public:
        AudioFrame(float* begin, float* end, int numChannels);

        int numChannels() const;
        const std::vector<float>& samples() const;
    private:
        int m_numChannels;
        std::vector<float> m_samples;
    };
} 