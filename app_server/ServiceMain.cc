#include <glog/logging.h>

#include "log/GLogConfigurator.hpp"
#include "task/ServiceTask.hpp"

auto main(const int32_t, char*) -> int32_t {
  service::GLogConfigurator log_configurator;
  log_configurator.execute();

  try {
    // Launch the application.
    app_server::ServiceTask service_task;
    service_task.run();
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }
}
