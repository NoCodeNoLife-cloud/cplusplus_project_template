#include <iostream>
#include <QApplication>
#include <boot/Startup.hpp>
#include <glog/logging.h>
#include <widget/MainWindow.hpp>
#include <aop/LauncherAspect.hpp>

common::Startup startup;

auto createMainWindow(int32_t argc, char* argv[]) -> bool
{
    QApplication app(argc, argv);
    app::MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}

// ReSharper disable once CppDFAConstantFunctionResult
auto mainTask(const int32_t argc, char* argv[]) -> bool
{
    try
    {
        createMainWindow(argc, argv);
        return EXIT_SUCCESS;
        // ReSharper disable once CppDFAUnreachableCode
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

auto main(const int32_t argc, char* argv[]) -> int32_t
{
    common::LauncherAspect launcher;
    launcher.exec(mainTask, argc, argv);
}
