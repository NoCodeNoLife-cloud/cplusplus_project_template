#pragma once
#include <QApplication>
#include <interface/IApplicationExecutor.hpp>
#include <qtApp/widget/QtMainWindow.hpp>

namespace app
{
    class QtExecutor final : public IApplicationExecutor
    {
    public:
        [[nodiscard]] auto execute(int32_t argc, char* argv[]) -> bool override
        {
            QApplication app(argc, argv);
            QtMainWindow mainWindow;
            mainWindow.show();
            return !QApplication::exec();
        }
    };
}
