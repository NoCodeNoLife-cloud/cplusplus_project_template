#include <service/config/Configurable.hpp>

namespace framework::service::config {
  Configurable::~Configurable() = default;

  auto Configurable::validateConfig(const Config& config) const -> bool {
    return true;
  }
}
