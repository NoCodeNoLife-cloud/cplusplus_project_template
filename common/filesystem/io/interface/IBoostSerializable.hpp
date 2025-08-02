#pragma once
namespace common {
// ReSharper disable once CppTemplateParameterNeverUsed
template <typename T>
class IBoostSerializable abstract {
 public:
  virtual ~IBoostSerializable() = default;

 private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& archive, uint32_t version);
};

template <typename T>
template <class Archive>
void IBoostSerializable<T>::serialize(Archive& archive, const uint32_t version) {
  static_cast<T*>(this)->serializeImpl(archive, version);
}
}  // namespace common
