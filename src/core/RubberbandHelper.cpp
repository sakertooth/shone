#include "RubberbandHelper.hpp"
#include <algorithm>
#include <stdexcept>

namespace shone::core 
{
    std::vector<AudioFrame> RubberbandHelper::executeRubberband(
        RubberBand::RubberBandStretcher& rubberBandStretcher, 
        const std::vector<AudioFrame>& audioFrames, 
        int blockSize)
    {
        auto deinterleavedAudio = deinterleaveAudio(audioFrames);
        auto deinterleavedAudioPtr = std::vector<float*>(deinterleavedAudio.size() / 2);

        for (int i = 0; i < static_cast<int>(deinterleavedAudio.size()); i += 2) 
        {
            deinterleavedAudioPtr[i] = &deinterleavedAudio[i];
        }

        const auto [numBlocks, remainingFrames] = std::div(deinterleavedAudio.size(), blockSize);
        auto frameBlocks = std::vector<std::vector<float*>>(numBlocks);

        for (int i = 0; i < numBlocks; ++i) 
        {
            const auto start = deinterleavedAudioPtr.begin() + i * blockSize;
            const auto end = deinterleavedAudioPtr.begin() + i * blockSize + blockSize;
            const auto frameBlock = std::vector<float*>(start, end);
            rubberBandStretcher.study(frameBlock.data(), blockSize, i == numBlocks - 1);
            frameBlocks.push_back(std::move(frameBlock));
        }

        for (int i = 0; i < numBlocks; ++i) 
        {
            rubberBandStretcher.process(frameBlocks[i].data(), blockSize, i == numBlocks - 1);
        }

        auto result = std::vector<AudioFrame>();
        while (rubberBandStretcher.available() != 0) 
        {
            const auto retrievedFrameBlock = std::vector<float*>(blockSize);
            rubberBandStretcher.retrieve(retrievedFrameBlock.data(), blockSize);

            for (auto& frame : retrievedFrameBlock)
            {
                result.push_back(AudioFrame{frame[0], frame[1]});     
            }
        }

        return result;
    }

    std::vector<float> RubberbandHelper::deinterleaveAudio(const std::vector<AudioFrame>& audioFrames) 
    {
        auto leftBuffer = std::vector<float>(audioFrames.size() / 2);
        auto rightBuffer = std::vector<float>(audioFrames.size() / 2);
        auto result = std::vector<float>(audioFrames.size());

        for (auto& frame : audioFrames)
        {
            leftBuffer.push_back(frame[0]);
            rightBuffer.push_back(frame[1]);
        }
        
        std::copy(leftBuffer.begin(), leftBuffer.end(), result.begin());
        std::copy(rightBuffer.begin(), rightBuffer.end(), result.begin() + leftBuffer.size());
        return result;
    }
}