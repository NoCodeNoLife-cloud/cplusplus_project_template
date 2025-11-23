#include <glog/logging.h>

#include "src/task/ClientTask.hpp"

auto main(const int32_t,
          char*[])
    -> int32_t
{
    app_client::ClientTask main_task("client");
    main_task.run();
}
