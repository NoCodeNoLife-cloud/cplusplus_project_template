#pragma once
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  template <typename T>
  concept DerivedFromBoostSerializable = std::is_base_of_v<IBoostSerializable<T>, T>;

  class BoostSerializer abstract {
  public:
    template <DerivedFromBoostSerializable T>
    static auto serializeObjectToBinaryString(const T& obj) -> std::string;
    template <DerivedFromBoostSerializable T>
    static auto deserializeObjectFromBinaryString(const std::string& data) -> T;
  };

  template <DerivedFromBoostSerializable T>
  auto BoostSerializer::serializeObjectToBinaryString(const T& obj) -> std::string {
    std::ostringstream o_string_stream;
    boost::archive::binary_oarchive binary_o_archive(o_string_stream);
    binary_o_archive << obj;
    return o_string_stream.str();
  }

  template <DerivedFromBoostSerializable T>
  auto BoostSerializer::deserializeObjectFromBinaryString(const std::string& data) -> T {
    T t = T();
    std::istringstream i_string_stream(data);
    boost::archive::binary_iarchive binary_i_archive(i_string_stream);
    binary_i_archive >> t;
    return t;
  }
}
