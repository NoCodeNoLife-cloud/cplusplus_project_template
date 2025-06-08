#include <aop/LauncherAspect.hpp>
#include <glog/logging.h>

auto mainTask() -> void
{
}

// ReSharper disable once CppDFAConstantFunctionResult
auto business() -> bool
{
    try
    {
        mainTask();
        return EXIT_SUCCESS;
        // ReSharper disable once CppDFAUnreachableCode
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

auto main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[]) -> int32_t
{
    common::LauncherAspect launcher;
    launcher.exec(business);
}
