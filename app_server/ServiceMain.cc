#include <glog/logging.h>

#include "task/ServiceTask.hpp"

auto main(const int32_t, char *[]) -> int32_t
{
    app_server::ServiceTask service_task;
    service_task.run();
}
