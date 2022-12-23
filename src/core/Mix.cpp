#include "Mix.hpp"
#include <stdexcept>

namespace shone::core 
{
    std::vector<AudioFrame> Mix::mixMonoToStereo(const std::vector<float>& data) 
    {
        auto result = std::vector<AudioFrame>(data.size());
        for (size_t i = 0; i < result.size(); ++i) 
        {
            result[i] = AudioFrame{data[i], data[i]};
        }

        return result;
    }

    std::vector<AudioFrame> Mix::mixDownToStereo(const std::vector<float>& data, int numChannels) 
    {
        if (numChannels <= 2) { throw std::runtime_error{"Cannot mixdown signal: numChannels <= 2"}; }
        
        auto result = std::vector<AudioFrame>(data.size() / numChannels);
        for (int i = 0; i < result.size(); i += numChannels) 
        {
            auto frame = std::vector<float>(numChannels);
            std::copy(data.begin() + i, data.begin() + i + numChannels, frame.begin());

            const auto left = frame[0];
            const auto right = frame[1];
            const auto center = frame[2];

            // Assume if it has at least 5 channels, then it has 2 surround channels
            const auto surroundLeft = numChannels >= 5 ? frame[3] : 0;
            const auto surroundRight = numChannels >= 5 ? frame[4] : 0;

            // Coefficients from the Digital Audio Compression (AC-4) standard
            const auto stereoLeft = left + 0.707f * center - 0.707f * surroundLeft - 0.707f * surroundRight;
            const auto stereoRight = right + 0.707f * center - 0.707f * surroundLeft - 0.707f * surroundRight;
            
            result.push_back(AudioFrame{stereoLeft, stereoRight});
        }

        return result;
    }

    std::vector<float> Mix::mixToMono(const std::vector<AudioFrame>& data) 
    {
        auto result = std::vector<float>(data.size());
        for (auto frame : data) 
        {
            result.push_back((frame[0] + frame[1]) / 2);
        }

        return result;
    }
}