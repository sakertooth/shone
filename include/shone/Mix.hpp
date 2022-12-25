#pragma once
#include "AudioFrame.hpp"
#include <vector>

namespace shone::core 
{
    class Mix 
    {
    public:
        static std::vector<AudioFrame> mixMonoToStereo(const std::vector<float>& data);
        static std::vector<AudioFrame> mixDownToStereo(const std::vector<float>& data, int numChannels);
        static std::vector<float> mixToMono(const std::vector<AudioFrame>& data);
    };
}