#pragma once
namespace common {
// ReSharper disable once CppTemplateParameterNeverUsed
template <typename T>
class IBoostSerializable abstract {
 public:
  virtual ~IBoostSerializable() = default;

 private:
  friend class boost::serialization::access;

  /// @brief Serialization implementation
  /// @param archive Archive
  /// @param version Version
  template <class Archive>
  auto serialize(Archive& archive, uint32_t version) -> void;
};

template <typename T>
template <class Archive>
auto IBoostSerializable<T>::serialize(Archive& archive, const uint32_t version) -> void {
  static_cast<T*>(this)->serializeImpl(archive, version);
}
}  // namespace common
