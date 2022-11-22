#pragma once
#include <cmath>
#include <string>

namespace shone::core 
{
    class MusicalNote
    {
    public:
        enum class Note 
        {
            A,
            ASharp,
            B,
            C,
            CSharp,
            D,
            DSharp,
            E,
            F,
            FSharp,
            G,
            GSharp
        };

        MusicalNote(float frequency, float referenceFrequency = 440.0f);
        MusicalNote(Note note, int octave = 4, int cents = 0.0f, float referenceFrequency = 440.0f);

        static std::string noteToStr(Note note);

        float frequency() const;
        float referenceFrequency() const;
        Note note() const;
        int octave() const;
        int cents() const;

        friend std::ostream& operator<<(std::ostream& os, const MusicalNote& note);

    private:
        float m_frequency;
        float m_referenceFrequency;
        Note m_note;
        int m_octave;
        int m_cents;
    };
}