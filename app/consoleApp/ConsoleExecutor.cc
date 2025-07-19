#include "ConsoleExecutor.hpp"

#include <glog/logging.h>

namespace app
{
    auto ConsoleExecutor::execute(int32_t argc, char* argv[]) -> bool
    {
        try
        {
            LOG(INFO) << "console Application start...";
            // Enter your execution code here
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
}
