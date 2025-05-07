#include <service/config/Configurable.hpp>

namespace common {
  Configurable::~Configurable() = default;

  auto Configurable::validateConfig(const Config& config) const -> bool {
    return true;
  }
}
