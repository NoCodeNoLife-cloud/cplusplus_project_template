#include "aop/LauncherAspect.hpp"

auto business() -> bool {
  // Implement business logic here.
  return EXIT_SUCCESS;
}

auto main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[]) -> int32_t {
  try {
    framework::aop::LauncherAspect launcher;
    auto res = launcher.exec(business);
  } catch (const std::exception& e) {
    LOG(ERROR) << "Error: " << e.what() << std::endl;
  }
}