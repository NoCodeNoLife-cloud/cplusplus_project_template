#pragma once

namespace app_client {

class MainTask {
 public:
  /// @brief Run the main task
  /// @return true if the task was successful
  static auto run() -> bool;

  /// @brief Logs client info
  static auto logClientInfo() -> void;
};

}  // namespace app_client
