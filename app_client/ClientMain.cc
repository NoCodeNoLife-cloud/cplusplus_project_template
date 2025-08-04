#include <glog/logging.h>

#include "task/ClientTask.hpp"

auto main(const int32_t, char*[]) -> int32_t {
  try {
    LOG(INFO) << "Application starting...";
    app_client::ClientTask main_task("project");
    main_task.run();
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
