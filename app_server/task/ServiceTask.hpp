#pragma once

namespace app_server {
/// @brief ServiceTask is responsible for managing the main service loop
/// and coordinating various subsystems within the application server.
class ServiceTask {
 public:
  /// @brief Run the main task
  /// @return true if the task was successful
  static auto run() -> bool;
};
}  // namespace app_server
