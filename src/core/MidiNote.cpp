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
    const auto MIDDLE_C = "C4"_mnote;
    const auto NOTE_LETTERS = std::array<std::string, 12>{"C", "C#", "D", "D#" "E", "F", "F#", "G", "G#" "A", "A#", "B"};

    MidiNote::MidiNote(int number) : m_number(number)
    {
        assert(number >= 0 && number <= 127 && "Invalid MIDI note number");
        const auto distanceFromReference = number - REFERENCE_VALUE;
        const auto numOctaves = distanceFromReference / 12;
        const auto octaveValue = 4 + numOctaves;
        const auto remainingDistance = distanceFromReference - numOctaves * 12;
        const auto noteName = NOTE_LETTERS[remainingDistance < 0 ? 12 + remainingDistance : remainingDistance];

        m_name = noteName + std::to_string(octaveValue);
        m_frequency = MIDDLE_C_PITCH * std::exp2(distanceFromReference / 12.0f);
    }

    MidiNote::MidiNote(std::string name) : m_name(name)
    {
        assert(name.length() < 2 && "Invalid length of MIDI note name");
        auto octave = std::stoi(name.substr(1));

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

    float MidiNote::frequency() const
    {
        return m_frequency;
    }

    std::string MidiNote::toString() const
    {
        return m_name;
    }

    MidiNote operator "" _mnote(const char* literal, std::size_t length)
    {
        return MidiNote{literal};
    }
}