#include "shone/core/Downmix.hpp"
#include <stdexcept>
#include <algorithm>
#include <cassert>

namespace shone::core
{
    std::vector<float> Downmix::mixMonoToStereo(std::vector<float>& samples, int numFrames)
    {
        auto result = std::vector<float>(numFrames * 2);
        for (int i = 0; i < numFrames; ++i)
        {
            const auto sample = samples[i];
            result[i] = sample * 0.7071f;
            result[i + 1] = sample * 0.7071f;
        }

        return result;
    }

    std::vector<float> Downmix::mixStereoToMono(std::vector<float>& samples, int numFrames) 
    {
        auto result = std::vector<float>(numFrames);
        for (int i = 0; i < numFrames; ++i)
        {
            result[i] = samples[i * 2] * 0.7071f + samples[i * 2 + 1] * 0.7071f;
        }

        return result;
    }

    std::vector<float> Downmix::mixSurroundToStereo(std::vector<float>& samples, int numFrames) 
    {
        auto result = std::vector<float>(numFrames * 2);
        for (int i = 0; i < numFrames; ++i) 
        {
            result[i * 2] = samples[i * 6] + 0.7071f * samples[i * 6 + 2] + 0.7071f * samples[i * 6 + 3];
            result[i * 2 + 1] = samples[i * 6 + 1] + 0.7071f * samples[i * 6 + 2] + 0.7071f * samples[i * 6 + 4];
        }

        return result;
    }
}