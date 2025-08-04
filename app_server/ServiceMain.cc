#include <glog/logging.h>

#include "log/GLogConfigurator.hpp"
#include "task/ServiceTask.hpp"

auto main(const int32_t, char*) -> int32_t {
  service::GLogConfigurator log_configurator;
  log_configurator.execute();

  LOG(INFO) << "Starting application...";
  try {
    app_server::ServiceTask::run();
  } catch (const std::exception& e) {
    LOG(ERROR) << "Exception occurred: " << e.what();
  } catch (...) {
    LOG(ERROR) << "Unknown exception occurred.";
  }
}
