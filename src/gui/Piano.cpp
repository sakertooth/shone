#include <QPainter>
#include <QLabel>

#include <array>
#include <iostream>

#include "shone/gui/Piano.hpp"
#include "shone/core/MidiNote.hpp"

namespace shone::gui
{
    constexpr auto WHITE_KEY_WIDTH = 80;
    constexpr auto WHITE_KEY_HEIGHT = 25;
    constexpr auto BLACK_KEY_WIDTH = 55;
    constexpr auto BLACK_KEY_HEIGHT = 15;
    constexpr auto PIANO_HEIGHT = 75 * WHITE_KEY_HEIGHT;

    Piano::Piano(QWidget* parent) : QWidget(parent) {}

    void Piano::paintEvent(QPaintEvent*)
    {
        auto painter = QPainter{this};
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::black);

        auto font = QFont{};
        font.setPointSize(8);
        painter.setFont(font);

        auto yPos = 0;
        auto drawKey = [&](const MidiNote& note, int width, int height, const QColor& keyColor, bool drawNoteName)
        {
            painter.drawRect(0, yPos, width, height);
            painter.fillRect(0, yPos, width, height, keyColor);

            if (drawNoteName)
            {
                painter.drawText(0, yPos, width, height, Qt::AlignRight | Qt::AlignVCenter, QString::fromStdString(note.name()));
            }
        };

        for (int i = 127; i >= 0; --i)
        {
            auto midiKey = MidiNote{i};
            if (midiKey.isSharp()) { continue; }

            drawKey(midiKey, WHITE_KEY_WIDTH, WHITE_KEY_HEIGHT, Qt::white, true);
            yPos += WHITE_KEY_HEIGHT;
        }

        yPos = 0;
        painter.setPen(Qt::white);
        painter.translate(0, WHITE_KEY_HEIGHT - BLACK_KEY_HEIGHT / 2);

        for (int i = 126; i >= 0; --i)
        {
            auto midiKey = MidiNote{i};
            if (!midiKey.isSharp())
            {
                yPos += WHITE_KEY_HEIGHT;
                continue;
            }

            drawKey(midiKey, BLACK_KEY_WIDTH, BLACK_KEY_HEIGHT, Qt::black, false);
        }
    }

    QSize Piano::sizeHint() const
    {
        return QSize{WHITE_KEY_WIDTH, PIANO_HEIGHT};
    }
}