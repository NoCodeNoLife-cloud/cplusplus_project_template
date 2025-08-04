#include <glog/logging.h>

#include "aop/LauncherAspect.hpp"
#include "task/MainTask.hpp"

auto main(const int32_t, char*[]) -> int32_t {
  try {
    LOG(INFO) << "Application starting...";
    // Launch
    common::LauncherAspect launcher;
    LOG(INFO) << "Executing main task...";
    launcher.exec(app_client::MainTask::run);
    LOG(INFO) << "Application finished successfully.";
  } catch (const std::exception& e) {
    LOG(ERROR) << "Exception caught: " << e.what();
    return 1;
  } catch (...) {
    LOG(ERROR) << "Unknown exception caught.";
    return 1;
  }
  return 0;
}
