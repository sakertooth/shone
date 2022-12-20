#include "RubberbandHelper.hpp"
#include "AudioBuffer.hpp"
#include <cmath>

int main() 
{
    auto audioBuffer = shone::core::AudioBuffer{"files/Sine_wave_440.wav"};
    auto rubberBandStretcher = RubberBand::RubberBandStretcher{static_cast<size_t>(audioBuffer.sampleRate()), 2};
    rubberBandStretcher.setPitchScale(std::pow(2.0, 1 / 12.0));

    auto pithedBuffer = shone::core::RubberbandHelper::executeRubberband(rubberBandStretcher, audioBuffer.audioFrames());
    auto pitchedFileBuffer = shone::core::AudioBuffer{pithedBuffer};
    pitchedFileBuffer.writeToDisk("files/Sine_wave_440_1ct.wav", SF_FORMAT_WAV | SF_FORMAT_PCM_24);
}