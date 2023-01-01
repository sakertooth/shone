#pragma once
#include <string>

namespace shone::gui
{
    class MidiNote
    {
    public:
        MidiNote(int number);
        MidiNote(const std::string& name);

        bool isSharp() const;
           
        int number() const;
        int octave() const;
        float frequency() const;
        const std::string& name() const;
        std::string noteLetter() const;

    private:
        int m_number;
        float m_frequency;
        std::string m_name;
    };
}