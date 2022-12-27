#include "shone/AudioBuffer.hpp"
#include "shone/AudioFile.hpp"
#include "shone/SndFileHelper.hpp"
#include "shone/Downmix.hpp"

#include <iostream>
#include <cassert>
#include <numeric>

namespace shone::core
{

    AudioBuffer::AudioBuffer(const AudioFile& audioFile, int sampleRate, int numChannels)
        : m_samples(audioFile.samples())
        , m_sampleRate(audioFile.sampleRate())
        , m_numChannels(audioFile.numChannels())
    {
        if (sampleRate != audioFile.sampleRate())
        {
            resample(sampleRate);
        }

        if (numChannels != audioFile.numChannels())
        {
            mix(numChannels);
        }
    }

    AudioBuffer::AudioBuffer(const std::vector<float>& samples, int sampleRate, int numChannels)
        : m_samples(samples)
        , m_sampleRate(sampleRate)
        , m_numChannels(numChannels)
    {}

    AudioBuffer::AudioBuffer(size_t size, int sampleRate, int numChannels)
        : m_samples(size)
        , m_sampleRate(sampleRate)
        , m_numChannels(numChannels)
    {}

    void AudioBuffer::writeToDisk(std::filesystem::path& filePath, int format)
    {
        auto audioInfo = SF_INFO{};
        auto audioHandle = SndFileHelper::openAudioHandle(filePath, audioInfo, SFM_WRITE);

        audioInfo.samplerate = m_sampleRate;
        audioInfo.channels = m_numChannels;
        audioInfo.format = format;

        sf_write_float(audioHandle, m_samples.data(), m_samples.size());
        sf_close(audioHandle);
    }

    void AudioBuffer::resample(int newSampleRate, int interpolationMode)
    {
        auto resampledData = std::vector<float>(m_samples.size());
        auto data = SRC_DATA{};
        data.data_in = m_samples.data();
        data.input_frames = m_samples.size();
        data.data_out = resampledData.data();
        data.output_frames = resampledData.size();
        data.src_ratio = static_cast<float>(newSampleRate) / m_sampleRate;

        auto error = src_simple(&data, interpolationMode, m_numChannels);
        if (error)
        {
            std::cerr << "Failed to resample AudioBuffer: " << src_strerror(error) << '\n';
            return;
        }

        m_samples = resampledData;
        m_sampleRate = newSampleRate;
    }

    void AudioBuffer::mix(int newNumChannels)
    {
        if (newNumChannels <= 0 || m_numChannels == newNumChannels)
        {
            std::cerr << "Failed to mix AudioBuffer: invalid # of channels\n";
            return;
        }

        // Only support upmixing/downmixing for mono/stereo for now
        if (!(newNumChannels == 1 || newNumChannels == 2))
        {
            std::cerr << "Failed to mix AudioBuffer: Unsupported upmix/downmix\n";
            return;
        }

        auto result = std::vector<float>(numFrames() * newNumChannels);
        for (int frameIndex = 0; frameIndex < numFrames(); ++frameIndex)
        {
            for (int coefficientIndex = 0; coefficientIndex < newNumChannels; ++coefficientIndex)
            {
                auto finalSampleValue = 0.0f;
                for (int sampleIndex = 0; sampleIndex < m_numChannels; ++sampleIndex)
                {
                    auto sample = m_samples[frameIndex * m_numChannels + sampleIndex];
                    auto coefficientValue = 0.0f;

                    if (newNumChannels == 1)
                    {
                        auto coefficients = Downmix::monoCoefficients();
                        coefficientValue = coefficients[sampleIndex];
                    }
                    else if (newNumChannels == 2)
                    {
                        auto coefficients = Downmix::stereoCoefficients();
                        coefficientValue = coefficients[coefficientIndex][sampleIndex];
                    }

                    finalSampleValue += sample * coefficientValue;
                }

                result[frameIndex * newNumChannels + coefficientIndex] = finalSampleValue;
            }
        }

        m_samples = result;
        m_numChannels = newNumChannels;
    }

    const std::vector<float>& AudioBuffer::samples() const
    {
        return m_samples;
    }

    int AudioBuffer::sampleRate() const
    {
        return m_sampleRate;
    }

    int AudioBuffer::numChannels() const
    {
        return m_numChannels;
    }

    int AudioBuffer::numFrames() const
    {
        return m_samples.size() / m_numChannels;
    }
}