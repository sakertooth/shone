#include <stdexcept>
#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>

#include "shone/core/MidiNote.hpp"

namespace shone::gui
{
    constexpr auto REFERENCE_VALUE = 60;
    constexpr auto MIDDLE_C_PITCH = 261.63f;
    constexpr auto MIDDLE_C_OCTAVE = 4;
    const auto NOTE_LETTERS = std::array<std::string, 12>{"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    MidiNote::MidiNote(int number) :
        m_number(number),
        m_frequency(MIDDLE_C_PITCH * std::exp2((number - REFERENCE_VALUE) / 12.0f)),
        m_name(NOTE_LETTERS[number % 12] + std::to_string(number / 12 - 1))
    {
        assert(number >= 0 && number <= 127 && "Invalid MIDI note number");
    }

    MidiNote::MidiNote(const std::string& name) : m_name(name)
    {
        assert(name.length() >= 2 && "Invalid length of MIDI note name");

        const auto octave = std::stoi(name.substr(name[1] == '#' ? 2 : 1));
        const auto octaveDistance = octave - 4;
        const auto noteDistance = std::distance(NOTE_LETTERS.begin(), std::find(NOTE_LETTERS.begin(), NOTE_LETTERS.end(), name.substr(0, 1)));
        const auto distanceFromReference = octaveDistance * 12 + noteDistance;

        m_number = REFERENCE_VALUE + distanceFromReference;
        m_frequency = MIDDLE_C_PITCH * std::exp2(distanceFromReference / 12.0f);
    }

    bool MidiNote::isSharp() const
    {
        return m_name[1] == '#';
    }

    int MidiNote::number() const
    {
        return m_number;
    }

    int MidiNote::octave() const
    {
        return std::stoi(m_name.substr(isSharp() ? 2 : 1));
    }

    float MidiNote::frequency() const
    {
        return m_frequency;
    }

    const std::string& MidiNote::name() const
    {
        return m_name;
    }

    std::string MidiNote::noteLetter() const
    {
        return m_name.substr(0, isSharp() ? 2 : 1);
    }
}