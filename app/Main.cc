#include <widget/MainWindow.hpp>
#include <QApplication>
#include <boot/Startup.hpp>
#include <aop/LauncherAspect.hpp>
#include <glog/logging.h>

common::Startup startup;

auto mainTask(int32_t argc, char* argv[]) -> bool
{
    QApplication app(argc, argv);
    app::MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}

// ReSharper disable once CppDFAConstantFunctionResult
auto business(const int32_t argc, char* argv[]) -> bool
{
    try
    {
        mainTask(argc, argv);
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
    launcher.exec(business, argc, argv);
}
