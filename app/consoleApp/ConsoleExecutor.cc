#include <consoleApp/ConsoleExecutor.hpp>
#include <glog/logging.h>

namespace app
{
    auto ConsoleExecutor::execute(int32_t argc, char* argv[]) -> bool
    {
        try
        {
            // Enter your execution code here
            LOG(INFO) << "Hello world";
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
}
