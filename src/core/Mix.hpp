#pragma once
#include "StereoFrame.hpp"
#include <vector>

namespace shone::core 
{
    class Mix 
    {
    public:
        static std::vector<StereoFrame> mixMonoToStereo(const std::vector<float>& data);
        static std::vector<StereoFrame> mixDownToStereo(const std::vector<float>& data, int numChannels);
        static std::vector<float> mixToMono(const std::vector<StereoFrame>& data);
    };
}