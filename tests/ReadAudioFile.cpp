#include "RubberbandHelper.hpp"
#include "AudioBuffer.hpp"
#include <cassert>
#include <iostream>

int main()
{
    // sample rate = 132000, duration = 5s, 1 channel
    const auto filePath = "files/Sine_wave_440.wav";
    const auto audioBuffer = shone::core::AudioBuffer{filePath};
    
    assert(audioBuffer.filePath() == filePath);
    assert(audioBuffer.sampleRate() == 132000);
    assert(audioBuffer.originalNumChannels() == 1);
    assert(audioBuffer.audioFrames().size() == 660000 * 2);
    assert(static_cast<int>(audioBuffer.audioFrames().size() / 2 / static_cast<double>(audioBuffer.sampleRate())) == 5);
}