#include "shone/AudioFile.hpp"
#include <cassert>
#include <iostream>

int main(int argc, char** argv)
{
    auto audioFile = shone::core::AudioFile{"Sine_wave_440.wav"};
    assert(audioFile.sampleRate() == 132000);
    assert(audioFile.numChannels() == 1);
    assert(audioFile.samples().size() == 660000);
    return EXIT_SUCCESS;
}