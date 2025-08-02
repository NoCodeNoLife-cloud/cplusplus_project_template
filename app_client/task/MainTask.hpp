#pragma once

namespace app_client {

class MainTask {
 public:
  static auto run() -> bool;
  static auto logClientInfo() -> void;
};

}  // namespace app_client
