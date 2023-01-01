#include <QHBoxLayout>
#include <QScrollArea>

#include "shone/gui/MainGui.hpp"
#include "shone/gui/PianoRoll.hpp"

namespace shone::gui
{
    MainGui::MainGui(QWidget* parent) : QWidget(parent)
    {
        auto pianoRoll = new PianoRoll{};
        pianoRoll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        
        auto pianoRollScrollArea = new QScrollArea{};
        pianoRollScrollArea->setBackgroundRole(QPalette::Dark);
        pianoRollScrollArea->setWidget(pianoRoll);

        auto layout = new QHBoxLayout{this};
        layout->addWidget(pianoRollScrollArea);
    }
}