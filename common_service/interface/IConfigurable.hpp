#pragma once
namespace service {
class IConfigurable abstract {
 public:
  virtual ~IConfigurable() = default;

 private:
  [[nodiscard]] virtual auto doConfig() -> bool = 0;
};
}  // namespace service
