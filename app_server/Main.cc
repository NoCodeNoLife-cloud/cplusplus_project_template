#include <glog/logging.h>

#include "aop/LauncherAspect.hpp"
#include "task/MainTask.hpp"

auto main(const int32_t, char*) -> int32_t {
  try {
    // Launch the application.
    common::LauncherAspect launcher;
    launcher.exec(app_server::MainTask::run);
  } catch (const std::exception& e) {
    LOG(ERROR) << e.what();
  }
}
