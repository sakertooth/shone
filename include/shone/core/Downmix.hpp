#pragma once
#include <vector>
#include <array>

namespace shone::core
{
    /**
     * @brief Support for downmixing using AudioBuffer.
     *
     */
    class Downmix
    {
    public:
        /**
         * @brief Upmix a mono signal with numFrames frames into a stereo signal.
         * 
         * @param samples 
         * @param numFrames 
         * @return std::vector<float> 
         */
        static std::vector<float> mixMonoToStereo(std::vector<float>& samples, int numFrames);

        /**
         * @brief Downmix a stereo signal with numFrames frames into a mono signal.
         * 
         * @param samples 
         * @return std::vector<float> 
         */
        static std::vector<float> mixStereoToMono(std::vector<float>& samples, int numFrames);

        /**
         * @brief Downmix a 5.1 surround signal with numFrames frames into a stereo signal.
         * 
         * @param samples 
         * @return std::vector<float> 
         */
        static std::vector<float> mixSurroundToStereo(std::vector<float>& samples, int numFrames);
    };
}
