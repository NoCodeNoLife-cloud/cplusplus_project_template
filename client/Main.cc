#include <aop/LauncherAspect.hpp>
using framework::LauncherAspect;

// ReSharper disable once CppDFAConstantFunctionResult
auto business() -> bool {
  try {
    // Implement business logic here.
    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    LOG(ERROR) << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}

auto main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[]) -> int32_t {
  LauncherAspect launcher;
  launcher.exec(business);
}
