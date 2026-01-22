#include <glog/logging.h>

#include "src/task/ServerTask.hpp"

auto main(const int32_t, char*[]) -> int32_t
{
    app_server::task::ServerTask service_task("server");
    service_task.run();
}
