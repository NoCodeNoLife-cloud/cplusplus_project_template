#include <aop/LauncherAspect.hpp>
// ReSharper disable once CppDFAConstantFunctionResult
auto business() -> bool {
  try {
    // Implement business logic here.
    return EXIT_SUCCESS;
    // ReSharper disable once CppDFAUnreachableCode
  } catch (const std::exception& e) {
    LOG(ERROR) << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}

// ReSharper disable once CppParameterNeverUsed
auto main(int32_t argc, char* argv[]) -> int32_t {
  common::LauncherAspect launcher;
  launcher.exec(business);
}
