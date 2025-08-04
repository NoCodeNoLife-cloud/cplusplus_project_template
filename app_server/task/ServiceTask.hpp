#pragma once

namespace app_server {
class ServiceTask {
 public:
  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> bool;
};
}  // namespace app_server
