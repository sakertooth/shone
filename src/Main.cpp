#include <QApplication>
#include "shone/gui/MainWindow.hpp"

int main(int argc, char** argv)
{
    auto app = new QApplication{argc, argv};

    auto mainWindow = new shone::gui::MainWindow();
    mainWindow->show();

    return app->exec();
}