#include "GLogOptions.hpp"

namespace common {
  GLogOptions::GLogOptions() = default;
  GLogOptions::~GLogOptions() = default;
  GLogOptions::GLogOptions(const GLogOptions& other) = default;
  GLogOptions& GLogOptions::operator=(const GLogOptions& other) = default;
  GLogOptions::GLogOptions(GLogOptions&& other) noexcept = default;

  auto GLogOptions::minLogLevel() const -> int32_t {
    return min_log_level_;
  }

  auto GLogOptions::logName() const -> std::string {
    return log_name_;
  }
}
