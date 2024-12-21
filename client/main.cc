#include <iostream>

#include " aop/LauncherAspect.hpp"

auto business() -> bool {
  // Implement business logic here.
  std::this_thread::sleep_for(std::chrono::seconds(1));
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
