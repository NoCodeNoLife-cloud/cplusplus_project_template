#include <glog/logging.h>

#include "task/MainTask.hpp"
#include "aop/LauncherAspect.hpp"

auto main(const int32_t, char*) -> int32_t {
  try {
    // Launch the application.
    common::LauncherAspect launcher;
    launcher.exec(app_server::MainTask::run);
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }
}
