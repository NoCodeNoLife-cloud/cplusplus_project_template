#pragma once

namespace app_server {
class MainTask {
 public:
  /// @brief Run the main task
  /// @return true if the task was successful
  static auto run() -> bool;
};
}  // namespace app_server
