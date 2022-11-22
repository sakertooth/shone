#include "MusicalNote.hpp"
#include <iostream>

namespace shone::core 
{

    MusicalNote::MusicalNote(float frequency, float referenceFrequency) :
        m_frequency(frequency),
        m_referenceFrequency(referenceFrequency)
    {
        if (static_cast<int>(frequency) == 0)
        {
            throw std::domain_error{"MusicalNote: Frequency cannot be zero."};
        }

        auto numCentsFromReference = std::round(1200 * std::log2(frequency / referenceFrequency));
        
        auto numOctavesFromReference = std::round(numCentsFromReference / 1200);
        numCentsFromReference -= numOctavesFromReference * 1200;

        auto numSemitonesFromReference = std::round(numCentsFromReference / 100);
        numCentsFromReference -= numSemitonesFromReference * 100;

        auto noteVal = static_cast<int>(numSemitonesFromReference) >= 0 ? 
            static_cast<Note>(static_cast<int>(numSemitonesFromReference)) : 
            static_cast<Note>(12 + static_cast<int>(numSemitonesFromReference));

        m_note = noteVal;  
        m_octave = 4 + numOctavesFromReference;
        m_cents = numCentsFromReference;
    }

    //TODO
    MusicalNote::MusicalNote(Note note, int octave, int cents, float referenceFrequency)
    {}

    std::string MusicalNote::noteToStr(Note note) 
    {
        switch (note) 
        {
        case Note::A:
            return "A";
        case Note::ASharp:
            return "A#";
        case Note::B:
            return "B";
        case Note::C:
            return "C";
        case Note::CSharp:
            return "C#";
        case Note::D:
            return "D";
        case Note::DSharp:
            return "D#";
        case Note::E:
            return "E";
        case Note::F:
            return "F";
        case Note::FSharp:
            return "F#";
        case Note::G:
            return "G#";
        case Note::GSharp:
            return "G#";
        default:
            return "N/A";
        }
    }

    float MusicalNote::frequency() const 
    {
        return m_frequency;
    }

    float MusicalNote::referenceFrequency() const
    {
        return m_referenceFrequency;
    }

    MusicalNote::Note MusicalNote::note() const 
    {
        return m_note;
    }

    int MusicalNote::octave() const 
    {
        return m_octave;
    }

    int MusicalNote::cents() const
    {
        return m_cents;
    }

    std::ostream& operator<<(std::ostream& os, const MusicalNote& note) 
    {
        os << note.m_note << note.m_octave << "(" << note.m_cents << " ct)";
        return os;
    }
}