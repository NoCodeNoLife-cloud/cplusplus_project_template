#include "QtExecutor.hpp"

#include <QApplication>

#include "widget/QtMainWindow.hpp"

namespace app
{
    auto QtExecutor::execute(int32_t argc, char* argv[]) -> bool
    {
        QApplication app(argc, argv);
        QtMainWindow mainWindow;
        mainWindow.show();
        return !QApplication::exec();
    }
}
