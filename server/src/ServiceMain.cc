#include <glog/logging.h>

#include "../include/task/ServerTask.hpp"

auto main(const int32_t, char*[]) -> int32_t
{
    app_server::ServerTask service_task("server");
    service_task.run();
}
