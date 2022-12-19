#include "RubberbandHelper.hpp"
#include <algorithm>
#include <stdexcept>

namespace shone::core 
{
    std::vector<AudioFrame> RubberbandHelper::executeRubberband(
        RubberBand::RubberBandStretcher& rubberBandStretcher, 
        const std::vector<AudioFrame>& audioFrames, 
        int sampleRate, int numChannels) 
    {
        auto input = std::vector<const float*>{audioFrames.size()};
        auto output = std::vector<float*>{audioFrames.size()};

        std::transform(audioFrames.begin(), audioFrames.end(), input.begin(), [](auto& audioFrame)
        {
            return audioFrame.samples().data();
        });

        rubberBandStretcher.study(input.data(), input.size(), true);
        rubberBandStretcher.process(input.data(), input.size(), true);
        if (rubberBandStretcher.available() != audioFrames.size()) 
        {
            throw std::runtime_error{"RubberbandHelper.cpp: Number of available frames does not match the original number of frames."};
            
        }

        rubberBandStretcher.retrieve(output.data(), output.size());

        auto frames = std::vector<AudioFrame>{};
        for (auto& frame : output) 
        {
            frames.emplace_back(frame, frame + numChannels, numChannels);
        }

        return frames;
    }
}