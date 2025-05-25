#include <aop/LauncherAspect.hpp>
#include <filesystem/serialize/YamlSerializer.hpp>
#include <glog/logging.h>
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

auto main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[]) -> int32_t {
  common::LauncherAspect launcher;
  launcher.exec(business);
}
