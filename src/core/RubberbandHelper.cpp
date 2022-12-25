#include "RubberbandHelper.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace shone::core 
{
    std::vector<AudioFrame> RubberbandHelper::executeRubberband(
        RubberBand::RubberBandStretcher& rubberBandStretcher, 
        const std::vector<AudioFrame>& audioFrames, 
        int blockSize)
    {
        auto deinterleavedAudio = deinterleaveAudio(audioFrames);
        auto deinterleavedAudioPtr = floatPtrBins(deinterleavedAudio);
        rubberBandStretcher.study(deinterleavedAudioPtr.data(), deinterleavedAudioPtr.size(), true);

        auto result = std::vector<float>{};
        auto framesProcessed = 0;

        do
        {
            const auto numFramesAvailable = rubberBandStretcher.available();
            if (numFramesAvailable == 0) 
            {
                //Process more data
                const auto numFramesRequired = rubberBandStretcher.getSamplesRequired();
                const auto numFramesLeft = deinterleavedAudioPtr.size() - framesProcessed;
                const auto numFramesToProcess = std::min(numFramesLeft, numFramesRequired);

                if (numFramesToProcess == 0) { continue; }

                const auto isFinalBlock = deinterleavedAudioPtr.data() + framesProcessed + numFramesToProcess 
                                        == deinterleavedAudioPtr.data() + deinterleavedAudioPtr.size();

                rubberBandStretcher.process(deinterleavedAudioPtr.data() + framesProcessed, numFramesToProcess, isFinalBlock);
                framesProcessed += numFramesToProcess;
            }
            else if (numFramesAvailable > 0) 
            {
                //Retrieve what is available and put into result
                auto outputFrames = std::vector<float>(numFramesAvailable * 2);
                auto outputFramesPtr = floatPtrBins(outputFrames);
                const auto numFramesRetrieved = rubberBandStretcher.retrieve(outputFramesPtr.data(), numFramesAvailable);

                if (numFramesRetrieved < static_cast<size_t>(numFramesAvailable)) 
                {
                    std::cerr << "RubberbandHelper::executeRubberband: " <<
                        numFramesRetrieved << " frames were retrieved, but " << 
                        numFramesAvailable << " frames were available\n";
                }

                result.insert(result.end(), outputFrames.begin(), outputFrames.end());
            }
        }
        while (rubberBandStretcher.available() != -1);
        return interleaveAudio(result);
    }

    std::vector<float> RubberbandHelper::deinterleaveAudio(const std::vector<AudioFrame>& audioFrames) 
    {
        auto leftBuffer = std::vector<float>(audioFrames.size());
        auto rightBuffer = std::vector<float>(audioFrames.size());

        for (size_t i = 0; i < audioFrames.size(); ++i) 
        {
            leftBuffer[i] = audioFrames[i][0];
            rightBuffer[i] = audioFrames[i][1];
        }
        
        auto result = std::vector<float>(audioFrames.size() * 2);
        result.insert(result.begin(), leftBuffer.begin(), leftBuffer.end());
        result.insert(result.begin() + leftBuffer.size(), rightBuffer.begin(), rightBuffer.end());

        return result;
    }

    std::vector<AudioFrame> RubberbandHelper::interleaveAudio(std::vector<float>& samples) 
    {
        const auto numSamples = samples.size();
        if (numSamples % 2 != 0) 
        {
            throw std::runtime_error{"RubberbandHelper::interleaveAudio: # of samples must be divisble by 2"};
        }

        auto leftBuffer = std::vector<float>(numSamples / 2);
        auto rightBuffer = std::vector<float>(numSamples / 2);

        std::copy(samples.begin(), samples.begin() + numSamples / 2, leftBuffer.begin());
        std::copy(samples.begin() + numSamples / 2, samples.end(), rightBuffer.begin());

        auto result = std::vector<AudioFrame>(numSamples / 2);
        for (size_t i = 0; i < result.size(); ++i) 
        {
            result[i] = AudioFrame{leftBuffer[i], rightBuffer[i]};
        }

        return result;
    }

    std::vector<float*> RubberbandHelper::floatPtrBins(std::vector<float>& samples) 
    {
        if (samples.size() % 2 != 0) 
        {
            std::cerr << "RubberbandHelper::floatPtrBins: # of samples should be divisble by 2\n";
        }

        auto result = std::vector<float*>(samples.size() / 2);
        for (size_t i = 0; i < result.size(); ++i) 
        {
            result[i] = &samples[2 * i];
        }

        return result;
    }
}