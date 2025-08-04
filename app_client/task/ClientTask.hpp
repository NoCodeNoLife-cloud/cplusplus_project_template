#pragma once
#include "utils/time/FunctionProfiler.hpp"

namespace app_client {
/// @brief A class that represents a client task
/// @details This class is responsible for running the main task and logging client info
class ClientTask {
 public:
  explicit ClientTask(const std::string &project_name_) : timer_(project_name_) {}

  /// @brief Run the main task
  /// @return true if the task was successful
  auto run() -> bool;

  /// @brief Logs client info
  static auto logClientInfo() -> void;

 private:
  common::FunctionProfiler timer_;
};

}  // namespace app_client
