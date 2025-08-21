#pragma once
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "filesystem/io/interface/IBoostSerializable.hpp"

namespace common {
/// @class BoostObjectSerializer
/// @brief A utility class for serializing and deserializing objects using Boost.Serialization.
/// This class provides static methods to convert objects to and from binary strings and XML files.
/// The objects must derive from IBoostSerializable to be serializable.
template <typename T>
concept DerivedFromBoostSerializable = std::is_base_of_v<IBoostSerializable<T>, T>;

class BoostObjectSerializer {
 public:
  /// @brief Serializes an object to a binary string representation.
  /// @tparam T The type of the object to serialize, must derive from IBoostSerializable.
  /// @param obj The object to serialize.
  /// @return A string containing the binary serialized data.
  template <DerivedFromBoostSerializable T>
  static auto serializeObjectToBinaryString(const T& obj) -> std::string;

  /// @brief Deserializes an object from a binary string representation.
  /// @tparam T The type of the object to deserialize, must derive from IBoostSerializable and be default initializable.
  /// @param data The binary string data to deserialize from.
  /// @return The deserialized object.
  template <DerivedFromBoostSerializable T>
    requires std::default_initializable<T>
  static auto deserializeObjectFromBinaryString(const std::string& data) -> T;

  /// @brief Serializes an object to an XML file.
  /// @tparam T The type of the object to serialize, must derive from IBoostSerializable.
  /// @param obj The object to serialize.
  /// @param filePath The path to the file where the XML data will be saved.
  /// @return True if the serialization was successful, false otherwise.
  template <DerivedFromBoostSerializable T>
  static auto serializeObjectToXMLFile(const T& obj, const std::filesystem::path& filePath) -> bool;

  /// @brief Deserializes an object from an XML file.
  /// @tparam T The type of the object to deserialize, must derive from IBoostSerializable.
  /// @param filePath The path to the XML file to deserialize from.
  /// @return The deserialized object.
  template <DerivedFromBoostSerializable T>
  static auto serializeObjectFromXMLFile(const std::filesystem::path& filePath) -> T;
};

template <DerivedFromBoostSerializable T>
auto BoostObjectSerializer::serializeObjectToBinaryString(const T& obj) -> std::string {
  std::ostringstream o_string_stream;
  boost::archive::binary_oarchive binary_o_archive(o_string_stream);
  binary_o_archive << obj;
  return o_string_stream.str();
}

template <DerivedFromBoostSerializable T>
  requires std::default_initializable<T>
auto BoostObjectSerializer::deserializeObjectFromBinaryString(const std::string& data) -> T {
  T t = T();
  std::istringstream i_string_stream(data);
  boost::archive::binary_iarchive binary_i_archive(i_string_stream);
  binary_i_archive >> t;
  return t;
}

template <DerivedFromBoostSerializable T>
auto BoostObjectSerializer::serializeObjectToXMLFile(const T& obj, const std::filesystem::path& filePath) -> bool {
  try {
    std::ofstream ofs(filePath);
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(obj);
    return true;
  } catch (std::exception& e) {
    throw std::runtime_error(e.what());
  }
}

template <DerivedFromBoostSerializable T>
auto BoostObjectSerializer::serializeObjectFromXMLFile(const std::filesystem::path& filePath) -> T {
  try {
    T t;
    std::ifstream ifs(filePath);
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(t);
    return t;
  } catch (std::exception& e) {
    throw std::runtime_error(e.what());
  }
}
}  // namespace common
