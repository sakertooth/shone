#pragma once
#include <array>
#include <cstddef>

namespace shone::core 
{
    /**
     * @brief 
     * Downmixing support for AudioBuffer.
     * Only supports downmixing to stereo and mono for now.
     */
    class Downmix 
    {
    public:
        // The CoefficientMatrix follows this order
        enum class InputChannels 
        {
            Left,
            Right,
            Center,
            SurroundLeft,
            SurroundRight,
            BackLeft,
            BackRight,
            MaxNumChannels
        };

        template<size_t N>
        using CoefficientMatrix = std::array<std::array<float, static_cast<size_t>(InputChannels::MaxNumChannels)>, N>;
        using CoefficientArray = std::array<float, static_cast<size_t>(InputChannels::MaxNumChannels)>;

        static const CoefficientArray& monoCoefficients();
        static const CoefficientMatrix<2>& stereoCoefficients();
    };
}