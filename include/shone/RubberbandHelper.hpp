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
            int blockSize = 2048);
    
        static std::vector<float> deinterleaveAudio(const std::vector<AudioFrame>& audioFrames);
        static std::vector<AudioFrame> interleaveAudio(std::vector<float>& samples);
        static std::vector<float*> floatPtrBins(std::vector<float>& samples);
    };
}