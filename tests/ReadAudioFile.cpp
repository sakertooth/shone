#include "shone/RubberbandHelper.hpp"
#include "shone/AudioBuffer.hpp"
#include <cassert>
#include <iostream>

int main()
{
    // original sample rate = 132000, duration = 5s (660000 samples), 1 channel
    const auto filePath = "files/Sine_wave_440.wav";
    const auto audioBuffer = shone::core::AudioBuffer{filePath};
    audioBuffer.writeToDisk("files/Sine_wave_440_read_verify.wav", SF_FORMAT_WAV | SF_FORMAT_PCM_24);
}