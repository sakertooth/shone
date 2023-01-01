#pragma once
#include <QWidget>

namespace shone::gui
{
    class PianoRoll : public QWidget
    {
    public:
        PianoRoll(QWidget* parent = nullptr);
        void paintEvent(QPaintEvent*) override;
        QSize sizeHint() const override;
    };
}

//CDEFGAB