#pragma once
#include <boost/serialization/serialization.hpp>

namespace framework::iface {
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
} // namespace framework::iface
