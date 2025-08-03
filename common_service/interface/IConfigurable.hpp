#pragma once
namespace service {
class IConfigurable abstract {
 public:
  virtual ~IConfigurable() = default;

 private:
  /// @brief Configure the service.
  /// @return true if configuration is successful, false otherwise.
  [[nodiscard]] virtual auto doConfig() -> bool = 0;
};
}  // namespace service
