#pragma once
#include <QWidget>

namespace shone::gui
{
    class Piano : public QWidget
    {
    public:
        Piano(QWidget* parent = nullptr);
        void paintEvent(QPaintEvent*) override;
        QSize sizeHint() const override;
    };
}

//CDEFGAB