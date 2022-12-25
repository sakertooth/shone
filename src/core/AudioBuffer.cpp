#include "shone/AudioBuffer.hpp"
#include "shone/AudioFile.hpp"

namespace shone::core
{

    AudioBuffer::AudioBuffer(const AudioFile& audioFile, int sampleRate, int numChannels) :
        m_samples(audioFile.samples()),
        m_sampleRate(audioFile.sampleRate()),
        m_numChannels(audioFile.numChannels())
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

    AudioBuffer::AudioBuffer(const std::vector<float>& samples, int sampleRate, int numFrames)
    {
        
    }

    AudioBuffer::AudioBuffer(size_t size, int sampleRate, int numChannels)
    {

    }

    void AudioBuffer::applyStretcher(const RubberBand::RubberBandStretcher& stretcher, int from, int to)
    {
        
    }

    void AudioBuffer::writeToDisk(std::filesystem::path& filePath, int mode)
    {

    }

    void AudioBuffer::resample(int newSampleRate, int interpolationMode)
    {

    }

    void AudioBuffer::mix(int newNumChannels)
    {

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
        return m_numFrames;
    }
}