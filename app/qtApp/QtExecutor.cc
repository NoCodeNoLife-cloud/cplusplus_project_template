#include "QtExecutor.hpp"

#include <QApplication>
#include <glog/logging.h>

#include "widget/QtMainWindow.hpp"

namespace app
{
    auto QtExecutor::execute(int32_t argc, char* argv[]) -> bool
    {
        LOG(INFO) << "Qt Application start...";
        QApplication app(argc, argv);
        QtMainWindow mainWindow;
        mainWindow.show();
        return !QApplication::exec();
    }
}
