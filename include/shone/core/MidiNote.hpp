#pragma once
#include <string>

namespace shone::gui
{
    class MidiNote
    {
    public:
        MidiNote(int number);
        MidiNote(std::string name);

        bool isSharp() const;
           
        int number() const;
        float frequency() const;
        std::string toString() const;

    private:
        int m_number;
        float m_frequency;
        std::string m_name;
    };

    MidiNote operator "" _mnote(const char* literal, std::size_t length);
}