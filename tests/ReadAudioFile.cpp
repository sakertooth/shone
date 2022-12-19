#include "RubberbandHelper.hpp"
#include "AudioBuffer.hpp"
#include <cassert>
#include <iostream>

int main()
{
    const auto filePath = "files/Sine_wave_440.wav";
    const auto audioBuffer = shone::core::AudioBuffer{filePath};
    
    assert(audioBuffer.filePath() == filePath);
    assert(audioBuffer.sampleRate() == 132000);
    assert(audioBuffer.audioFrames().size() == 330000);
    assert(audioBuffer.audioFrames().size() / static_cast<double>(audioBuffer.sampleRate()) == 5.0f);
}