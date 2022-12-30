#pragma once
#include <QMainWindow>

namespace shone::gui
{
    constexpr auto DEFAULT_WIDTH = 1366;
    constexpr auto DEFAULT_HEIGHT = 768;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow();

    private:
        QWidget* test;
    };
}