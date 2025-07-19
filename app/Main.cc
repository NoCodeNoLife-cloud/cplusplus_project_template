#include <cstdlib>
#include <stdexcept>
#include <glog/logging.h>

#include "aop/LauncherAspect.hpp"
#include "boot/ApplicationLauncher.hpp"
// ReSharper disable once CppDFAConstantFunctionResult
auto mainTask(const int32_t argc, char* argv[]) -> bool
{
    try
    {
        if (const app::ApplicationLauncher app_boot; !app_boot.boot(argc, argv))
        {
            throw std::runtime_error("Failed to run application");
        }
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
    coco::LauncherAspect launcher;
    launcher.exec(mainTask, argc, argv);
}
