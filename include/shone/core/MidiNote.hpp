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
        float frequency() const;
        std::string name() const;

    private:
        int m_number;
        float m_frequency;
        std::string m_name;
    };
}