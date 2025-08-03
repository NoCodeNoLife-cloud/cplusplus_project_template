#pragma once
#include <cstdint>

namespace app {
class IApplicationExecutor abstract {
 public:
  virtual ~IApplicationExecutor() = default;

  /// @brief Executes the application with the given command-line arguments.
  /// @param argc The number of command-line arguments.
  /// @param argv An array of pointers to null-terminated strings representing the command-line arguments.
  /// @return true if the execution was successful, false otherwise.
  [[nodiscard]] virtual auto execute(int32_t argc, char* argv[]) -> bool = 0;
};
}  // namespace app
