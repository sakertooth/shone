#include <QStatusBar>
#include <QMenuBar>

#include "shone/gui/MainWindow.hpp"
#include "shone/gui/MainGui.hpp"

namespace shone::gui
{
    MainWindow::MainWindow() : QMainWindow()
    {
        setWindowTitle("Shone");
        resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        
        auto mainGui = new MainGui{this};
        setCentralWidget(mainGui);
    }
}
