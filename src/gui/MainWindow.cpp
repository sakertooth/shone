#include <QStatusBar>
#include <QMenuBar>

#include "shone/gui/MainWindow.hpp"

namespace shone::gui 
{
    MainWindow::MainWindow() : QMainWindow()
    {
        setWindowTitle("Shone");
        resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }
}
