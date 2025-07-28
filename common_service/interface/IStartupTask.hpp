#pragma once

namespace service {
class IStartupTask abstract {
 public:
  virtual ~IStartupTask() = default;
  virtual auto execute() -> bool = 0;
};
}  // namespace service
