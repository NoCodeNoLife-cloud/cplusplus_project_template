#include <boot/AppBoot.hpp>
#include <consoleApp/ConsoleExecutor.hpp>
#include <qtApp/QtExecutor.hpp>

namespace app
{
    auto AppBoot::boot(const int32_t argc, char* argv[]) const -> bool
    {
        bool result = false;
        if (config_.appType() == "console")
        {
            ConsoleExecutor console_executor;
            result = console_executor.execute(argc, argv);
        }
        else if (config_.appType() == "qt")
        {
            QtExecutor qtExecutor;
            result = qtExecutor.execute(argc, argv);
        }
        return result;
    }
}
