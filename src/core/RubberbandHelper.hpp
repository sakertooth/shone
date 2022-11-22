#pragma once
#include "rubberband/RubberBandStretcher.h"
#include "AudioFrame.hpp"

namespace shone::core 
{
    class RubberbandHelper 
    {
    public:
        static std::vector<AudioFrame> executeRubberband(
            RubberBand::RubberBandStretcher& rubberBandStretcher, 
            const std::vector<AudioFrame>& audioFrames, 
            int sampleRate, int numChannels);
    };
}