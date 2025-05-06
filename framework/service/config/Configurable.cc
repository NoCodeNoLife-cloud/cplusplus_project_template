#include <service/config/Configurable.hpp>

namespace framework {
  Configurable::~Configurable() = default;

  auto Configurable::validateConfig(const Config& config) const -> bool {
    return true;
  }
}
